#include <LSM303DLH.h>
#include <Wire.h>

// Constructors ////////////////////////////////////////////////////////////////

LSM303DLH::LSM303DLH()
{
}

// Public Methods //////////////////////////////////////////////////////////////

// Turns on the LSM303DLH's accelerometer and magnetometers and places them in normal
// mode.
void LSM303DLH::enable(void)
{
	//Enable Accelerometer
	Wire.beginTransmission(ACC_ADDRESS);
	Wire.send(CTRL_REG1_A);
	//0x27 = 0b00100111
	// Normal power mode, all axes enabled
	Wire.send(0x27); 
	Wire.endTransmission();
  
	//Enable Magnetometer
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(MR_REG_M);
	//0x00 = 0b00000000
	// Continuous conversion mode
	Wire.send(0x00);
	Wire.endTransmission();
}

// Reads all 6 channels of the LSM303DLH and stores them in the object variables
void LSM303DLH::read()
{
	//read accelerometer
	Wire.beginTransmission(ACC_ADDRESS);
	// assert the MSB of the address to get the accelerometer 
	// to do slave-transmit subaddress updating.
	Wire.send(OUT_X_L_A | (1 << 7)); 
	Wire.endTransmission();
	Wire.requestFrom(ACC_ADDRESS,6);

	while (Wire.available() < 6);
	
	uint8_t xla = Wire.receive();
	uint8_t xha = Wire.receive();
	uint8_t yla = Wire.receive();
	uint8_t yha = Wire.receive();
	uint8_t zla = Wire.receive();
	uint8_t zha = Wire.receive();

	accelerometerX = (xha << 8 | xla) >> 4;
	accelerometerY = (yha << 8 | yla) >> 4;
	accelerometerZ = (zha << 8 | zla) >> 4;
	
	//read magnetometer
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(OUT_X_H_M);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS,6);

	while (Wire.available() < 6);

	uint8_t xhm = Wire.receive();
	uint8_t xlm = Wire.receive();
	uint8_t yhm = Wire.receive();
	uint8_t ylm = Wire.receive();
	uint8_t zhm = Wire.receive();
	uint8_t zlm = Wire.receive();

	magnetometerX = (xhm << 8 | xlm);
	magnetometerY = (yhm << 8 | ylm);
	magnetometerZ = (zhm << 8 | zlm);
}