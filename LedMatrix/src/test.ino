#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <LedMatrix.h>


//macros for led matrix
#define PIN 6
#define NUM_PIXELS 450
#define WIDTH 15
#define HEIGHT 30

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GBR);
LedMatrix matrix(NUM_PIXELS, WIDTH, HEIGHT, &strip);


//sd test
#include <SD.h>
#include <SPI.h>

const int CS_PIN = 53; // chip select

File root;

File file;

File scores;


void setup() {
  matrix.begin();
  matrix.clear();
  matrix.drawWord("GG", 2, 5);
  matrix.drawNumber("66", 2, 12);
  matrix.show();
  matrix.clear();
  matrix.show();
  delay(250);

  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:

  // while (!Serial);
  //
  // Serial.print("Initializing SD card...");
  //
  // if (!SD.begin(CS_PIN)) {
  //
  //   Serial.println("initialization failed. Things to check:");
  //
  //   Serial.println("1. is a card inserted?");
  //
  //   Serial.println("2. is your wiring correct?");
  //
  //   Serial.println("3. did you change the chipSelect pin to match your shield or module?");
  //
  //   Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
  //
  //   while (true);
  // }
  //
  // Serial.println("initialization done.");
  //
  // root = SD.open("/");
  //
  // printDirectory(root, 0);
  //
  // root.close();
  //
  // Serial.println("done!");
  //
  // Serial.println("\nOpen scores file...");
  // scores = SD.open("/SNAKE.TXT", FILE_WRITE);
  //
  // //writeToFile("GLN    66", scores);
  //
  // readLine(scores);
  //
  // Serial.println("\nClosing scores file...");
  // scores.close();
}


void loop() {
  String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for(unsigned int i=0; i<alphabet.length(); i++){
    matrix.drawLetter(alphabet[i], int 5, int 12);
  }
}


void printDirectory(File dir, int numTabs) {

  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {

      // no more files

      break;

    }

    for (uint8_t i = 0; i < numTabs; i++) {

      Serial.print('\t');

    }

    Serial.print(entry.name());

    if (entry.isDirectory()) {

      Serial.println("/");

      printDirectory(entry, numTabs + 1);

    } else {

      // files have sizes, directories do not

      Serial.print("\t\t");

      Serial.println(entry.size(), DEC);

    }

    entry.close();

  }
}

void initializeSD(){
  Serial.print("Initializing SD card...");

  if (!SD.begin(CS_PIN)) {

    Serial.println("initialization failed!");

    while (1);

  }

  Serial.println("initialization done.");
}

int createFile(char filename[]){
  file = SD.open(filename, FILE_WRITE);

  if (file) {
    Serial.println("File created successfully.");
    return 1;
  } else {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[], File file){
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile(File file){
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}

int openFile(char filename[]){
  file = SD.open(filename);
  if (file) {
    Serial.println("File opened with success!");
    return 1;
  } else {
    Serial.println("Error opening file...");
    return 0;
  }
}

String readLine(File file){
  String received = "";
  char ch;
  while (file.available()){
    ch = file.read();
    if (ch == '\n'){
      return String(received);
    } else {
      received += ch;
    }
  }
  return "";
}
