#ifndef LSM303DLH_h
#define LSM303DLH_h

#include <Wire.h>

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

class LSM303DLH
{
	public:
		signed int accelerometerX;
		signed int accelerometerY;
		signed int accelerometerZ;
		signed int magnetometerX;
		signed int magnetometerY;
		signed int magnetometerZ;
		//TwoWire wire;
		LSM303DLH();
		void enable(void);
		void read(void);
};

#endif



