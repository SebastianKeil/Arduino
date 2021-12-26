#ifndef LedMatrix_h
#define LedMatrix_h

#include <FastLED_NeoMatrix.h>

// @TODO: when creating an InteractiveMatrix specify periphery objects, e.g. controller (maybe setter functions, e.g. matrix->setController())

// DOCUMENTATION from other classes down the inheritance tree
// -------------------------------------------------------------------------------------------------------------------
// drawing functions, e.g. fillRect: https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.h
// for description of the macros, that describe the matrix build, see: https://github.com/adafruit/Adafruit_NeoMatrix/blob/master/Adafruit_NeoMatrix.h
// online tool for ttf to gfx readable font header: https://rop.nl/truetype2gfx/
// -------------------------------------------------------------------------------------------------------------------

// arduino pins for analog reads of x and y directions
#define ANAL_X 0
#define ANAL_Y 1
#define TRIGGER 3
#define BUTTONS 4
// for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define UPRIGHT 4
#define DOWNRIGHT 5
#define DOWNLEFT 6
#define UPLEFT 7
#define N_DIRECTIONS 8

struct Vector2D {
  uint16_t x;
  uint16_t y;
};

class InteractiveMatrix : public FastLED_NeoMatrix {
  public:
    uint16_t n_pixels;

    // Constructor for single matrix
    InteractiveMatrix(CRGB *leds, uint16_t matrix_width, uint16_t matrix_height, 
      uint8_t matrixType = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);

    // Constructor for tiled matrices
    InteractiveMatrix(CRGB *leds, uint16_t matrix_width, uint16_t matrix_height, uint8_t tX, uint8_t tY,
      uint8_t matrixType = NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS +
                         NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_ROWS);

    void checkInputsAnalogStick(bool allowDiagonalMoves);

    int direction(bool allowDiagonalMoves);

    uint16_t get_matrixWidth(){
      return this->matrixWidth;
    }

    uint16_t get_matrixHeight(){
      return this->matrixHeight;
    }

  private:
    int _directions[9];

    void _zeroDirections();
};

#endif