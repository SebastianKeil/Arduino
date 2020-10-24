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
int directions[4];


void setup() {
  Serial.begin(9600);
    pinMode(BUTTONS, INPUT_PULLUP);

//    strip.begin();
}

void loop() {
  if (digitalRead(BUTTONS) == 1){
      //TODO Pause Menu?
      }

    left = 0;
    right = 0;
    down = 0;
    up = 0;
    
    if(analogRead(0) < 400) left = map(analogRead(0), 400, 0, 1, 10);
    if(analogRead(0) > 700) right = map(analogRead(0), 0, 700, 1, 10);
    if(analogRead(1) < 400) down = map(analogRead(1), 400, 0, 1, 10);
    if(analogRead(1) > 700) up = map(analogRead(1), 0, 700, 1, 10);
    
    }

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


    Serial.print("directions["); 
    for(byte i = 0; i < 4; i++){
      Serial.print(directions[i] + " "); 
      Serial.println("]");
    }

    int dir_max = directions[0];
    int dir_max_index = 0;
    for(byte i = 1; i < 4; i++){
      if(directions[i] > dir_max){ 
        dir_max = directions[i];
        dir_max_index = i;
      }
    }
    Serial.println("dir_max: " + dir_max);
    Serial.println("dir_max_index: " + dir_max_index);

    delay(500);

    
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
