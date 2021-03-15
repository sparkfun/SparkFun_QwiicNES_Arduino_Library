/*
  Reading the Instantaneous State of the NES Controller
  By: Nick Poole
  SparkFun Electronics
  Date: March 10th 2021
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example demonstrates how to use the isPressed() method to capture the instantaneous status of a button on the NES controller.
  This method polls the controller at the moment that the request is made, so it is possible to miss button presses. It is the simplest
  way to poll the controller and also the most time-critical.

  ALWAYS CONNECT A NES CONTROLLER TO THE QWIICNES BEFORE APPLYING POWER

*/

#include <SparkFun_QwiicNES_Arduino_Library.h>

QwiicNES myController;

// isPressed() and wasPressed() both take a button argument which references the button by NES Standard Controller byte order
// these variables make the code a little more readable by replacing the byte order with the button name
const byte A = 0;
const byte B = 1;
const byte SELECT = 2;
const byte START = 3;
const byte UP = 4;
const byte DOWN = 5;
const byte LEFT = 6;
const byte RIGHT = 7;

void setup() {

  myController.begin(); // Start The QwiicNES

  Serial.begin(115200); // Start the serial terminal at baud 115200

}

void loop() {

  // Poll and print the controller states
  Serial.print("[A:");
  Serial.print(myController.isPressed(A));  
  Serial.print(" | B:");
  Serial.print(myController.isPressed(B));  
  Serial.print(" | SELECT:");
  Serial.print(myController.isPressed(SELECT));  
  Serial.print(" | START:");
  Serial.print(myController.isPressed(START));  
  Serial.print(" | UP:");
  Serial.print(myController.isPressed(UP));  
  Serial.print(" | DOWN:");
  Serial.print(myController.isPressed(DOWN));  
  Serial.print(" | LEFT:");
  Serial.print(myController.isPressed(LEFT));  
  Serial.print(" | RIGHT:");
  Serial.print(myController.isPressed(RIGHT)); 
  Serial.println("]"); 
  
}
