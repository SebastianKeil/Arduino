#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 450
#define PIXEL_WIDTH = 30
#define PIXEL_LENGTH = 15

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 5

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define START_LEN = 4 //length of tail, without head

//TODO: delete fruit when new spawns == when it gets eaten
//TODO: make snake bigger after eating fruit
//Todo: Make sure the fruit can't spawn on the snake
//TODO: end of game screen

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GBR);

int head_x;
int head_y;
int tail[16];   //pixel number, not coordinates
int len;
int fruit;
bool fruitOnField = false;
int dir = RIGHT;

class snake {
    int head_x, head_y;
    int len;            //length of tail, without head
    int tail [16];       //TODO: add max_length which is given in constructor and is used instead of hard coded 16
    int dir;
    head_color = [0, 60, 255];
    tail_color = [150, 20, 255];

public:
    snake(int x, int y, int start_len){
        this.head_x = x;
        this.head_y = y;
        this.len = start_len;
        this.dir = RIGHT;
    };

    void advance() { //TODO: rename to calculate?
        //iterate over the snake from back to front, so:
        //i:     0  1  2  3   4-15 | len is 4
        //  [32][33,34,35,36, NUll] becomes
        //  [32][33,33,34,35, NULL]
        for (int i = this.len-1; i > 0; i--){
            this.tail[i] = this.tail[i-1]
        }
        // set first tail segment to head coordinates:
        // [32][32,33,34,35, NULL]
        this.tail[0] = coordsToPixelNum(this.head_x, this.head_y);

        //update head coordinates
        switch (this.dir) {
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

    bool isDead() {
        //check if head left the screen
        if (this.head_x < 0 || this.head_x > PIXEL_WIDTH-1 || this.head_y < 0 || this.head_y > PIXEL_LENGTH-1) {
            return true;
        }
        //check if snake hit itself
        for (int i = 0; i < len; i++){
            if (tail[i] == coordsToPixelNum(this.head_x, this.head_y)) return true;
        }
        return false;
    }

    void removePixel(Adafruit_NeoPixel strip){
        strip.setPixelColor(coordsToPixelNum(this.head_x, this.head_y), 0, 0, 0);
        for (int i = 0; i < len; i++) {
            strip.setPixelColor(tail[i], 0, 0, 0);
        }
    }

    void setPixel(Adafruit_NeoPixel strip, int colors[3]) {
        strip.setPixelColor(coordsToPixelNum(this.head_x, this.head_y), 0, 60, 255);
        for (int i = 0; i < len; i++) {
            strip.setPixelColor(tail[i], 150, 20*i, 255);
        }
    }

    void checkInputs(){
        if (digitalRead(UP_BUTTON) && (this.dir == LEFT || this.dir == RIGHT))
            this.dir = UP;
        if (digitalRead(DOWN_BUTTON) && (this.dir == LEFT || this.dir == RIGHT))
            this.dir = DOWN;
        if (digitalRead(RIGHT_BUTTON) && (this.dir == UP || this.dir == DOWN))
            this.dir = RIGHT;
        if (digitalRead(LEFT_BUTTON) && (this.dir == UP || this.dir == DOWN))
            this.dir = LEFT;
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
};

class fruit {
    int position;
    int color = [255, 255, 0];

    //TODO: idea: make a timer that lets fruits disappear after some time, so we can have different fruits worth more or less points -> MAX is BLOODORANGE

public:
    fruit(){
        this.position = (int) random(NUM_PIXELS-1);;
    }

    void setPixel(Adafruit_NeoPixel strip){
        strip.setPixelColor(this.position, color[0], color[1], color[2]);
    }
};

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
    checkInputs();
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

void checkInputs(){
    if (digitalRead(UP_BUTTON) && (dir == LEFT || dir == RIGHT))
        dir = UP;
    if (digitalRead(DOWN_BUTTON) && (dir == LEFT || dir == RIGHT))
        dir = DOWN;
    if (digitalRead(RIGHT_BUTTON) && (dir == UP || dir == DOWN))
        dir = RIGHT;
    if (digitalRead(LEFT_BUTTON) && (dir == UP || dir == DOWN))
        dir = LEFT;
}

void advanceSnake() { //TODO: rename to calculateSnake?
    //iterate over the snake from back to front, so:
    //i:     0  1  2  3   4-15 | len is 4
    //  [32][33,34,35,36, NUll] becomes
    //  [32][33,33,34,35, NULL]
    for (int i = len-1; i > 0; i--){
        tail[i] = tail[i-1]
    }
    // set first tail segment to head coordinates:
    // [32][32,33,34,35, NULL]
    tail[0] = coordsToPixelNum(head_x, head_y);

    //update head coordinates
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
