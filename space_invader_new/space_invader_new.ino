#include <Led_Matrix.h>
#include <Adafruit_NeoPixel.h> 
#include "Bullet.h"

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

//define for game
#define START_MAGAZINE 5
#define BULLETS_COUNT_MAX 10



class PlayerShip{
  
  public:
    int cockpit_x;
    int cockpit_y;

    //stats
    int bulletAmount;

    PlayerShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr){
      this->cockpit_x = cockpit_x;
      this->cockpit_y = cockpit_y;
      this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
    }

    void fly(LedMatrix* matrixPtr){
      switch (matrixPtr->checkDirection()) {
        case LEFT:
          if (this->cockpit_x-1 > 0){
            this->cockpit_x--;
          }
          break;
        case RIGHT:
          if (this->cockpit_x+1 < WIDTH-1){
            this->cockpit_x++;
          }
          break;
        case UP:
          if (this->cockpit_y > 0){
            this->cockpit_y--;
          }
          break;
        case DOWN:
          if (this->cockpit_y+1 < HEIGHT-1){
            this->cockpit_y++;
          }
          break;
      }
      this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
    }


    void draw(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
      stripPtr->setPixelColor(this->_cockpitPixelNum, 250,250,0);
      stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y+1), 200,200,0);
      stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x+1, this->cockpit_y+1), 200,200,0);
      stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x-1, this->cockpit_y+1), 200,200,0);
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
  ship.draw(&strip, &matrix);
  strip.show(); 
}

void loop() {
  
  ship.fly(&matrix);
  
  strip.clear();
  
  ship.draw(&strip, &matrix);
  
  strip.show();
  delay(50);
}
