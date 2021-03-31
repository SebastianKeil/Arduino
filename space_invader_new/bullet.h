#ifndef bullet_h
#define bullet_h

#include <Vector.h>
#include "Arduino.h"
#include "Led_Matrix.h"

class Bullet{

  public:
  Bullet(int x, int y, int dir_x, int dir_y);
  move();
  show();

  private:
    
    int x;
    int y;
    int dir_x;
    int dir_y;
};

#endif
