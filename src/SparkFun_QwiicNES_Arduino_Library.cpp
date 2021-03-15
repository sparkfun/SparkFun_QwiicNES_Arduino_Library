/*
  This is a library written for the SparkFun QwiicNES
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/18038

  Written by Nick Poole @ SparkFun Electronics, March 8th, 2021

  The QwiicNES is a USB/I2C interface for NES game controllers

  https://github.com/sparkfun/SparkFun_QwiicNES_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.7

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_QwiicNES_Arduino_Library.h"
#include "Arduino.h"

//Constructor
QwiicNES::QwiicNES()
{

}

//Initializes the I2C connection
//Returns false if board is not detected
boolean QwiicNES::begin(TwoWire &wirePort, uint8_t deviceAddress)
{
  _i2cPort = &wirePort;
  _i2cPort->begin(); //This resets any setClock() the user may have done

  _deviceAddress = deviceAddress;

  if (isConnected() == false) return (false); //Check for sensor presence

  return (true); //We're all setup!
}

//Returns true if I2C device ack's
boolean QwiicNES::isConnected()
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  if (_i2cPort->endTransmission() != 0)
    return (false); //Sensor did not ACK
  return (true);
}

//Change the I2C address of this address to newAddress
boolean QwiicNES::setI2CAddress(uint8_t newAddress)
{
  if (8 <= newAddress && newAddress <= 119)
  {
    writeRegister(QWIICNES_CHANGE_ADDRESS, newAddress);

    //Once the address is changed, we need to change it in the library
    _deviceAddress = newAddress;

    if (begin(Wire, newAddress) == true)
    {
      Serial.print("Address: 0x");
      if (newAddress < 16) Serial.print("0");
      Serial.print(newAddress, HEX); //Prints out new Address value in HEX
      Serial.print(" ");
      return (true);
    }
    else
    {
      Serial.println("Address Change Failure");
      return (false);
    }
  }
  else
  {
    Serial.println();
    Serial.println("ERROR: Input outside available address range (8-119)");
    return (false);
  }
  
}

//Return current I2C Address (known value for I2C debugging)
byte QwiicNES::getI2CAddress()
{
  byte address = readRegister(QWIICNES_ADDRESS);
  return(address);
}

//Get instantaneous button states at the time of the request, return as byte
byte QwiicNES::getCurrentButtonStates()
{
  byte buttons = readRegister(QWIICNES_CURRENT_STATE);
  return(buttons);
}

//Get accumulated button states since last request, return as byte
byte QwiicNES::getAccumulatedButtonStates()
{
  accumulatedStates = readRegister(QWIICNES_ACCUMULATOR);
  return(accumulatedStates);
}

//Get instantaneous button status 
bool QwiicNES::isPressed(uint8_t index)
{
  return (getCurrentButtonStates() >> index) & 1;
}

//Check a particular button status from last getAccumulatedButtonStates()
bool QwiicNES::wasPressed(uint8_t index)
{   
  return (accumulatedStates >> index) & 1;
}

//Reads from a given location from the QwiicNES
uint8_t QwiicNES::readRegister(uint8_t addr)
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  _i2cPort->write(addr);
  if (_i2cPort->endTransmission() != 0)
  {
    //Serial.println("No ack!");
    return (0); //Device failed to ack
  }
  _i2cPort->requestFrom((uint8_t)_deviceAddress, (uint8_t)1);
  if (_i2cPort->available()) {
    return (_i2cPort->read());
  }
  else
  {
    //Serial.println("No ack!");
    return (0); //Device failed to respond
  }
}

//Write a byte value to a spot in the QwiicNES
boolean QwiicNES::writeRegister(uint8_t addr, uint8_t val)
{
  _i2cPort->beginTransmission((uint8_t)_deviceAddress);
  _i2cPort->write(addr);
  _i2cPort->write(val);
  if (_i2cPort->endTransmission() != 0)
  {
    //Serial.println("No write ack!");
    return (false); //Device failed to ack
  }

  delay(30); // allow EPROM time to store value

  return (true);
}