#include <LSM303DLH.h>
#include <Wire.h>
#include <math.h>
#include <vector.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address, 
// and sets the last bit correctly based on reads and writes
#define ACC_ADDRESS 		(0x30 >> 1)
#define MAG_ADDRESS 		(0x3C >> 1)

#define CTRL_REG1_A 		(0x20)
#define CTRL_REG2_A 		(0x21)
#define CTRL_REG3_A 		(0x22)
#define CTRL_REG4_A			(0x23)
#define CTRL_REG5_A 		(0x24)
#define HP_FILTER_RESET_A 	(0x25)
#define REFERENCE_A 		(0x26)
#define STATUS_REG_A 		(0x27)

#define OUT_X_L_A  			(0x28)
#define OUT_X_H_A  			(0x29)
#define OUT_Y_L_A  			(0x2A)
#define OUT_Y_H_A  			(0x2B)
#define OUT_Z_L_A  			(0x2C)
#define OUT_Z_H_A  			(0x2D)

#define INT1_CFG_A  		(0x30)
#define INT1_SOURCE_A  		(0x31)
#define INT1_THS_A  		(0x32)
#define INT1_DURATION_A  	(0x33)
#define INT2_CFG_A  		(0x34)
#define INT2_SOURCE_A  		(0x35)
#define INT2_THS_A  		(0x36)
#define INT2_DURATION_A  	(0x37)

#define CRA_REG_M  			(0x00)
#define CRB_REG_M  			(0x01)
#define MR_REG_M  			(0x02)

#define OUT_X_H_M  			(0x03)
#define OUT_X_L_M  			(0x04)
#define OUT_Y_H_M  			(0x05)
#define OUT_Y_L_M  			(0x06)
#define OUT_Z_H_M  			(0x07)
#define OUT_Z_L_M  			(0x08)

#define SR_REG_M   			(0x09)
#define IRA_REG_M   		(0x0A)
#define IRB_REG_M   		(0x0B)
#define IRC_REG_M   		(0x0C)

// Constructors ////////////////////////////////////////////////////////////////

LSM303DLH::LSM303DLH()
{
	// These are just some values for a particular unit, it is recommended that
	// a calibration be done for your particular unit.
	m_max.x = +540; m_max.y = +500; m_max.z = 180;
	m_min.x = -520; m_min.y = -570; m_min.z = -770;
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

	a.x = (xha << 8 | xla) >> 4;
	a.y = (yha << 8 | yla) >> 4;
	a.z = (zha << 8 | zla) >> 4;
	
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

	m.x = (xhm << 8 | xlm);
	m.y = (yhm << 8 | ylm);
	m.z = (zhm << 8 | zlm);
}

// Returns the number of degrees from the -Y axis that it
// is pointing.
int LSM303DLH::heading()
{
	return heading((vector){0,-1,0});
}

// Returns the number of degrees from the from vector that it
// is pointing.
int LSM303DLH::heading(vector from)
{
	// shift and scale
    m.x = (m.x - m_min.x) / (m_max.x - m_min.x) * 2 - 1.0;
    m.y = (m.y - m_min.y) / (m_max.y - m_min.y) * 2 - 1.0;
    m.z = (m.z - m_min.z) / (m_max.z - m_min.z) * 2 - 1.0;

	vector temp_a = a;
    // normalize
    vector_normalize(&temp_a);
    //vector_normalize(&m);

    // compute E and N
    vector E;
    vector N;
    vector_cross(&m,&temp_a,&E);
    vector_normalize(&E);
    vector_cross(&temp_a,&E,&N);
	
    // compute heading
    int heading = round(atan2(vector_dot(&E,&from), vector_dot(&N,&from)) * 180/M_PI);
    if(heading < 0) heading += 360;
	return heading;
}
