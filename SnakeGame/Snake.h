#ifndef Snake_h
#define Snake_h

#include <InteractiveMatrix.h>

template<uint16_t max_len>
  class Snake {
    public:
      InteractiveMatrix *matrix;
      struct Vector2D start;
      uint16_t start_len;
      struct Vector2D head;
      struct Vector2D removedTailSegment;
      struct Vector2D tail [max_len];
      uint16_t len;
      uint16_t direction;
      uint16_t new_direction; // for making the save movement work, e.g. cant move DOWN when current direction is UP

      // Colors
      uint16_t head_color = 30000;
      uint16_t tail_color = 5065;
      uint16_t dark_matter = 0;

      Snake(uint16_t start_x, uint16_t start_y, InteractiveMatrix *matrix, uint16_t start_len=4){
        this->matrix = matrix;
        this->start.x = start_x;
        this->start.y = start_y;
        this->start_len = start_len;
        this->createStartSnake();
      }

      void draw(){
        this->matrix->drawPixel(this->head.x, this->head.y, head_color);
        for (int i = 0; i < this->len; i++) {
          this->matrix->drawPixel(this->tail[i].x, this->tail[i].y, tail_color);
        }
        this->matrix->drawPixel(this->removedTailSegment.x, this->removedTailSegment.y, dark_matter);
      }

      void move(){
        //store the pixel number, where to turn of the color
        this->removedTailSegment = this->tail[this->len-1];
        //iterate over the snake from back to front, so:
        //i:     0  1  2  3   4-15 | len is 4
        //  [32][33,34,35,36, NUll] becomes
        //  [32][33,33,34,35, NULL]
        for (int i = this->len-1; i > 0; i--){
            this->tail[i] = this->tail[i-1];
        }
        // set first tail segment to head coordinates:
        // [32][32,33,34,35, NULL]
        this->tail[0] = this->head;

        
        // only move if direction is in 0..7, i.e. not 8 and thus a legit direction
        if (this->matrix->direction(false) < N_DIRECTIONS) {
          this->new_direction = this->matrix->direction(false);
          if((this->new_direction == UP) && (this->direction == LEFT || this->direction == RIGHT))
            this->direction = UP;
          if((this->new_direction == DOWN) && (this->direction == LEFT || this->direction == RIGHT))
            this->direction = DOWN;
          if((this->new_direction == RIGHT) && (this->direction == UP || this->direction == DOWN))
            this->direction = RIGHT;
          if((this->new_direction == LEFT) && (this->direction == UP || this->direction == DOWN))
            this->direction = LEFT; 
        }


        switch (this->direction) {
            case UP:
                this->head.y -= 1;
                break;
            case DOWN:
                this->head.y += 1;
                break;
            case RIGHT:
                this->head.x += 1;
                break;
            case LEFT:
                this->head.x -= 1;
                break;
        }
      }

      void eatFruit(){
        this->len++; 
      }

      bool isDead(){
        //check if head left the screen
        if (this->head.x < 0 || this->head.x > this->matrix->get_matrixWidth()-1 || this->head.y < 0 || this->head.y > this->matrix->get_matrixHeight()-1) {
            return true;
        }
        //check if snake hit itself
        for (int i = 0; i < this->len; i++){
            if (this->tail[i].x == this->head.x && this->tail[i].y == this->head.y) return true;
        }
        return false;
      }

      void createStartSnake(){
        this->head.x = this->start.x;
        this->head.y = this->start.y;
        for (int i=0; i<this->len; i++){
            this->tail[i].x = this->start.x;
            this->tail[i].y = this->start.y+(i+1);
        }
        this->len = start_len;
        this->direction = UP;
      }
  };

#endif