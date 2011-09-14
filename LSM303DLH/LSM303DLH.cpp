#include <LSM303DLH.h>
#include <Wire.h>
#include <math.h>

// Defines ////////////////////////////////////////////////////////////////

// The Arduino two-wire interface uses a 7-bit number for the address, 
// and sets the last bit correctly based on reads and writes
#define ACC_ADDRESS (0x30 >> 1)
#define MAG_ADDRESS (0x3C >> 1)

// Constructors ////////////////////////////////////////////////////////////////

LSM303DLH::LSM303DLH(void)
{
	// These are just some values for a particular unit; it is recommended that
	// a calibration be done for your particular unit.
	m_max.x = +540; m_max.y = +500; m_max.z = 180;
	m_min.x = -520; m_min.y = -570; m_min.z = -770;
}

// Public Methods //////////////////////////////////////////////////////////////

// Turns on the LSM303DLH's accelerometer and magnetometers and places them in normal
// mode.
void LSM303DLH::enableDefault(void)
{
	// Enable Accelerometer
	// 0x27 = 0b00100111
	// Normal power mode, all axes enabled
	writeAccReg(LSM303DLH_CTRL_REG1_A, 0x27);
  
	// Enable Magnetometer
	// 0x00 = 0b00000000
	// Continuous conversion mode
	writeMagReg(LSM303DLH_MR_REG_M, 0x00);
}

// Writes an accelerometer register
void LSM303DLH::writeAccReg(byte reg, byte value)
{
	Wire.beginTransmission(ACC_ADDRESS);
	Wire.send(reg);
	Wire.send(value);
	Wire.endTransmission();
}

// Reads an accelerometer register
byte LSM303DLH::readAccReg(byte reg)
{
	byte value;
	
	Wire.beginTransmission(ACC_ADDRESS);
	Wire.send(reg);
	Wire.endTransmission();
	Wire.requestFrom(ACC_ADDRESS, 1);
	value = Wire.receive();
	Wire.endTransmission();
	
	return value;
}

// Writes a magnetometer register
void LSM303DLH::writeMagReg(byte reg, byte value)
{
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(reg);
	Wire.send(value);
	Wire.endTransmission();
}

// Reads a magnetometer register
byte LSM303DLH::readMagReg(byte reg)
{
	byte value;
	
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(reg);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS, 1);
	value = Wire.receive();
	Wire.endTransmission();
	
	return value;
}

// Reads the 3 accelerometer channels and stores them in vector a
void LSM303DLH::readAcc(void)
{
	Wire.beginTransmission(ACC_ADDRESS);
	// assert the MSB of the address to get the accelerometer 
	// to do slave-transmit subaddress updating.
	Wire.send(LSM303DLH_OUT_X_L_A | (1 << 7)); 
	Wire.endTransmission();
	Wire.requestFrom(ACC_ADDRESS, 6);

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
}

// Reads the 3 magnetometer channels and stores them in vector m
void LSM303DLH::readMag(void)
{
	Wire.beginTransmission(MAG_ADDRESS);
	Wire.send(LSM303DLH_OUT_X_H_M);
	Wire.endTransmission();
	Wire.requestFrom(MAG_ADDRESS, 6);

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

// Reads all 6 channels of the LSM303DLH and stores them in the object variables
void LSM303DLH::read(void)
{
	readAcc();
	readMag();
}

// Returns the number of degrees from the -Y axis that it
// is pointing.
int LSM303DLH::heading(void)
{
	return heading((vector){0,-1,0});
}

// Returns the number of degrees from the From vector projected into
// the horizontal plane is away from north.
// 
// Description of heading algorithm: 
// Shift and scale the magnetic reading based on calibration data to
// to find the North vector. Use the acceleration readings to
// determine the Down vector. The cross product of North and Down
// vectors is East. The vectors East and North form a basis for the
// horizontal plane. The From vector is projected into the horizontal
// plane and the angle between the projected vector and north is
// returned.
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
    vector_cross(&m, &temp_a, &E);
    vector_normalize(&E);
    vector_cross(&temp_a, &E, &N);
	
    // compute heading
    int heading = round(atan2(vector_dot(&E, &from), vector_dot(&N, &from)) * 180 / M_PI);
    if (heading < 0) heading += 360;
	return heading;
}

void LSM303DLH::vector_cross(const vector *a,const vector *b, vector *out)
{
  out->x = a->y*b->z - a->z*b->y;
  out->y = a->z*b->x - a->x*b->z;
  out->z = a->x*b->y - a->y*b->x;
}

float LSM303DLH::vector_dot(const vector *a,const vector *b)
{
  return a->x*b->x+a->y*b->y+a->z*b->z;
}

void LSM303DLH::vector_normalize(vector *a)
{
  float mag = sqrt(vector_dot(a,a));
  a->x /= mag;
  a->y /= mag;
  a->z /= mag;
}
