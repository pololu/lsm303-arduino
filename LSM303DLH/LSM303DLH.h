#ifndef LSM303DLH_h
#define LSM303DLH_h

#include <WProgram.h> // for byte data type

// register addresses

#define LSM303DLH_CTRL_REG1_A       0x20
#define LSM303DLH_CTRL_REG2_A       0x21
#define LSM303DLH_CTRL_REG3_A       0x22
#define LSM303DLH_CTRL_REG4_A       0x23
#define LSM303DLH_CTRL_REG5_A       0x24
#define LSM303DLH_HP_FILTER_RESET_A 0x25
#define LSM303DLH_REFERENCE_A       0x26
#define LSM303DLH_STATUS_REG_A      0x27

#define LSM303DLH_OUT_X_L_A         0x28
#define LSM303DLH_OUT_X_H_A         0x29
#define LSM303DLH_OUT_Y_L_A         0x2A
#define LSM303DLH_OUT_Y_H_A         0x2B
#define LSM303DLH_OUT_Z_L_A         0x2C
#define LSM303DLH_OUT_Z_H_A         0x2D

#define LSM303DLH_INT1_CFG_A        0x30
#define LSM303DLH_INT1_SRC_A        0x31
#define LSM303DLH_INT1_THS_A        0x32
#define LSM303DLH_INT1_DURATION_A   0x33
#define LSM303DLH_INT2_CFG_A        0x34
#define LSM303DLH_INT2_SRC_A        0x35
#define LSM303DLH_INT2_THS_A        0x36
#define LSM303DLH_INT2_DURATION_A   0x37

#define LSM303DLH_CRA_REG_M         0x00
#define LSM303DLH_CRB_REG_M         0x01
#define LSM303DLH_MR_REG_M          0x02

#define LSM303DLH_OUT_X_H_M         0x03
#define LSM303DLH_OUT_X_L_M         0x04
#define LSM303DLH_OUT_Y_H_M         0x05
#define LSM303DLH_OUT_Y_L_M         0x06
#define LSM303DLH_OUT_Z_H_M         0x07
#define LSM303DLH_OUT_Z_L_M         0x08

#define LSM303DLH_SR_REG_M          0x09
#define LSM303DLH_IRA_REG_M         0x0A
#define LSM303DLH_IRB_REG_M         0x0B
#define LSM303DLH_IRC_REG_M         0x0C

class LSM303DLH
{
	public:
		typedef struct vector
		{
			float x, y, z;
		} vector;
		
		vector a; // accelerometer readings
		vector m; // magnetometer readings
		vector m_max; // maximum magnetometer values, used for calibration
		vector m_min; // minimum magnetometer values, used for calibration
	
		LSM303DLH(void);
		
		void enableDefault(void);
		
		void writeAccReg(byte reg, byte value);
		byte readAccReg(byte reg);
		void writeMagReg(byte reg, byte value);
		byte readMagReg(byte reg);
		
		void readAcc(void);
		void readMag(void);
		void read(void);
		
		int heading(void);
		int heading(vector from);
		
		// vector functions
		static void vector_cross(const vector *a, const vector *b, vector *out);
		static float vector_dot(const vector *a,const vector *b);
		static void vector_normalize(vector *a);
};

#endif



