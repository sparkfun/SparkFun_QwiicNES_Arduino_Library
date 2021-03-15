/*
  Reading the Accumulated State of the NES Controller
  By: Nick Poole
  SparkFun Electronics
  Date: March 10th 2021
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example demonstrates how to use the wasPressed() method to capture the accumulated status of a button on the NES controller.
  This method works best in systems where timing is less critical, but no button presses can be missed. Calling getAccumulatedButtonStates()
  takes a snapshot of all buttons which have been pressed since the last call to getAccumulatedButtonStates() and, optionally, returns them
  as a byte. Subsequent calls to wasPressed() will reference this snapshot.

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

  // Prompt the user to press some buttons on the controller
  Serial.print("Press some buttons for the next 5...");
  delay(1000);
  Serial.print(" 4...");
  delay(1000);
  Serial.print(" 3...");
  delay(1000);
  Serial.print(" 2...");
  delay(1000);
  Serial.println(" 1...");
  delay(1000);

  myController.getAccumulatedButtonStates(); // Grab a snapshot of the accumulated button presses since last loop

  // Print button states
  Serial.print("[A:");
  Serial.print(myController.wasPressed(A));  
  Serial.print(" | B:");
  Serial.print(myController.wasPressed(B));  
  Serial.print(" | SELECT:");
  Serial.print(myController.wasPressed(SELECT));  
  Serial.print(" | START:");
  Serial.print(myController.wasPressed(START));  
  Serial.print(" | UP:");
  Serial.print(myController.wasPressed(UP));  
  Serial.print(" | DOWN:");
  Serial.print(myController.wasPressed(DOWN));  
  Serial.print(" | LEFT:");
  Serial.print(myController.wasPressed(LEFT));  
  Serial.print(" | RIGHT:");
  Serial.print(myController.wasPressed(RIGHT)); 
  Serial.println("]"); 
  
}
