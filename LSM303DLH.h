#ifndef LSM303DLH_h
#define LSM303DLH_h
#include <Wire.h>
#include <vector.h>

class LSM303DLH
{
	public:
		vector a; //accelerometer	
		vector m; //magnetometer
		vector m_max;
		vector m_min;
	
		LSM303DLH();
		void enable(void);
		void read(void);
		int heading(void);
		int heading(vector from);
};

#endif



