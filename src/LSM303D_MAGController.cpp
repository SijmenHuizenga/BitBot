#include <LSM303D_MAG.h>
#include <Wire.h>

LSM303DMag::LSM303DMag(void) {
	// high resolution mode
	writeReg(0x24, 0x64);

	// +/- 4 gauss full scale
	writeReg(0x25, 0x20);

	// low power mode off & continuous-conversion mode
	writeReg(0x26, 0x00);
	lastUpdate = 0;
	isReceiving = false;
}

void LSM303DMag::writeReg(byte reg, byte value) {
	Wire.beginTransmission(i2cAddress);
	  Wire.write(reg);
	  Wire.write(value);
	Wire.endTransmission();
}

void LSM303DMag::update(){
	unsigned long curMils = millis();
	if(isReceiving && Wire.available() >= 6){
		byte xl = Wire.read();
		byte xh = Wire.read();
		byte yl = Wire.read();
		byte yh = Wire.read();
		byte zl = Wire.read();
		byte zh = Wire.read();

		//raw values are between -32767 and 32767
		float x = (float) (xh << 8 | xl);
		float y = (float) (yh << 8 | yl);
		float z = (float) (zh << 8 | zl);

		r = sqrt(x*x+y*y+z*z);
		t = acos(z/r);
		f = atan(y/x);

		Serial.println(String(r) + ";" + String(t) + ";" + String(f)+";"+String(x) + ";" + String(y) + ";" + String(z));

		isReceiving = false;
		lastUpdate = curMils;
	}else if(isReceiving && curMils - lastUpdate - update_delay > 1000){
		//nothing received within 1000ms
		Serial.println("Had Timeout!");
		isReceiving = false;
		lastUpdate = curMils;
	}else if(!isReceiving && curMils - lastUpdate > update_delay){
		Wire.beginTransmission(i2cAddress);
		Wire.write( 0b10001000 );
		  Wire.endTransmission();
		Wire.requestFrom(i2cAddress, (byte) 6);

		isReceiving = true;
	}
}

void LSM303DMag::heading(){

}

