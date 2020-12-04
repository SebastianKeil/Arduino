#include "Arduino.h"
#include "Led_Matrix.h"

//for Arduino pins
#define ANAL_X 0
#define ANAL_Y 1


//for directions array
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

//for buttons
#define TRIGGER 3
#define BUTTONS 4




LedMatrix::LedMatrix(int numPixels, int width, int height)
{
	this->_numPixels = numPixels;
	this->_width = width;
	this->_height = height;
	for (int i = 0; i < (sizeof(this->_buttons)/sizeof(this->_buttons[0])); i++) { this->_buttons[i] = false; }
}	

int LedMatrix::coordsToPixelNum(int x, int y){
	int pixelNum;
	if (x%2 == 0)				//column downwards
	{
		pixelNum = 420 - x * this->_height + y;
	}else{						//column upwards
		pixelNum = 419 - (x - 1) * this->_height - y;
	}
	return pixelNum;



}

void LedMatrix::checkInputs(){
	for (int i = 0; i < (sizeof(this->_directions)/sizeof(this->_directions[0])); i++) {this->_directions[i] = 0; }
	if(analogRead(ANAL_X) < 350) this->_directions[LEFT]= map(analogRead(0), 400, 0, 2, 10);
    if(analogRead(ANAL_X) > 750) this->_directions[RIGHT]= map(analogRead(0), 700, 1023, 2, 10);
    if(analogRead(ANAL_Y) > 750) this->_directions[UP]= map(analogRead(1), 700, 1023, 2, 10);
    if(analogRead(ANAL_Y) < 350) this->_directions[DOWN]= map(analogRead(1), 400, 0, 2, 10);

    for (int i = 0; i < (sizeof(this->_directions)/sizeof(this->_directions[0])); i++)
    {
    	Serial.print(i); Serial.print(": ");
    	Serial.println(this->_directions[i]);
    	Serial.println();
    	
    }
    Serial.print("x: ");
	Serial.println(analogRead(ANAL_X));
	Serial.print("y: ");
	Serial.println(analogRead(ANAL_Y));
    Serial.println();

}
    

int LedMatrix::checkDirection(){

	this->checkInputs();

	int maxInput = 0;
	int maxInput_Index = 4;

	for (int i = 0; i < 4; i++)
	{
		if (this->_directions[i] > maxInput)
		{
			maxInput = this->_directions[i];
			maxInput_Index = i;
		}
	}
	return maxInput_Index;
}

void LedMatrix::checkButtons(){
	for (int i = 0; i < (sizeof(this->_buttons)/sizeof(this->_buttons[0])); i++) {this->_buttons[i] = false; }
	//for (int i = 0; i < sizeof(this->_buttons); i++) {Serial.println(this->_buttons[i]); }
	if (digitalRead(TRIGGER)) this->_buttons[0] = true;
	if (digitalRead(BUTTONS)) this->_buttons[1] = true;
	//for (int i = 0; i < sizeof(this->_buttons); i++) {Serial.println(this->_buttons[i]); }

}

bool LedMatrix::isPressed(int button){
	
	this->checkButtons();

	return this->_buttons[button];
}