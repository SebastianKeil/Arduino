#include <Adafruit_NeoPixel.h>
#include <Vector.h>


#define PIN 6
#define NUM_PIXELS 450
#define PIXEL_WIDTH 30  
#define PIXEL_LENGTH 15

#define TRIGGER 3
#define BUTTONS 4
#define ANALOG_X 0
#define ANALOG_y 1

#define NO_INPUTS 4
#define UP 1
#define DOWN 0
#define RIGHT 3
#define LEFT 2


class PlayerShip{
  public: int cockpit_x;
  public: int cockpit_y;
  public: int shooting_range = 30;
  public: int magazine = 5;
  int cockpit_pos;
  int left, right, down, up;
  int directions[5];
  int dir;
  public: bool is_shooting = false;

  public: int color_off[3] = {0,0,0};
  public: int ship_color[3] = {20,60,0};

public:
  PlayerShip(int cockpit_x, int cockpit_y){
    this->cockpit_x = cockpit_x;
    this->cockpit_y = cockpit_y;
    this->cockpit_pos = this->coordsToPixelNum(cockpit_x, cockpit_y);
  }

  setPixel(Adafruit_NeoPixel * strip, int color[3]){
    strip->setPixelColor(this->cockpit_pos, color[0], color[1], color[2]);
    strip->setPixelColor(coordsToPixelNum(cockpit_x-1, cockpit_y), color[0], color[1], color[2]);
    strip->setPixelColor(coordsToPixelNum(cockpit_x-1, cockpit_y+1), color[0], color[1], color[2]);
    strip->setPixelColor(coordsToPixelNum(cockpit_x-1, cockpit_y-1), color[0], color[1], color[2]);
  }

  int coordsToPixelNum(int x, int y) {
        int pixelNumber;
        if (y % 2 == 0) {
            pixelNumber = (y+1) * 30 - x - 1;
        } else {
            pixelNumber = y * 30 + x;
        }
        return pixelNumber;
    }

   void shoot(){
      //Bullet bullet = new Bullet(cockpit_x+1, cockpit_y);
   }

   void fly(Adafruit_NeoPixel* strip){
      this->checkInputs();
      switch (this->dir) {
            case UP:
                this->cockpit_y -= 1;
                break;
            case DOWN:
                this->cockpit_y += 1;
                break;
            case RIGHT:
                this->cockpit_x += 1;
                break;
            case LEFT:
                this->cockpit_x -= 1;
                break;
        }
        this->cockpit_pos = coordsToPixelNum(cockpit_x, cockpit_y);
   }

   void checkInputs(){
        this->zeroDirections();
        this->is_shooting = false;
        if(analogRead(0) < 400) left = map(analogRead(0), 400, 0, 2, 10);
        if(analogRead(0) > 700) right = map(analogRead(0), 700, 1023, 2, 10);
        if(analogRead(1) < 400) down = map(analogRead(1), 400, 0, 2, 10);
        if(analogRead(1) > 700) up = map(analogRead(1), 700, 1023, 2, 10);
        if(digitalRead(TRIGGER)) this->is_shooting = true;
        
        directions[0] = left;
        directions[1] = right;
        directions[2] = down;
        directions[3] = up;
        
        int dir_max = 0;
        int dir_max_index = 4;
        for(byte i = 0; i < 4; i++){
          if(directions[i] > dir_max){ 
            dir_max = directions[i];
            dir_max_index = i;
          }
        }
        this->dir = dir_max_index;
   }

   void zeroDirections(){
      this->left = 0;
      this->right = 0;
      this->down = 0;
      this->up = 0;
    }
};

class Bullet{
  int pos_x, pos_y;
  public: int color_off[3] = {0,0,0};
  public: int bullet_color[3] = {30,60,90};

  public:
    Bullet(int pos_x, int pos_y){
      this->pos_x = pos_x;
      this->pos_y = pos_y;    
    }

    void fly(Adafruit_NeoPixel * strip){
      if(this->pos_x < 29){
        this->setPixel(strip, this->color_off);
        this->pos_x++;
        this->setPixel(strip, this->bullet_color);
        return 0;
      }
      this->kill(strip);
      
    }

    void setPixel(Adafruit_NeoPixel * strip, int color[3]){
      strip->setPixelColor(coordsToPixelNum(this->pos_x, this->pos_y), color[0], color[1], color[2]);
    }

    void kill(Adafruit_NeoPixel * strip) {
      this->setPixel(strip, this->color_off);
      delete this;
    }

    int coordsToPixelNum(int x, int y) {
        int pixelNumber;
        if (y % 2 == 0) {
            pixelNumber = (y+1) * 30 - x - 1;
        } else {
            pixelNumber = y * 30 + x;
        }
        return pixelNumber;
    }
};

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
PlayerShip ship(3,7);
Bullet* bullets[3];
int bullet_amount = 3;

Adafruit_NeoPixel* stripPtr = &strip;
PlayerShip* shipPtr = &ship;

void setup() {
  strip.begin();
  ship.setPixel(stripPtr, ship.ship_color);
}

void loop() {
  if(ship.is_shooting) {
    bullets[0] = new Bullet(ship.cockpit_x, ship.cockpit_y);
  }

  for(byte i = 0; i < bullet_amount; i++){
    bullets[i]->fly(stripPtr);
  }
  
  ship.setPixel(stripPtr, ship.color_off);
  ship.fly(stripPtr);
  ship.setPixel(stripPtr, ship.ship_color);
  
  strip.show();
}
