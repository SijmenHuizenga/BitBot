#ifndef LSM303_h
#define LSM303_h

#include <Arduino.h>
#include <math.h>

/**
 * This type holds an x, y and z of the specified type
 */
template<typename T> struct Vector {
	T x, y, z;
	String toString() {
		return String(x) + ";" + String(y) + ";" + String(z);
	}
};

class LSM303DMag {
	public:
		//static variables
		static const byte i2cAddress = 0b0011101; //i2c address of the device
		static const unsigned int update_delay = 100; //ms between updates

	private:
		void writeReg(byte reg, byte value);
		unsigned long lastUpdate;
		bool isReceiving;
		float r, t, f;
	public:
		Vector<int> readings; // magnetometer readings
		LSM303DMag(void);
		void update();
		void heading();

};

#endif

