#ifndef Bullet_h
#define Bullet_h

#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 

class Bullet{

  public:
  
  int x;
  int y;
  int dir_x;
  int dir_y;
  
  Bullet(int x, int y, int dir_x, int dir_y);
  void move();
  void show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr);
};

#endif
