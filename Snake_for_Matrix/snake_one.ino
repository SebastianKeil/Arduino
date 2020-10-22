#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 450

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 5

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define START_LEN = 4

//TODO: delete fruit when new spawns == when it gets eaten
//TODO: make snake bigger after eating fruit
//Todo: Make sure the fruit can't spawn on the snake

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GBR);

int head_x;
int head_y;
int tail[16];   //pixel number, not coordinates
int len;
int fruit;
bool fruitOnField = false;
int dir = RIGHT;

void setup() {
    Serial.begin(9600);
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
 
    strip.begin();
    blackScreen();
    strip.show();
    resetGame();
    strip.show();
    randomSeed(analogRead(0));
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

  if (SnakeIsDead()) {
      deleteSnake();
      resetGame();
  }
  advanceSnake();
  setSnakePixel();
  setFruitPixel();
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


bool SnakeIsDead() {
    //check if head left the screen
    if (head_x < 0 || head_x > 29 || head_y < 0 || head_y > 14) {
    return true;
    }
    //check if snake hit itself
    for (int i = 0; i < len; i++){
        if (tail[i] == coordsToPixelNum(head_x, head_y)) return true;
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
    head_x = 15;
    head_y = 7;
    len = START_LEN;
    for(int i = 0; i < len; i++){
        tail[i] = coordsToPixelNum(15, head_y-1-i);
    }
    dir = RIGHT;
    setSnakePixel();
    delay(200);
}

void setSnakePixel() {
  strip.setPixelColor(coordsToPixelNum(head_x, head_y), 0, 60, 255);
  for (int i = 0; i < len; i++) {
    strip.setPixelColor(tail[i], 150, 20*i, 255);
  }
  //TODO: why is the last tail segment set to black here?
  strip.setPixelColor(tail[len - 1], 0, 0, 0);
}

int coordsToPixelNum(int x, int y) {
  int pixelNumber;

  if (y % 2 == 0) {
    pixelNumber = (y+1) * 30 - x -1;
  } else {
    pixelNumber = y * 30 + x;
  }
  return pixelNumber;
}

void blackScreen(){
  for (int i = 0; i < NUM_PIXELS;  i++) {
      strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();

}

void setFruitPixel() {
    fruit = (int) random(NUM_PIXELS-1);
    strip.setPixelColor(fruit, 255, 255, 0);
}
