//#include <Adafruit_NeoPixel.h>

#define TRIGGER 3
#define BUTTOMS 4
#define ANALOG_X 0
#define ANALOG_y 1

//Adafruit_NeoPixel strip(450, 6, NEO_GBR);


void setup() {
  Serial.begin(9600);
    pinMode(BUTTOMS, INPUT_PULLUP);

//    strip.begin();
}

void loop() {
  Serial.print("ANALOG_X: ");
  Serial.println(analogRead(0));
  Serial.println("______________");
  Serial.print("ANALOG_Y: ");
  Serial.println(analogRead(1));
  Serial.println("______________");
  Serial.print("TRIGGER: ");
  Serial.println(digitalRead(TRIGGER));
  Serial.println("______________");
  Serial.print("BUTTOMS: ");
  Serial.println(digitalRead(BUTTOMS));
  Serial.println("______________");
  delay(500);
}
