/*
  Changing the I2C Address of The QwiicNES
  By: Nick Poole
  SparkFun Electronics
  Date: March 10th 2021
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example demonstrates how to change the I2C Address fo The QwiicNES. If you get an error, check your electrical connections.
  Otherwise, try running one of the other examples with your new address, it may have changed before you could open the serial terminal.

  ALWAYS CONNECT A NES CONTROLLER TO THE QWIICNES BEFORE APPLYING POWER

*/

#include <SparkFun_QwiicNES_Arduino_Library.h>

QwiicNES myController;

const byte currentAddress = 0x54;
const byte newAddress = 0x50;

void setup() {

  Serial.begin(115200);

}

void loop() {

  if(myController.begin(Wire, currentAddress)){
    
    Serial.print("The QwiicNES was found at address 0x");
    Serial.println(myController.getI2CAddress(), HEX);
    Serial.println("Changing to new address...");
  
    if(myController.setI2CAddress(newAddress))
    {
      Serial.print("Success!");
    }
  
    while(1){};
    
  }else{

    Serial.print("No QwiicNES was found at address 0x");
    Serial.print(currentAddress, HEX);
    Serial.print(" (did you already run this sketch?)");

    while(1){};
    
  }
  
}
