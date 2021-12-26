#include "InteractiveMatrix.h"
#include <FastLED.h>
#include "pzim3x520pt7b.h"
#include "three_to_five0pt7b.h"
#include "three_to_five5pt7b.h"

#define PIN 6
#define matrix_width 17
#define matrix_height 12
#define NUMMATRIX (matrix_width * matrix_height)

CRGB matrixleds[NUMMATRIX];
InteractiveMatrix *matrix = new InteractiveMatrix(matrixleds, matrix_width, matrix_height, 
                                                  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);


int x    = matrix_width;
int pass = 0;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL,PIN>(matrixleds, NUMMATRIX); 
  matrix->begin();
  matrix->setFont(&three_to_five5pt7b);
  matrix->fillScreen(0);
  
}

const uint16_t colors[] = {
  matrix->Color(255, 0, 0), matrix->Color(0, 255, 0), matrix->Color(0, 0, 255) };


void loop() {
  int photo = analogRead(0);
  int temperatur = analogRead(1);
  Serial.println(photo);

  matrix->fillScreen(0);
  matrix->setTextColor(map(photo, 100, 900, 565, 12000));
  matrix->setCursor(2, map(photo, 100, 900, 5, 12));
  matrix->print(F("GAY"));
  matrix->show();
  delay(1000);
}
