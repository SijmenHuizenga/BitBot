#ifndef LSM303_h
#define LSM303_h

#include <Arduino.h> // for byte data type
/**
 * This type holds an x, y and z of the specified type
 */
template<typename T> struct Vector {
	T x, y, z;
	String toString() {
		return String(x) + ";" + String(y) + ";" + String(z);
	}
};

class LSM303D {
	public:
		//static variables
		static const byte i2cAddress = 0b0011101; //i2c address of the device
		static const unsigned int update_delay = 1000; //ms between updates

	public:
		Vector<int> m_max; // maximum magnetometer values, used for calibration
		Vector<int> m_min; // minimum magnetometer values, used for calibration
		void writeReg(byte reg, byte value);

		unsigned long lastUpdate;
		bool isReceiving;
	public:
		Vector<int> magReadings; // magnetometer readings

		LSM303D(void);
		void readMag(void);
		void update();

};

#endif

