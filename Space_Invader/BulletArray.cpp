#include "Arduino.h"
#include "Led_Matrix.h"
#include <Adafruit_NeoPixel.h> 
#include "BulletArray.h"

//macros for led matrix
#define WIDTH 15
#define HEIGHT 30

BulletArray::BulletArray(){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      this->field[i][j] = 0;
    }
  }
} 

void BulletArray::shift(int shiftAmount){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      if(this->field[i][j] == 1 && j > 0){
        this->field[i][j + shiftAmount] = 1;
        this->field[i][j] = 0;
      }
      if(j == 0 && this->field[i][j + 1] == 1){
        this->field[i][j] = 1;
      }
      if(j == 0 && this->field[i][j] == 1){ // new if cond 
        this->field[i][j] = 0;
      }
    }
  }
}



void BulletArray::show(Adafruit_NeoPixel* stripPtr, LedMatrix* matrixPtr){
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      if(this->field[i][j] == 1 && j >= 0){ // new =
        stripPtr->setPixelColor(matrixPtr->coordsToPixelNum(i, j), 0, 255, 0);
      }
    }
  }
}
