
/*
 Hydreon RG-9 RS232 Arduino 

 Based on https://forum.arduino.cc/t/serial-input-basics/278284

Connect the SO(Serial out) pin to pin 5 on the shield to the SI(Serial in) to pin 6.
D5 / SO
D6 / SI

Rain Sensitivity Levels
R 0 (None)
R 1 (Rain Drops)
R 2 (Very Light)
R 3 (Medium Light)
R 4 (Medium)
R 5 (Medium Heavy)
R 6 (Heavy)
R 7 (Violent)
R 0 TooCold;TooCold = appended to message if it is too cold to reliably sense, this will also set the R value to 0.
*/

const byte numChars = 32;
char rain_sensitivity[numChars]; // an array to store the received data
#include <SoftwareSerial.h>
SoftwareSerial Serial1(5, 6);// RX, TX

boolean newData = false;

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);// opens serial port, sets data rate to 9600 bps
}

void loop() {
 recvWithEndMarker();
 //showNewData();
 Serial.println(rain_sensitivity);
}

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 // if (Serial.available() > 0) {
  while (Serial1.available() > 0 ) {
// while (Serial1.available() > 0 && newData == false) {
 rc = Serial1.read();

 if (rc != endMarker) {
 rain_sensitivity[ndx] = rc;
 ndx++;
 if (ndx >= numChars) {
 ndx = numChars - 1;
 }
 }
 else {
 rain_sensitivity[ndx] = '\0'; // terminate the string
 ndx = 0;
 newData = true;
 }
 }
}

void showNewData() {
 if (newData == true) {
 Serial.println(rain_sensitivity);
 newData = false;
 }
}
