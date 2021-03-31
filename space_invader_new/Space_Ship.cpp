#include "Space_Ship.h"
#include "Arduino.h"

//for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

//for buttons
#define TRIGGER 3
#define BUTTONS 4

SpaceShip::SpaceShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr){
  this->cockpit_x = cockpit_x;
  this->cockpit_y = cockpit_y;
  this->_cockpitPixelNum = matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y);
}

void SpaceShip::move(LedMatrix* matrixPtr){
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

void SpaceShip::shoot(LedMatrix* matrixPtr){
  this -> bullets.push_back(new Bullet(this->cockpit_x, this->cockpit_y+1, 0, 1))
}

void SpaceShip::show(Adafruit_NeoPixel* stripPtr, LedMatrix *matrixPtr){
  stripPtr->setPixelColor(this->_cockpitPixelNum, 250,250,0);
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x, this->cockpit_y+1), 200,200,0);
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x+1, this->cockpit_y+1), 200,200,0);
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->cockpit_x-1, this->cockpit_y+1), 200,200,0);
}
