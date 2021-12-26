#ifndef Fruit_h
#define Fruit_h

#include <InteractiveMatrix.h>

class Fruit {
  struct Vector2D pos;

  //TODO: fruit ideas
  //ideas: move fruit und time fruit

  public:
    InteractiveMatrix *matrix;
    uint16_t color = 35000;

    Fruit(InteractiveMatrix *matrix){
      this->matrix = matrix;
      this->resetPos();
    }

    void resetPos(){
      this->pos.x = (int) random(this->matrix->get_matrixWidth());
      this->pos.y = (int) random(this->matrix->get_matrixHeight());
    }

    void draw(uint16_t color=35000){
      this->matrix->drawPixel(this->pos.x, this->pos.y, color);
    }

    void undraw(){
      this->draw(0);
    }

    bool isEaten(uint16_t x, uint16_t y) {
      if (x == this->pos.x && y == this->pos.y) return true;
      return false;
    }
};

#endif