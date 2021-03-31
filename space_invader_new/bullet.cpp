#include <Vector.h>
#include "Arduino.h"
#include "Led_Matrix.h"

public:
Bullet::Bullet(int x, int y, int dir_x, int dir_y){
    this.x = x;
    this.y = y;
    this.dir_x = dir_x;
    this.dir_y = dir_y;
} 

void Bullet::move(){
  this.x = this.x + this.dir_x;
  this.y = this.y + this.dir_y;
}

void Bullet::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->x, this->y), 0, 255, 0);
}
