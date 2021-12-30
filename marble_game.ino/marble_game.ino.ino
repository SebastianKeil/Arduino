#include <InteractiveMatrix.h>
#include <three_to_five5pt7b.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#define PIN 6
#define matrix_width 17
#define matrix_height 12
#define N_PIXELS (matrix_width * matrix_height)

#define MAX_VEL 6
#define MAX_FORCE 10
#define MAX_ACC 6

#define MAX_VEL_MAG sqrt(MAX_VEL * MAX_VEL + MAX_VEL * MAX_VEL)
uint16_t MARBLE_COL = 5065;
uint16_t NO_COL = 0;


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/ CLASS_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

class Marbel{
  public:
  InteractiveMatrix *matrix;
  struct Vector2D old_pos;
  struct Vector2D pos;
  struct Vector2D vel;
  struct Vector2D acc;

  Marbel(uint16_t x, uint16_t y, InteractiveMatrix *matrix){
    this->pos.x = x;
    this->pos.y = y;
    this->vel = { 0, 0};
    this->acc = { 0, 0};
    this->matrix = matrix;
  }

  void applyForce(struct Vector2D tilt){
    this->acc.x = tilt.x;
    this->acc.y = tilt.y;

    if(this->acc.x > MAX_ACC) this->acc.x = MAX_ACC;
    if(this->acc.y > MAX_ACC) this->acc.y = MAX_ACC;
    if(this->acc.x < -MAX_ACC) this->acc.x = -MAX_ACC;
    if(this->acc.y < -MAX_ACC) this->acc.y = -MAX_ACC;
  }

  void roll(){
    this->old_pos.x = this->pos.x;
    this->old_pos.y = this->pos.y;
    
    this->vel.x += this->acc.x;
    this->vel.y += this->acc.y;

    //max velocity
    if(this->vel.x > MAX_VEL) this->vel.x = MAX_VEL;
    if(this->vel.y > MAX_VEL) this->vel.y = MAX_VEL;
    if(this->vel.x < -MAX_VEL) this->vel.x = -MAX_VEL;
    if(this->vel.y < -MAX_VEL) this->vel.y = -MAX_VEL;


    
    if(still_on_matrix('x')){
      if(this->vel.x > 0) this->pos.x ++;
      if(this->vel.x < 0) this->pos.x --;
    }
    if(still_on_matrix('y')){
      if(this->vel.y > 0) this->pos.y ++;
      if(this->vel.y < 0) this->pos.y --;
    }
  }

  void draw(){
    this->matrix->drawPixel(this->old_pos.x, this->old_pos.y, NO_COL);
    this->matrix->drawPixel(this->pos.x, this->pos.y, MARBLE_COL);
  }

  void friction(){
    if(this->vel.x > 0) this->vel.x --;
    if(this->vel.y > 0) this->vel.y --;
    if(this->vel.x < 0) this->vel.x ++;
    if(this->vel.y < 0) this->vel.y ++;
  }

  int calc_delay_time(){
    int vel_mag = sqrt(this->vel.x*this->vel.x + this->vel.y*this->vel.y);
    return map(vel_mag, 0, MAX_VEL_MAG, 100, 0);
  }

  bool still_on_matrix(char axis){
    switch (axis){
      case 'x':
        if((this->pos.x < 1 && this->vel.x < 1) || (this->pos.x > matrix_width-2 && this->vel.x > 0)) return false;
        break;
      case 'y':
        if((this->pos.y < 1 && this->vel.y < 1) || (this->pos.y > matrix_height-2 && this->vel.y > 0)) return false;
        break;
    }
    return true;
  }

  void print_vel_data(){
  Serial.print("X:"); Serial.print(this->acc.x); Serial.print("  ");
  Serial.print("Y:");Serial.print(this->acc.y); Serial.print(" .......... ");
  Serial.print("X:"); Serial.print(this->vel.x); Serial.print("  ");
  Serial.print("Y:");Serial.print(this->vel.y); Serial.print(" .......... ");
  Serial.print("X:"); Serial.print(this->pos.x); Serial.print("  ");
  Serial.print("Y:");Serial.println(this->pos.y);
}
};


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/ DATA _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// SENSOR DATA
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
sensors_event_t event; 

//MATRIX
CRGB matrixleds[N_PIXELS];
//NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG = 8
InteractiveMatrix *matrix = new InteractiveMatrix(matrixleds, matrix_width, matrix_height, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

//MARBLE GAME
struct Vector2D tilt;
Marbel *marble = new Marbel(8, 6, matrix);
int delay_time;


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/ FUNCTIONS_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
struct Vector2D calculate_tilt(){
  struct Vector2D force;
  force.x = map(static_cast<int>(event.magnetic.x), -50, 50, -MAX_FORCE, MAX_FORCE);
  force.y = map(static_cast<int>(event.magnetic.y), -65, 45, MAX_FORCE, -MAX_FORCE);
  return force;
}

void print_sensor_data(){
  if(digitalRead(3)) Serial.println("BUTTOM");
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("\t");
  Serial.print("Y: ");Serial.println(event.magnetic.y); Serial.print("\t");
}

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/ LOOPS_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT);
  FastLED.addLeds<NEOPIXEL,PIN>(matrixleds, N_PIXELS); 
  matrix->begin();

  if(!mag.begin()) Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
}

void loop() { 
  mag.getEvent(&event);
  //print_sensor_data();
  

  tilt = calculate_tilt();
  marble->applyForce(tilt);
  marble->roll();
  marble->friction();
  
  //marble->print_vel_data();
  marble->draw();

  matrix->show();

  delay_time = marble->calc_delay_time();
  delay(delay_time);
}
