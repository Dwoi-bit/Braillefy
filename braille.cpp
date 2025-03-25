#include <ESP32Servo.h>
#include <Stepper.h>

void rollPaper();
void clearServos();
void printBraille(String Braille, bool isCapital, bool isNumber);

Servo Servos[6]; // Define an array of 6 Servo objects
bool waitingForInput = true;
const int IN1 = 27;
const int IN2 = 26;
const int IN3 = 25;
const int IN4 = 33;

// Servo pins (modify based on actual wiring)
const int ServoPins[6] = {15, 13, 19, 16, 21, 14};



void setup() {
  Serial.begin(9600); // Use a higher baud rate for ESP32
  // Attach servos to their respective pins
  for (int i = 0; i < 6; i++) {
    Servos[i].attach(ServoPins[i], 500, 2500);
  };
  clearServos();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  String input = "";
  String braille = "";
  bool isCapital = false;
  bool isNumber = false;
  if(waitingForInput) {
    Serial.println("Enter text to convert: ");
    waitingForInput = false;
  };
  
  if (Serial.available() > 0) {    
    input = Serial.readString();  
    input.trim();
    waitingForInput = true;
    Serial.println(input);
    for (int i = 0; i < input.length(); i++) {
      char inputChar = input[i];
      Serial.print("Doing character ");
      Serial.println(inputChar);
      if (isUpperCase(inputChar)) {
        isCapital = true;
        inputChar = tolower(inputChar);
      } else {
        isCapital = false;
      };
      isNumber = isDigit(inputChar);
      Serial.println(isNumber);
      switch (inputChar) {
        case 'a': braille = "100000"; break;
        case 'b': braille = "101000"; break;
        case 'c': braille = "110000"; break;
        case 'd': braille = "110100"; break;
        case 'e': braille = "100100"; break;
        case 'f': braille = "111000"; break;
        case 'g': braille = "111100"; break;
        case 'h': braille = "101100"; break;
        case 'i': braille = "011000"; break;
        case 'j': braille = "011100"; break;
        case 'k': braille = "100010"; break;
        case 'l': braille = "101010"; break;
        case 'm': braille = "110010"; break;
        case 'n': braille = "110110"; break;
        case 'o': braille = "100110"; break;
        case 'p': braille = "111010"; break;
        case 'q': braille = "111110"; break;
        case 'r': braille = "101110"; break;
        case 's': braille = "011010"; break;
        case 't': braille = "011110"; break;
        case 'u': braille = "100011"; break;
        case 'v': braille = "101011"; break;
        case 'w': braille = "011101"; break;
        case 'x': braille = "110011"; break;
        case 'y': braille = "110111"; break;
        case 'z': braille = "100111"; break;
        case '0': braille = "011100"; break;
        case '1': braille = "100000"; break;
        case '2': braille = "101000"; break;
        case '3': braille = "110000"; break;
        case '4': braille = "110100"; break;
        case '5': braille = "100100"; break;
        case '6': braille = "111000"; break;
        case '7': braille = "111100"; break;
        case '8': braille = "101100"; break;
        case '9': braille = "011000"; break;
        case ' ': braille = "111111"; break;
        default: braille = "000000"; break;
      };
      Serial.print("braille printing now is ");
      Serial.print(braille);
    printBraille(braille, isCapital, isNumber);
    delay(500);
    };
  };
}
void rollPaper() {
  for(int i = 0; i < 150; i++) {
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    delay(5);
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    delay(5);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    delay(5);
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    delay(5);
  };
}

void clearServos() {
   Servos[0].write(90);
   Servos[1].write(45);
   delay(200);
   Servos[2].write(90);
   Servos[3].write(30);
   delay(200);
   Servos[4].write(90);
   Servos[5].write(20);
   delay(200);
}

void printBraille(String Braille, bool isCapital, bool isNumber) {
  bool toClear = false;

  if (isCapital) {
    Servos[5].write(20); // push in 
    delay(100);
    Servos[5].write(90); // push out
    delay(100);
    clearServos();
    delay(100);
    rollPaper();
    delay(200);
  }

  if (isNumber) {
    Serial.println("I am here");
    Servos[1].write(45);
    Servos[3].write(30);
    delay(100);
    Servos[4].write(90);
    Servos[5].write(20);
    delay(100);
    Servos[1].write(90);
    Servos[3].write(90);
    delay(100);
    Servos[4].write(30);
    Servos[5].write(90);
    delay(100);
    clearServos();
    delay(200);
    rollPaper();
    delay(200);
  }

  // for (int i = 0; i < 6; i++) {
  //   if (Braille[i] == '1') {
  //     Servos[i].write(0);
  //     toClear = true;
  //   }
  // }
  if(Braille[0] == '1' && Braile != "111111") {
    Servos[0].write(45);
    toClear = true;
    delay(200);
  };

  if(Braille[1] == '1' && Braile != "111111") {
    Servos[1].write(90);
    toClear = true;
    delay(200);
  };
  
  if(Braille[2] == '1' && Braile != "111111") {
    Servos[2].write(30);
    toClear = true;
    delay(200);
  };
  
  if(Braille[3] == '1' && Braile != "111111") {
    Servos[3].write(90);
    toClear = true;
    delay(200);
  };

  if(Braille[4] == '1' && Braile != "111111") {
    Servos[4].write(20);
    toClear = true;
    delay(200);
  };
  
  if(Braille[5] == '1' && Braile != "111111") {
    Servos[5].write(90);
    toClear = true;
  };

  if (toClear) {
    clearServos();
  };

  if(Braille != "000000") {
    rollPaper();
  };
}
