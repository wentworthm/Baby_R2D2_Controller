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
char auth[] = "";
int xVal, yVal, headSpeed, soundCnt;
bool startup, xCmd, yCmd, headLeft, headRight;
double rampUp;
int wifiStartupState;

Servo leftServo, rightServo, headServo;
const int leftServoPin = D5;
const int rightServoPin = D6;
const int headServoPin = D7;

WiFiServer server(80);

BLYNK_WRITE(V1)
{
  xVal = param.asInt();
  startup = true;
  xCmd = true;
}

BLYNK_WRITE(V0)
{
  yVal = param.asInt();
  startup = true;
  yCmd = true;
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

  //leg motors
  int modifiedY = map(xVal, 0, 1024, 0, 1000) - 500;
  int modifiedX = map(yVal, 0, 1024, 0, 1000) - 500;
  int leftMotor, rightMotor;

  if (modifiedX < 0) {
    leftMotor = 1500 + modifiedY;
    rightMotor = 1500 - ((modifiedY + 1) / abs(modifiedY + 1)) * 500;
  }
  else if (modifiedX > 0) {
    leftMotor = 1500 + ((modifiedY + 1) / abs(modifiedY + 1)) * 500;
    rightMotor = 1500 - modifiedY;
  }
  else {
    leftMotor = 1500 + modifiedY;
    rightMotor = 1500 - modifiedY;
  }

  Serial.print(leftMotor);
  Serial.print(" - ");
  Serial.println(rightMotor);
  
  if(headLeft || headRight) {
    int multiplier;
    if(headLeft) {
      multiplier = 1;
    }
    else {
      multiplier = -1;
    }
    
    headServo.attach(headServoPin);
    headServo.writeMicroseconds(1500 + map(headSpeed, 0, 1024, 0, 500) * multiplier * rampUp);

    if(rampUp < 1.0) {
      rampUp += 0.1;
    }
  }
  else {
    rampUp = 0.0;
    headServo.detach();
  }

  if (startup) {
    if(leftMotor >= 1495 && leftMotor <= 1505 && rightMotor >= 1495 && rightMotor <= 1505) {
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
      xCmd = false;
      yCmd = false;
    }
  }
  
  delay(50);
  Blynk.run();
}
