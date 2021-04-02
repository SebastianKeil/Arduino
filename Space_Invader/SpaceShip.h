#ifndef SpaceShip_h
#define SpaceShip_h	

#include "Arduino.h"
#include "BulletArray.h"
#include <Vector.h>
#include <Adafruit_NeoPixel.h>
#include <Led_Matrix.h>

#define MAX_BULLETS 10

class SpaceShip{

	public:
    int cockpit_x;
    int cockpit_y;
		BulletArray bullets;
    int shape;
    int weapon;
   
		SpaceShip(int cockpit_x, int cockpit_y, LedMatrix* matrixPtr, int shape=0, int weapon=0);
    void move(LedMatrix* matrixPtr);
		void shoot(LedMatrix* matrixPtr);
    void show(Adafruit_NeoPixel* stripPtr, LedMatrix *matrixPtr);
    int getBulletAmount();

	private:
    int _cockpitPixelNum;
    int _bulletAmount;
};

#endif
