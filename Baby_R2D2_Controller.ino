#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"
#include "sounds.h"

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2SNoDAC *out;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "<insert blynk token here>";
int xVal, yVal, headSpeed, soundCnt;
bool startup, headLeft, headRight;
double rampUpHead, rampUpBody;

Servo leftServo, rightServo, headServo;
const int leftServoPin = D5;
const int rightServoPin = D6;
const int headServoPin = D7;
const int NEUTRAL = 1500;
const int CONTROLLER_NEUTRAL = 511;
const int NEUTRAL_ZONE = 20;
const int MIN_CONTROLLER = 0;
const int MAX_CONTROLLER = 1024;

WiFiServer server(80);

BLYNK_WRITE(V0)
{
  xVal = param[0].asInt();
  yVal = param[1].asInt();
  
  startup = true;
}

BLYNK_WRITE(V2)
{
  headLeft = param.asInt();
}

BLYNK_WRITE(V3)
{
  headRight = param.asInt();
}

BLYNK_WRITE(V4)
{
  headSpeed = param.asInt();
}

BLYNK_WRITE(V5)
{
  int sound = param.asInt();

  if(sound) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( noise, sizeof(noise) );
    out = new AudioOutputI2SNoDAC();
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);

    while (wav->isRunning()) {
      if (!wav->loop()) wav->stop();
    }
  }
}

BLYNK_WRITE(V6)
{
  int sound = param.asInt();

  if(sound) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( beeping, sizeof(beeping) );
    out = new AudioOutputI2SNoDAC();
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);

    while (wav->isRunning()) {
      if (!wav->loop()) wav->stop();
    }
  }
}

BLYNK_WRITE(V7)
{
  int sound = param.asInt();

  if(sound) {
    audioLogger = &Serial;
    file = new AudioFileSourcePROGMEM( scream, sizeof(scream) );
    out = new AudioOutputI2SNoDAC();
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);

    while (wav->isRunning()) {
      if (!wav->loop()) wav->stop();
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  startup = false;
  headSpeed = 0;
  headLeft = false;
  headRight = false;

  Blynk.config(auth);
  WiFiManager wifiManager;
  bool result = wifiManager.autoConnect("Baby_R2D2","MasterLuke");
  Blynk.connect();
}

void loop()
{
  int leftMotor, rightMotor;
  //leg motors
  int modifiedX = map(xVal, MIN_CONTROLLER, MAX_CONTROLLER, 0, 1000) - 500;
  int modifiedY = map(yVal, MIN_CONTROLLER, MAX_CONTROLLER, 0, 1000) - 500;

  if (modifiedX < 0) {
    leftMotor = NEUTRAL + modifiedY;
    rightMotor = NEUTRAL - ((modifiedY + 1) / abs(modifiedY + 1)) * 500;
  }
  else if (modifiedX > 0) {
    leftMotor = NEUTRAL + ((modifiedY + 1) / abs(modifiedY + 1)) * 500;
    rightMotor = NEUTRAL - modifiedY;
  }
  else {
    leftMotor = NEUTRAL + modifiedY;
    rightMotor = NEUTRAL - modifiedY;
  }

  if(headLeft || headRight) {
    int multiplier;
    if(headLeft) {
      multiplier = 1;
    }
    else {
      multiplier = -1;
    }
    
    headServo.attach(headServoPin);
    headServo.writeMicroseconds(NEUTRAL + map(headSpeed, 0, 1024, 0, 500) * multiplier * rampUpHead);

    if(rampUpHead < 1.0) {
      rampUpHead += 0.1;
    }
  }
  else {
    rampUpHead = 0.0;
    headServo.detach();
  }

  if (startup) {
    if(leftMotor == NEUTRAL && rightMotor == NEUTRAL) {
      rampUpBody = 0.0;
      leftServo.detach();
      rightServo.detach();
    }
    else {
      if(!leftServo.attached()) {
        leftServo.attach(leftServoPin);
      }
      if(!rightServo.attached()) {
        rightServo.attach(rightServoPin);
      }
      leftServo.writeMicroseconds(leftMotor);
      rightServo.writeMicroseconds(rightMotor);
    }
  }
  
  delay(50);
  Blynk.run();
}
