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


	lastVal = -1;
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

		//raw values are between min and max int values
		int x = (int) (xh << 8 | xl);
		int y = (int) (yh << 8 | yl);
		int z = (int) (zh << 8 | zl);

		//receiving from int min to int max
		x = map(x, minX, maxX, -16384, 16384);
		y = map(y, minY, maxY, -16384, 16384);

		float s = atan(((float)y)/((float)x));
		s = degrees(s);
		if(x > 0 && y > 0){
			hoek = 90 - s;
		}else if(x > 0 && y < 0){
			hoek = 90 + abs(s);
		}else if(x < 0 && y < 0){
			hoek = 180 + (90 - s);
		}else if(x < 0 && y > 0){
			hoek = 270 + abs(s);
		}else{
			//could not find. Wait for next update.
			//I am aware that at x==0 and y==0
			//nothing is detected. This is on purpose!
		}
		hoek = add360(hoek, 90);
		isReceiving = false;
		lastUpdate = curMils;

		if(lastVal != hoek){
			lastVal = hoek;
			this->callback();
		}

	}else if(isReceiving && curMils - lastUpdate - update_delay > 1000){
		//nothing received within 1000ms
		Serial.println("LSM303D had Timeout!");
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

Direction LSM303DMag::heading(){
	if(hoek >= 337 || hoek < 22)
		return N;
	if(hoek >= 22  && hoek < 67)
		return WN;
	if(hoek >= 67 && hoek < 112)
		return W;
	if(hoek >= 112&& hoek < 153)
		return SW;
	if(hoek >= 153&& hoek < 202)
		return S;
	if(hoek >= 202&& hoek < 247)
		return ES;
	if(hoek >= 247&& hoek < 292)
		return E;
	if(hoek >= 292&& hoek < 337)
		return NE;
	return N;
}

void LSM303DMag::setValueChangeCallback(void(*call)(void)){
	this->callback = call;
}
