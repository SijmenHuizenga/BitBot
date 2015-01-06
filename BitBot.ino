#include <Wire.h>
#include "BitBot.h"

void setup() {
	Serial.begin(9600);
	Wire.begin();
	Serial.println("a");
	Serial.println(String(freeRam()));
	BitBot::getBot()->setup();
	Serial.println("freRam: " + String(freeRam()));
}

void loop() {
	BitBot::getBot()->loop();
}

static int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
