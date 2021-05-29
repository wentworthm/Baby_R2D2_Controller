# Baby_R2D2_Controller

***THIS REPO IS STILL A WORK IN PROGRESS***

This is a controller for the Baby R2 unit from Michael Bradeley (https://www.patreon.com/mrbaddeley).  It is currently designed for controlling the three servos and a speaker using an ESP8266 nodemcu board.  User control is done using the Blynk IoT Platform.  User control is done using a custom Blynk App which can downloaded by scanning the QR code at the bottom of this readme into the Blynk application on your mobile phone.

## Required Software/Libraries
Arduino IDE: https://www.arduino.cc/en/software
ESP8266 board extention for the Arduino IDE: https://arduino-esp8266.readthedocs.io/en/latest/installing.html
Arduino Library Manager: WiFiManager, Blynk, Servo, ESP8266Audio

## Important note
There is a switch between the RX pin and the TIP120 circuit.  This is needed as the RX pin is needed by the ESP8266 Audio library for sending the sounds to the speaker.  If this is connected while you attempt to upload a new arduino sketch the IDE will not be able to upload to the board.  The switch breaks the connection allowing you to quickly upload then reactivate the speaker.  This is more useful for testing, but I decided to leave it in the official design.

![image](https://user-images.githubusercontent.com/7434662/119748188-50680980-be62-11eb-8d37-ec3ddb276986.png)
