#include <LSM303D.h>
#include <Wire.h>
#include <math.h>

LSM303D::LSM303D(void) {
	m_min = (Vector<int> ) { -32767, -32767, -32767 };
	m_max = (Vector<int> ) { +32767, +32767, +32767 };

	// high resolution mode
	writeReg(0x24, 0x64);

	// +/- 4 gauss full scale
	writeReg(0x25, 0x20);

	// low power mode off & continuous-conversion mode
	writeReg(0x26, 0x00);
	lastUpdate = 0;
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

		magReadings.x = (int) (xhm << 8 | xlm);
		magReadings.y = (int) (yhm << 8 | ylm);
		magReadings.z = (int) (zhm << 8 | zlm);

		Serial.println(magReadings.toString());

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

