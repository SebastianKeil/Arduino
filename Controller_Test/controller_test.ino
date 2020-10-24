//#include <Adafruit_NeoPixel.h>

#define TRIGGER 3
#define BUTTONS 4
#define ANALOG_X 0
#define ANALOG_y 1

//Adafruit_NeoPixel strip(450, 6, NEO_GBR);
int left;
int right;
int up;
int down;
int directions[5];


void setup() {
  Serial.begin(9600);
    pinMode(BUTTONS, INPUT_PULLUP);

//    strip.begin();
}

void loop() {
  if (digitalRead(BUTTONS) == 1){
      //TODO Pause Menu?
      }

    left = 1;
    right = 1;
    down = 1;
    up = 1;
    
    if(analogRead(0) < 400) left = map(analogRead(0), 400, 0, 2, 10);
    if(analogRead(0) > 700) right = map(analogRead(0), 700, 1023, 2, 10);
    if(analogRead(1) < 400) down = map(analogRead(1), 400, 0, 2, 10);
    if(analogRead(1) > 700) up = map(analogRead(1), 700, 1023, 2, 10);
    
    Serial.println("");
    Serial.print("left: ");
    Serial.println(left);
    Serial.print("right: ");
    Serial.println(right);
    Serial.print("down: ");
    Serial.println(down);
    Serial.print("up: "); 
    Serial.println(up);


    directions[0] = left;
    directions[1] = right;
    directions[2] = down;
    directions[3] = up;
    directions[4] = 0;


    Serial.print("directions["); 
    for(byte i = 0; i < 4; i++){
      Serial.print(directions[i]); 
      if(i < 3) Serial.print(", ");
    }
    Serial.println("]");

    int dir_max = directions[0];
    int dir_max_index = 4;
    
    for(byte i = 1; i < 4; i++){
      if(directions[0] > 1) dir_max_index = 0;
      if(directions[i] > dir_max){ 
        dir_max = directions[i];
        dir_max_index = i;
      }
    }
    Serial.print("dir_max: ");
    Serial.println(dir_max);
    Serial.print("dir_max_index: ");
    Serial.println(dir_max_index);
    Serial.print("that means: ");
    
    switch (dir_max_index){
      case 0:
        Serial.println("left");
        break;
      case 1:
        Serial.println("right");
        break;
      case 2:
        Serial.println("down");
        break;
      case 3:
        Serial.println("up");
        break;
      case 4:
        Serial.println("no input");
        break;
    }

    delay(1000);

    
//  Serial.print("ANALOG_X: ");
//  Serial.println(analogRead(0));
//  Serial.println("______________");
//  Serial.print("ANALOG_Y: ");
//  Serial.println(analogRead(1));
//  Serial.println("______________");
//  Serial.print("TRIGGER: ");
//  Serial.println(digitalRead(TRIGGER));
//  Serial.println("______________");
//  Serial.print("BUTTOMS: ");
//  Serial.println(digitalRead(BUTTOMS));
//  Serial.println("______________");
//  delay(500);
}
