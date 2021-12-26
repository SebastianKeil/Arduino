#include <InteractiveMatrix.h>
#include <three_to_five5pt7b.h>
#include "Snake.h"
#include "Fruit.h"
#include <FastLED.h>

#define PIN 6
#define matrix_width 17
#define matrix_height 12
#define N_PIXELS (matrix_width * matrix_height)


CRGB matrixleds[N_PIXELS];
InteractiveMatrix *matrix = new InteractiveMatrix(matrixleds, matrix_width, matrix_height, 
                                                  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

Snake< N_PIXELS > *snake = new Snake< N_PIXELS >(8, 5, matrix, 2);
Fruit *fruit = new Fruit(matrix);

uint16_t currentScore = 0;
uint16_t highScore = 0;

void setup() {
  pinMode(TRIGGER, INPUT_PULLUP);
  
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL,PIN>(matrixleds, N_PIXELS); 
  
  matrix->begin();
  matrix->setFont(&three_to_five5pt7b);
  fruit->draw();
  snake->draw();
  matrix->show();
}

void loop() {
  snake->move();
  snake->draw(); // TODO check this implementation

  if( snake->isDead() ) {
        matrix->clear();
        matrix->show();
        
        if (currentScore > highScore) {
          highScore = currentScore;
        }
        
        matrix->setCursor(1, 4);
        matrix->print("You  " + String(currentScore));
        
        matrix->show();
        delay(1250);
        currentScore = 0;
        matrix->clear();
        matrix->show();

        matrix->setCursor(1, 4);
        matrix->print("Top  " + String(highScore));
        matrix->show();
        delay(1250);
        matrix->clear();
        matrix->show();
        
        snake->createStartSnake();
        snake->draw();
        fruit->resetPos();
        fruit->draw();
    }

  if( fruit->isEaten(snake->head.x, snake->head.y) ){
    fruit->undraw();
    fruit->resetPos();
    snake->eatFruit();
    snake->draw();
    fruit->draw();
    currentScore++;
  }

  matrix->show(); // TODO check this implementation
  delay(200);
}