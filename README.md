# Baby_R2D2_Controller

***THIS REPO IS STILL A WORK IN PROGRESS***

This is a controller for the Baby R2 unit from Michael Bradeley (https://www.patreon.com/mrbaddeley).  It is currently designed for controlling the three servos and a speaker using an ESP8266 nodemcu board.  User control is done using the Blynk IoT Platform.  User control is done using a custom Blynk App which can downloaded by scanning the QR code at the bottom of this readme into the Blynk application on your mobile phone.

## Required Software/Libraries
Arduino IDE: https://www.arduino.cc/en/software
ESP8266 board extention for the Arduino IDE: https://arduino-esp8266.readthedocs.io/en/latest/installing.html
Arduino Library Manager: WiFiManager, Blynk, Servo, ESP8266Audio

## Important note
There is a switch between the RX pin and the TIP120 circuit.  This is needed as the RX pin is needed by the ESP8266 Audio library for sending the sounds to the speaker.  If this is connected while you attempt to upload a new arduino sketch the IDE will not be able to upload to the board.  The switch breaks the connection allowing you to quickly upload then reactivate the speaker.  This is more useful for testing, but I decided to leave it in the official design.

## Blynk Setup
### Install the app on your phone (IOS/Android)
If you don't have the Blynk download it from Google Play or the IOS App Store.  This is a free for basic use tool.
### Create a new project
Open the Blynk app and click on "New Project"

<img src="https://user-images.githubusercontent.com/7434662/120406483-f3b09700-c318-11eb-9eba-63573df4b9db.PNG" height="300" />
Fill in a "Project Name", I used "baby r2d2".  For the device choose ESP8266 and select wifi for the connection type.  When this is all filled in press the "Create Project" button.

<img src="https://user-images.githubusercontent.com/7434662/120406620-49853f00-c319-11eb-8971-b29e0e41aef5.PNG" height="300" />
Once you hit the create button, an email will be sent to you.  This email is important as it has your device token in it.  This token will be used in the Arduino sketch.

<img src="https://user-images.githubusercontent.com/7434662/120407029-45a5ec80-c31a-11eb-8921-a70becbcd620.PNG" height="300" />
Once you click "OK" you'll be brougth to the main project screen.  If you click on the center of the screen a list will appear from the right side of the screen showing all of the objects you can add to your project.

<img src="https://user-images.githubusercontent.com/7434662/120407121-7dad2f80-c31a-11eb-9419-bc8a3b9f996d.PNG" height="300" />
I have chosen this layout, it's efficient and simple.  You will at a minimum need all of these components for your application, but you are free to rearrage the objects/items as desired.

<img src="https://user-images.githubusercontent.com/7434662/120407188-9fa6b200-c31a-11eb-9a0c-2b6b9e48dc27.PNG" height="300" />
Select the "Joystick" option by clicking on it.  Switch from "split" to "merge" and for the pin select "V0".  When you're finished press "OK" in the upper right corner.

<img src="https://user-images.githubusercontent.com/7434662/120407701-af72c600-c31b-11eb-890c-46038e86c878.PNG" height="300" />
Select the left head spin button.  Select the pin and change it to virtual and "V2".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120407822-e47f1880-c31b-11eb-90e8-4dcbd3d9fa78.PNG" height="300" />
Select the right head spin button.  Select the pin and change it to virtual and "V3".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120407866-ef39ad80-c31b-11eb-93aa-446a3da456b6.PNG" height="300" />
Select the virtical slider used to change the head speed.  Select the pin and change it to virtual and "V4".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120407944-0ed0d600-c31c-11eb-8a1a-575d0f35b1db.PNG" height="300" />
Select the first button that will be used for noises.  Select the pin and change it to virtual and "V5".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120408036-3162ef00-c31c-11eb-8da1-58d99058cef4.PNG" height="300" />
Select the first button that will be used for noises.  Select the pin and change it to virtual and "V6".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120408042-34f67600-c31c-11eb-8289-e562f7f7bd43.PNG" height="300" />
Select the first button that will be used for noises.  Select the pin and change it to virtual and "V7".  When you're finished press "OK" in the upper right 

<img src="https://user-images.githubusercontent.com/7434662/120408064-42abfb80-c31c-11eb-909e-0acc62151961.PNG" height="300" />

Press the "play button" in the upper right hand corner and the app is ready.
