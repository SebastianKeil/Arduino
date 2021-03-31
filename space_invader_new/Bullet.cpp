#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 
#include "Bullet.h"

#define HEIGHT 30

Bullet::Bullet(int x, int y, int dir_x, int dir_y){
    this->x = x;
    this->y = y;
    this->dir_x = dir_x;
    this->dir_y = dir_y;
} 

void Bullet::move(){
  Serial.println(this->y);
  if(this->y >= 0 && this->y <= 30){
    Serial.println("HELO");
    this->x += this->dir_x;
    this->y += this->dir_y;
  }
}

void Bullet::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(this->x, this->y), 0, 255, 0);
}
