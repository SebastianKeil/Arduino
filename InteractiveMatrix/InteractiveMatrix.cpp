#include <FastLED_NeoMatrix.h>
#include "InteractiveMatrix.h"


// for directions array
const uint8_t lowerThreshholdAnalogStick = 400;
const uint8_t upperThreshholdAnalogStick = 600;


// constructor for a single LED matrix
InteractiveMatrix::InteractiveMatrix(CRGB *leds, uint16_t matrix_width, uint16_t matrix_height, 
  uint8_t default_scheme): 
  FastLED_NeoMatrix(leds, matrix_width, matrix_height, default_scheme) {
    this->n_pixels = matrix_width * matrix_height;
  }


// Constructor for tiled LED matrices
InteractiveMatrix::InteractiveMatrix(CRGB *leds, uint16_t matrix_width, uint16_t matrix_height, uint8_t tX, uint8_t tY,
  uint8_t default_scheme):
  FastLED_NeoMatrix(leds, matrix_width, matrix_height, tX, tY, default_scheme) {
    this->n_pixels = matrix_width * matrix_height;
  }


void InteractiveMatrix::checkInputsAnalogStick(bool allowDiagonalMoves){
  // check the analog X and Y for input and write the mapped results in the directions array

	this->_zeroDirections(); // smooth controller input, e.g. when the last input was slightly larger as the current, desired input
	if(analogRead(ANAL_X) < lowerThreshholdAnalogStick) this->_directions[RIGHT]= map(analogRead(ANAL_X), 400, 0, 2, 10);
	if(analogRead(ANAL_X) > upperThreshholdAnalogStick) this->_directions[LEFT]= map(analogRead(ANAL_X), 700, 1023, 2, 10);
	if(analogRead(ANAL_Y) > upperThreshholdAnalogStick) this->_directions[UP]= map(analogRead(ANAL_Y), 700, 1023, 2, 10);
	if(analogRead(ANAL_Y) < lowerThreshholdAnalogStick) this->_directions[DOWN]= map(analogRead(ANAL_Y), 400, 0, 2, 10);

  if (allowDiagonalMoves){
    if(analogRead(ANAL_X) > upperThreshholdAnalogStick && analogRead(ANAL_Y) > upperThreshholdAnalogStick) this->_directions[UPLEFT]= map(analogRead(ANAL_X), 700, 1023, 2, 10) + map(analogRead(ANAL_Y), 700, 1023, 2, 10);
	  if(analogRead(ANAL_X) > upperThreshholdAnalogStick && analogRead(ANAL_Y) < lowerThreshholdAnalogStick) this->_directions[DOWNLEFT]= map(analogRead(ANAL_X), 700, 1023, 2, 10) + map(analogRead(ANAL_Y), 400, 0, 2, 10);
	  if(analogRead(ANAL_X) < lowerThreshholdAnalogStick && analogRead(ANAL_Y) < lowerThreshholdAnalogStick) this->_directions[DOWNRIGHT]= map(analogRead(ANAL_X), 400, 0, 2, 10) + map(analogRead(ANAL_Y), 400, 0, 2, 10);
	  if(analogRead(ANAL_X) < lowerThreshholdAnalogStick && analogRead(ANAL_Y) > upperThreshholdAnalogStick) this->_directions[UPRIGHT]= map(analogRead(ANAL_X), 400, 0, 2, 10) + map(analogRead(ANAL_Y), 700, 1023, 2, 10);
  }
}


int InteractiveMatrix::direction(bool allowDiagonalMoves){
  // TODO make this so one can pass a type of checkInputsCONTROLLERTYPE function
  // given the current directions, determine the direction that was intended by controller user

	this->checkInputsAnalogStick(allowDiagonalMoves);

	int maxInput = 0;
	int maxInputIdx = N_DIRECTIONS;

	for (int i = 0; i < N_DIRECTIONS; i++)
	{
		if (this->_directions[i] > maxInput)
		{
			maxInput = this->_directions[i];
			maxInputIdx = i;
		}
	}
	return maxInputIdx;
}


void InteractiveMatrix::_zeroDirections() {
  // reset the dierections matrix, for a fresh controller input read
  for (unsigned int i = 0; i < (sizeof(this->_directions)/sizeof(this->_directions[0])); i++) {
    this->_directions[i] = 0; 
  }
}