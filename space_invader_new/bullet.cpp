#include <Vector.h>
#include "Arduino.h"
#include "Led_Matrix.h"

bullet::bullet(int x, int y, int dir_x, int dir_y){
    this.x = x;
    this.y = y;
    this.dir_x = dir_x;
    this.dir_y = dir_y;
} 

void bullet::move(){
  this.x = this.x + this.dir_x;
  this.y = this.y + this.dir_y;
}

void bullet::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->x, this->y), 0, 255, 0);
}
