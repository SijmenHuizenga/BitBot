
#include <Wire.h>
#include "BitBot.h"

void setup() {
	Serial.begin(9600);
	Wire.begin();

	BitBot::getBot()->setup();
}

void loop() {
	BitBot::getBot()->loop();
}


