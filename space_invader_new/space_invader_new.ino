#include <Led_Matrix.h>
#include <Adafruit_NeoPixel.h> 

//macros for led matrix
#define PIN 6
#define NUM_PIXELS 450
#define WIDTH 15  
#define HEIGHT 30


//for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

//macros for controller
#define TRIGGER 0
#define BUTTONS 1
#define ANALOG_X 0
#define ANALOG_y 1

class PlayerShip{
  public:
    int cockpit_x;
    int cockpit_y;

    PlayerShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr){
      this->cockpit_x = cockpit_x;
      this->cockpit_y = cockpit_y;
      this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
    }

    void fly(LedMatrix* matrixPtr){
      switch (matrixPtr->checkDirection()) {
        case LEFT:
          this->cockpit_x--;
          break;
        case RIGHT:
          this->cockpit_x++;
          break;
        case UP:
          this->cockpit_y--;
          break;
        case DOWN:
          this->cockpit_y++;
          break;
      }
      this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
    }

    int check_bounds(int x, int y) {
      return 0;
    }

    void draw(Adafruit_NeoPixel* stripPtr){
      stripPtr->setPixelColor(this->_cockpitPixelNum, 200,200,0);
    }

    void undraw(Adafruit_NeoPixel* stripPtr){
      
    }

    private:
      int _cockpitPixelNum;
};

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT);
PlayerShip ship(7, 25, &matrix);

void setup() {  
  Serial.begin(9600);
  strip.begin();
  ship.draw(&strip);
  strip.show(); 
}

void loop() {
  strip.setPixelColor(matrix.coordsToPixelNum(10, 15), 200,0,0);
  ship.fly(&matrix);
  strip.clear();
  ship.draw(&strip);
  strip.show();
  delay(50);
}
