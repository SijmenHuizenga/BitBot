#ifndef LSM303_h
#define LSM303_h

#include <Arduino.h>
#include <math.h>

enum Direction{
	N, WN, W, SW, S, ES, E, NE
};


static char DirToString(Direction d){
	switch (d) {
		case N: return 'N'; break;
		case WN: return '1'; break;
		case W: return 'W'; break;
		case SW: return '2'; break;
		case S: return 'S'; break;
		case ES: return '3'; break;
		case E: return 'E'; break;
		case NE: return '4'; break;
	}
	return 'N';
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
		int hoek;

		float minX , maxX, minY, maxY;
	public:
		LSM303DMag(void);
		void update();
		Direction heading();
		int getHoek(){return this->hoek;};


};

#endif

