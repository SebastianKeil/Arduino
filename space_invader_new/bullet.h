#ifndef bullet_h
#define bullet_h

#include <Vector.h>
#include "Arduino.h"
#include "Led_Matrix.h"

class bullet{

  public:
  move();
  show();

  private:
    
    int x;
    int y;
    int dir_x;
    int dir_y;
};

#endif
