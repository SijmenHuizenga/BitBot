#ifndef LSM303_h
#define LSM303_h

#include <Arduino.h>
#include <math.h>
#include "Util.h"

/**
 * Alle windrichtingen. Omdat bepaalde
 * lettercombinaties (SE) al bezet waren,
 * zijn ze hier een beetje raar:
 * N = noord
 * NW = noord west
 * W = west
 * SW = zuid west
 * S = zuid
 * ES = zuid oost
 * E = oost
 * NE = noord oost
 */
enum Direction {
	N, WN, W, SW, S, ES, E, NE
};

/**
 * vorm een direction naar een stukie tekst
 */
static String DirToString(Direction d) {
	switch (d) {
	case N:
		return "N";
		break;
	case WN:
		return "NW";
		break;
	case W:
		return "W";
		break;
	case SW:
		return "SW";
		break;
	case S:
		return "S";
		break;
	case ES:
		return "SE";
		break;
	case E:
		return "E";
		break;
	case NE:
		return "NE";
		break;
	}
	return "N";
}
;

class LSM303DMag {
	public:
		//static variables
		static const byte i2cAddress = 0b0011101; //i2c address of the device
		static const unsigned int update_delay = 100; //ms between updates
	private:
		/**
		 * schrijf een waarde naar het register in LSM303D
		 */
		void writeReg(byte reg, byte value);

		/**
		 * wanneer was de laatste waarde-update?
		 */
		unsigned long lastUpdate;

		/**
		 * of ik wel of niet een waarde aan het ontvangen ben
		 */
		bool isReceiving;

		/**
		 * de functie die wordt aangeroepen als de draaing verandert
		 */
		void (*callback)(void);

		/**
		 * de laatste waarden die naar de callback is gestuurd
		 */
		int lastVal;

		/**
		 * de minimale, maximale waarde van X en Y. Deze wodren gebruikt voor calibratie
		 */
		static const float minX = -1811;
		static const float maxX = 3102;
		static const float minY = -2548;
		static const float maxY = 1573;

	public:
		//public so it can be referensed to DrivingControllers
		int hoek;

		/**
		 * constructor
		 */
		LSM303DMag();

		/**
		 * update die vanalles doet. Mag zo vaak als je wil worden aangeroepen
		 */
		void update();

		/**
		 * welke windrichting kijkt de arduino op?
		 */
		Direction heading();

		/**
		 * welke hoeek (0-360) ben ik opgedraaid?
		 */
		int getHoek() {
			return this->hoek;
		};

		/**
		 * wlke functie moet worden aangeroepen bij verandering vna richting
		 */
		void setValueChangeCallback(void (*)(void));
};

#endif

