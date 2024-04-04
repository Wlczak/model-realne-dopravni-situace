#include <Servo.h>
Servo myservo;
const int servoPin = 6;
int pos = 0;
int redLeft = 2;
int redRight = 3;
int white = 4;
int button = 5;
int servoPos = 100;
int piezo = A0;
unsigned long servoTime = 0;
unsigned long lightTime = 0;
bool status = false;
void setup() {
  pinMode(redLeft, OUTPUT);
  pinMode(redRight, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(button, INPUT);
  myservo.attach(servoPin);
  myservo.write(servoPos);
  Serial.begin(9600);
  pinMode(piezo, OUTPUT);
}
void loop() {

  if (digitalRead(button) == 1) {
    //set up
    Serial.println("start");
    digitalWrite(white, LOW);
    lightTime = millis();
    servoTime = millis();
    //code redundancy function
    redLight(15);


    while (servoPos < 131) {
      if (millis() - servoTime > 40) {
        myservo.write(servoPos);
        servoPos++;
        servoTime = millis();
      }
      if (millis() - lightTime > 500) {
        lightTime = millis();
        if (status) {
          digitalWrite(redLeft, LOW);
          digitalWrite(redRight, HIGH);
          status = false;
          noTone(piezo);
        } else {
          digitalWrite(redLeft, HIGH);
          digitalWrite(redRight, LOW);
          status = true;
          tone(piezo, 1000);
        }
      }
    }
    delay(500);
    //Code redundancy function
    redLight(30);

  } else {
    noTone(piezo);
    digitalWrite(redLeft, LOW);
    digitalWrite(redRight, LOW);


    if (servoPos > 65) {
      if (millis() - servoTime > 40) {
        myservo.write(servoPos);
        servoPos--;
        servoTime = millis();
      }
    }
    if (millis() - lightTime > 500) {
      lightTime = millis();
      if (status) {
        digitalWrite(white, LOW);
        status = false;
      } else {
        digitalWrite(white, HIGH);
        status = true;
      }
    }
  }
}
void redLight(int cycles) {
  for (int i = 0; i < 15; i++) {
    if (status) {
      digitalWrite(redLeft, LOW);
      digitalWrite(redRight, HIGH);
      status = false;
      noTone(piezo);
      delay(500);

    } else {
      digitalWrite(redLeft, HIGH);
      digitalWrite(redRight, LOW);
      status = true;
      tone(piezo, 1000);
      delay(500);
    }
  }
}