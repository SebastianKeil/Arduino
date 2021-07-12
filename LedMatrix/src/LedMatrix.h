/*
	lead_matrix.h - Library for the led matrix which
	inlcudes mapping (x,y) coordinates to the corresponding
	pixel number of an adafruitNeoPixel led strip as well as
	checking the inputs of the controller.
*/
#ifndef LedMatrix_h
#define LedMatrix_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class LedMatrix{

	public:
		LedMatrix(int numPixels, int width, int height, Adafruit_NeoPixel* stripPtr);
		void begin();
		void show();
		void clear();
		int coordsToPixelNum(int x, int y);
		void drawDigit(int digit, int x, int y, int alpha=1);
		void drawNumber(String number, int x, int y, int alpha=1);
		void drawLetter(char letter, int x, int y, int alpha=1);
		void drawWord(String word, int x, int y, int alpha=1);
		void checkInputs();
		int checkDirection();
		void checkButtons();
		bool isPressed(int button);

	protected:
		Adafruit_NeoPixel* stripPtr;

	private:
		int _numPixels;
		int _width;
		int _height;

		int _directions[9];
		bool _buttons[2];

		// digits of size 3x5
		void _draw0(int x, int y, int alpha=1);
		void _draw1(int x, int y, int alpha=1);
		void _draw2(int x, int y, int alpha=1);
		void _draw3(int x, int y, int alpha=1);
		void _draw4(int x, int y, int alpha=1);
		void _draw5(int x, int y, int alpha=1);
		void _draw6(int x, int y, int alpha=1);
		void _draw7(int x, int y, int alpha=1);
		void _draw8(int x, int y, int alpha=1);
		void _draw9(int x, int y, int alpha=1);

		// letters of type 5x5
		void _drawChar(bool (&charArray)[5][5], int x, int y, int alpha=1);

		bool _A[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,1,1,1,1},
										{1,0,0,0,1}
										};

		bool _B[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,1},
										{1,1,1,1,0},
										{1,0,0,0,1},
										{1,1,1,1,1}
										};

		bool _C[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,0},
										{1,0,0,0,0},
										{1,0,0,0,0},
										{1,1,1,1,1}
										};

		bool _D[5][5] = {
										{1,1,1,1,0},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,1,1,1,0}
										};

		bool _E[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,0},
										{1,1,1,1,0},
										{1,0,0,0,0},
										{1,1,1,1,1}
										};

		bool _F[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,0},
										{1,1,1,1,0},
										{1,0,0,0,0},
										{1,0,0,0,0}
										};

		bool _G[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,0},
										{1,0,0,1,1},
										{1,0,0,0,1},
										{1,1,1,1,1}
										};

		bool _H[5][5] = {
										{1,0,0,0,1},
										{1,0,0,0,0},
										{1,1,1,1,1},
										{1,0,0,0,1},
										{1,0,0,0,1}
										};

		bool _I[5][5] = {
										{1,1,1,1,1},
										{0,0,1,0,0},
										{0,0,1,0,0},
										{0,0,1,0,0},
										{1,1,1,1,1}
										};

		bool _J[5][5] = {
										{0,0,0,1,1},
										{0,0,0,0,1},
										{0,0,0,0,1},
										{1,0,0,0,1},
										{1,1,1,1,1}
										};

		bool _K[5][5] = {
										{1,0,0,0,1},
										{1,0,0,1,0},
										{1,1,1,0,0},
										{1,0,0,1,0},
										{1,0,0,0,1}
										};

		bool _L[5][5] = {
										{1,0,0,0,0},
										{1,0,0,0,0},
										{1,0,0,0,0},
										{1,0,0,0,0},
										{1,1,1,1,1}
										};

		bool _M[5][5] = {
										{1,0,0,0,1},
										{1,1,0,1,1},
										{1,0,1,0,1},
										{1,0,0,0,1},
										{1,0,0,0,1}
										};

		bool _N[5][5] = {
										{1,0,0,0,1},
										{1,1,0,0,1},
										{1,0,1,0,1},
										{1,0,0,1,1},
										{1,0,0,0,1}
										};

		bool _O[5][5] = {
										{0,1,1,1,0},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{0,1,1,1,0}
										};

		bool _P[5][5] = {
										{1,1,1,1,0},
										{1,0,0,0,1},
										{1,1,1,1,0},
										{1,0,0,0,0},
										{1,0,0,0,0}
										};

		bool _Q[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,1,1,1,1},
										{0,0,1,0,0}
										};

		bool _R[5][5] = {
										{1,1,1,1,0},
										{1,0,0,0,1},
										{1,1,1,1,0},
										{1,0,0,0,1},
										{1,0,0,0,1}
										};

		bool _S[5][5] = {
										{1,1,1,1,1},
										{1,0,0,0,0},
										{1,1,1,1,1},
										{0,0,0,0,1},
										{1,1,1,1,1}
										};

		bool _T[5][5] = {
										{1,1,1,1,1},
										{0,0,1,0,0},
										{0,0,1,0,0},
										{0,0,1,0,0},
										{0,0,1,0,0}
										};

		bool _U[5][5] = {
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,1,1,1,1}
										};

		bool _V[5][5] = {
										{1,0,0,0,1},
										{1,0,0,0,1},
										{0,1,0,1,0},
										{0,1,0,1,0},
										{0,0,1,0,0}
										};

		bool _W[5][5] = {
										{1,0,0,0,1},
										{1,0,0,0,1},
										{1,0,1,0,1},
										{1,0,1,0,1},
										{0,1,0,1,0}
										};

		bool _X[5][5] = {
										{1,0,0,0,1},
										{0,1,0,1,0},
										{0,0,1,0,0},
										{0,1,0,1,0},
										{1,0,0,0,1}
										};

		bool _Y[5][5] = {
										{1,0,0,0,1},
										{1,0,0,0,1},
										{0,1,0,1,0},
										{0,0,1,0,0},
										{0,0,1,0,0}
										};

		bool _Z[5][5] = {
										{1,1,1,1,1},
										{0,0,0,1,0},
										{0,0,1,0,0},
										{0,1,0,0,0},
										{1,1,1,1,1}
										};
};


#endif
