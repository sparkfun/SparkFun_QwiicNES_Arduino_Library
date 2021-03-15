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

#ifndef _SPARKFUN_QWIICNES_ARDUINO_LIBRARY_H
#define _SPARKFUN_QWIICNES_ARDUINO_LIBRARY_H
#include "Arduino.h"
#include "Wire.h"

#define QWIICNES_ADDR 0x54 //7-bit unshifted default I2C Address

//Map to the various registers on the QwiicNES
enum qwiicNESRegisters {
  QWIICNES_CURRENT_STATE = 0x00,
  QWIICNES_ACCUMULATOR = 0x01,
  QWIICNES_ADDRESS = 0x02,
  QWIICNES_CHANGE_ADDRESS = 0x03
};

class QwiicNES {
  public:
    QwiicNES();

    boolean begin(TwoWire &wirePort = Wire, uint8_t deviceAddress = QWIICNES_ADDR);
    boolean isConnected(); //Checks if sensor ack's the I2C request
		
	byte getCurrentButtonStates(); //Get instantaneous button states at the time of the request, return as byte
    byte getAccumulatedButtonStates(); //Get accumulated button states since last request, return as byte

    boolean isPressed(uint8_t index); //Get instantaneous button status 
	boolean wasPressed(uint8_t index); //Check a particular button status from last getAccumulatedButtonStates()
	
	boolean setI2CAddress(uint8_t newAddress); //Change the I2C address to newAddress (Prints new address over serial)
    byte getI2CAddress(); //Return current I2C Address (known value for I2C debugging)
	
  private:
    TwoWire *_i2cPort;
	uint8_t _deviceAddress;

    uint8_t readRegister(uint8_t addr);

    boolean writeRegister(uint8_t addr, uint8_t val);

    byte accumulatedStates; //Used for storing results from last getAccumulatedButtonStates()
};

#endif
