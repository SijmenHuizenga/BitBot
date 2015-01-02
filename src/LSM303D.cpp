#include <LSM303D.h>
#include <Wire.h>
#include <math.h>

LSM303D::LSM303D(void) {
	min = (Vector<unsigned int> ) {32767, 32767, 32767};
	max = (Vector<unsigned int> ) {32767, 32767, 32767};

	// high resolution mode
	writeReg(0x24, 0x64);

	// +/- 4 gauss full scale
	writeReg(0x25, 0x20);

	// low power mode off & continuous-conversion mode
	writeReg(0x26, 0x00);
	lastUpdate = 10;
	isReceiving = false;
}

void LSM303D::writeReg(byte reg, byte value) {
	Wire.beginTransmission(i2cAddress);
	  Wire.write(reg);
	  Wire.write(value);
	Wire.endTransmission();
}

void LSM303D::update(){
	if(isReceiving && Wire.available() >= 6){
		byte xlm = Wire.read();
		byte xhm = Wire.read();
		byte ylm = Wire.read();
		byte yhm = Wire.read();
		byte zlm = Wire.read();
		byte zhm = Wire.read();

		//raw values are between -32767 and 32767
		int rawX = (int) (xhm << 8 | xlm); //naar unsigned int zodat getal tussen 0 en 365
		int rawY = (int) (yhm << 8 | ylm);
		int rawZ = (int) (zhm << 8 | zlm);

		//readings go from 0 to 65535. So need to add 32767
		readings.x = rawX+32767;
		readings.y = rawY+32767;
		readings.z = rawZ+32767;

//		readings.x = (int) map(readings.x, min.x, max.x, 0, 360);
//		readings.y = (int) map(readings.y, min.y, max.y, 0, 360);
//		readings.z = (int) map(readings.z, min.z, max.z, 0, 360);

//		Serial.println(readings.toString());

		Serial.println("min: " + min.toString());
		Serial.println("max: " + max.toString());

		isReceiving = false;
		lastUpdate = millis();
	}else if(isReceiving && millis() - lastUpdate - update_delay > 1000){
		//nothing received within 1000ms
		isReceiving = false;
		lastUpdate = millis();
	}else if(!isReceiving && millis() - lastUpdate > update_delay){
		Wire.beginTransmission(i2cAddress);
		Wire.write( 0b10001000 );
		  Wire.endTransmission();
		Wire.requestFrom(i2cAddress, (byte) 6);

		isReceiving = true;
	}
}

