#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_PIXELS 450
#define PIXEL_WIDTH 30  
#define PIXEL_LENGTH 15

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define RIGHT_BUTTON 4
#define LEFT_BUTTON 5

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define START_X 10
#define START_Y 7
#define START_LEN 4 //length of tail, without head
#define MAX_TAIL_LENGTH 16

//TODO: check inputs makes mistake, e.g. we can still go left, when already going right 
//TODO: Make sure the fruit can't spawn on the snake
// something like while(fruit.pos == head || tail[1] || ...) do ( fruit.pos = rand(0,499)
//TODO: start of game screen
// display game name, start message (and high score)
//TODO: end of game screen
// display game over, number of points, and restart message

class Snake {
    public: int head_x, head_y;
    int len;                            //length of tail, without head
    public: int tail [MAX_TAIL_LENGTH];         //TODO: add max_length which is given in constructor and is used instead of hard coded 16
    int removedTailSegment;
    int dir;
    int head_color[3] = {0, 60, 255};
    int tail_color[3] = {150, 20, 255};

public:
    Snake(int x, int y, int start_len){
        this->head_x = x;
        this->head_y = y;
        this->len = start_len;
        this->tail[0] = coordsToPixelNum(this->head_x-1, this->head_y);
        for (int i=1; i<this->len; i++){
            this->tail[i] = this->coordsToPixelNum(this->head_x-(i+1), this->head_y);
        }
        this->dir = RIGHT;
    };

    void advance() {
        //store the pixel number, where to turn of the color
        this->removedTailSegment = this->tail[len-1];
        //iterate over the snake from back to front, so:
        //i:     0  1  2  3   4-15 | len is 4
        //  [32][33,34,35,36, NUll] becomes
        //  [32][33,33,34,35, NULL]
        for (int i = this->len-1; i > 0; i--){
            this->tail[i] = this->tail[i-1];
        }
        // set first tail segment to head coordinates:
        // [32][32,33,34,35, NULL]
        this->tail[0] = this->headPixelNum();

        //check inputs and then update head coordinates
        //this->checkInputs();
        switch (this->dir) {
            case UP:
                this->head_y -= 1;
                break;
            case DOWN:
                this->head_y += 1;
                break;
            case RIGHT:
                this->head_x += 1;
                break;
            case LEFT:
                this->head_x -= 1;
                break;
        }
    }

    void eatFruit(){
        this->len++; 
    }

    bool isDead() {
        //check if head left the screen
        if (this->head_x < 0 || this->head_x > PIXEL_WIDTH-1 || this->head_y < 0 || this->head_y > PIXEL_LENGTH-1) {
            return true;
        }
        //check if snake hit itself
        for (int i = 0; i < this->len; i++){
            if (tail[i] == this->headPixelNum()) return true;
        }
        return false;
    }

    void removePixel(Adafruit_NeoPixel * strip){                                       //give a pointer to our strip object
        strip->setPixelColor(this->headPixelNum(), 0, 0, 0);
        for (int i = 0; i < len; i++) {
            strip->setPixelColor(tail[i], 0, 0, 0);
        }
    }

    void resetPosition(){
        this->head_x = START_X;
        this->head_y = START_Y;
        this->len = START_LEN;
        this->tail[0] = this->coordsToPixelNum(this->head_x-1, this->head_y);
        for (int i=1; i<this->len; i++){
            this->tail[i] = this->coordsToPixelNum(this->head_x-(i+1), this->head_y);
        }
        this->dir = RIGHT;
    }

    void setPixel(Adafruit_NeoPixel * strip) {
        strip->setPixelColor(this->headPixelNum(), 0, 60, 255);
        for (int i = 0; i < this->len; i++) {
            strip->setPixelColor(this->tail[i], 150, 20*i, 255);
        }
        strip->setPixelColor(this->removedTailSegment, 0, 0, 0);
    }

    void checkInputs(){
        if (digitalRead(UP_BUTTON) && (this->dir == LEFT || this->dir == RIGHT))
            this->dir = UP;
        if (digitalRead(DOWN_BUTTON) && (this->dir == LEFT || this->dir == RIGHT))
            this->dir = DOWN;
        if (digitalRead(RIGHT_BUTTON) && (this->dir == UP || this->dir == DOWN))
            this->dir = RIGHT;
        if (digitalRead(LEFT_BUTTON) && (this->dir == UP || this->dir == DOWN))
            this->dir = LEFT;
    }

    int coordsToPixelNum(int x, int y) {
        int pixelNumber;
        if (y % 2 == 0) {
            pixelNumber = (y+1) * 30 - x - 1;
        } else {
            pixelNumber = y * 30 + x;
        }
        return pixelNumber;
    }

    int headPixelNum() {
        return this->coordsToPixelNum(this->head_x, this->head_y);
    }
};

class Fruit {
    int position;
    int color[3] = {255, 255, 0};

    //TODO: fruit ideas
    //ideas: move fruit und time fruit

public:
    Fruit(){
        this->position = (int) random(NUM_PIXELS-1);
    }

    void resetPosition(){
        this->position = (int) random(NUM_PIXELS-1);
    }

    void setPixel(Adafruit_NeoPixel * strip){
        strip->setPixelColor(this->position, color[0], color[1], color[2]);
    }

    void removePixel(Adafruit_NeoPixel * strip){
        strip->setPixelColor(this->position, 0, 0, 0);
    }

    bool isEaten(Snake * snake) {
        if (snake->headPixelNum() == this->position) return true;
        return false;
    }
};

// game objects
Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
            Snake snake(START_X, START_Y, START_LEN);
            Fruit fruit;

//pointers to these objects
Adafruit_NeoPixel * stripPtr = &strip;
            Snake * snakePtr = &snake;
            Fruit * fruitPtr = &fruit;

void resetGame(Snake * snake, Fruit * fruit, Adafruit_NeoPixel * strip){
    snake->resetPosition();
    snake->setPixel(strip);
    
    fruit->resetPosition();
    fruit->setPixel(strip);
    strip->show(); 
    
}


void setup() {
    Serial.begin(9600);
    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
 
    strip.begin();
    strip.clear();
    strip.show();
    resetGame(snakePtr, fruitPtr, stripPtr);
    randomSeed(analogRead(0));
}


void loop() {
    snake.advance();
    snake.setPixel(stripPtr);
    if( snake.isDead() ) {
        snake.removePixel(stripPtr);
        fruit.removePixel(stripPtr);
        resetGame(snakePtr, fruitPtr, stripPtr);
    }
    if( fruit.isEaten(snakePtr) ){
        fruit.removePixel(stripPtr);
        fruit.resetPosition();
        snake.eatFruit();
        snake.setPixel(stripPtr);
        fruit.setPixel(stripPtr);
    }

    strip.show();
    delay(200);
}
