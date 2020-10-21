#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 450

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 5

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GBR);

int head_x = 15;
int head_y = 8;
int tail[16];   //pixelnumb, no coords
int len = 4;
int fruit = 0;
int dir = RIGHT;

void setup() {
  Serial.begin(9600);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
 
  strip.begin();
  tail[0] = coordsToPixelNum(15, 7);
  tail[1] = coordsToPixelNum(15, 6);
  tail[2] = coordsToPixelNum(15, 5);
  tail[3] = coordsToPixelNum(15, 4);
  blackScreen();
  strip.show();
  randomSeed(analogRead(0));
  fruit = (int) random(449);
}

void loop() {
  if (digitalRead(UP_BUTTON) && (dir == LEFT || dir == RIGHT))
    dir = UP;
  if (digitalRead(DOWN_BUTTON) && (dir == LEFT || dir == RIGHT))
    dir = DOWN;
  if (digitalRead(RIGHT_BUTTON) && (dir == UP || dir == DOWN))
    dir = RIGHT;
  if (digitalRead(LEFT_BUTTON) && (dir == UP || dir == DOWN))
    dir = LEFT;

  if (SnakeIsDead()) resetGame();
  advanceSnake();
  displayAll();
  strip.show();
  delay(200);
}

void advanceSnake() {
  int tmp = tail[0];
  tail[0] = coordsToPixelNum(head_x, head_y);
  
  for (int i = 1; i < len; i++) {
    int itmp = tail[i];
    tail[i] = tmp;
    tmp = itmp;
  }

  switch (dir) {
    case UP:
      head_y -= 1;
      break;
    case DOWN:
      head_y += 1;
      break;
    case RIGHT:
      head_x += 1;
      break;
    case LEFT:
      head_x -= 1;
      break;
  }
}


boolean SnakeIsDead() {

  if (head_x < 0 || head_x > 29 || head_y < 0 || head_y > 14) {
    return true;
  }
  
  for (int i = 0; i < len; i++){
    if (tail[i] == coordsToPixelNum(head_x, head_y))return true;
  }
  
  return false;
}

void deleteSnake(){
  strip.setPixelColor(coordsToPixelNum(head_x, head_y), 0, 0, 0);
  for (int i = 0; i < len; i++) {
    strip.setPixelColor(tail[i], 0, 0, 0);
  }
}

void resetGame(){
    deleteSnake();
    head_x = 15;
    head_y = 7;
    tail[0] = coordsToPixelNum(15, 6);
    tail[1] = coordsToPixelNum(15, 5);
    tail[2] = coordsToPixelNum(15, 4);
    tail[3] = coordsToPixelNum(15, 3);
    len = 4;
    dir = RIGHT;
    fruit = (int) random(449);
    displayAll();
    delay(200);
}

void displayAll() {
  strip.setPixelColor(coordsToPixelNum(head_x, head_y), 0, 60, 255);
  for (int i = 0; i < len - 1; i++) {
    strip.setPixelColor(tail[i], 150, 20*i, 255);
    char message[16];
    sprintf(message, "%d = %d\n", coordsToPixelNum(15, 6), tail[i]);
  }
  
  strip.setPixelColor(tail[len - 1], 0, 0, 0);
  strip.setPixelColor(fruit, 255, 255, 0);
}

int coordsToPixelNum(int x, int y) {
  int pixelNumber = 0;

  if (y % 2 == 0) {
    pixelNumber = (y+1) * 30 - x -1;
  } else {
    pixelNumber = y * 30 + x;
  }
  return pixelNumber;
}

void blackScreen(){
  for (int x = 0; x < 30;  x++) {
    for (int y = 0; y < 15; y ++) {
      strip.setPixelColor(coordsToPixelNum(x, y), 0, 0, 0);
    }
    strip.show();
    
  }
}
