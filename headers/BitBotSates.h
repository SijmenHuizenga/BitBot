/*
 * BitBotSates.h
 *
 *  Created on: 7 jan. 2015
 *      Author: Sijmen
 */

#ifndef HEADERS_BITBOTSATES_H_
#define HEADERS_BITBOTSATES_H_


enum BitBotState{
	//Bij botsing moet robot:
	NABOTSING_ACHTERUIT, 	//een stukje achteruit
	NABOTSING_DRAAIEN_A,   //draaien,
	NABOTSING_VOORUIT,		//een stukje vooruit
	NABOTSING_DRAAIEN_B,	//terug draaien

	//tijdens lichtzoeken:
	LICHTZOEKEN_STARTING,  //zoeken naar een verschil van licht
	LICHTZOEKEN_GRADIENT,   //draaien van x naar y ass
	LICHTZOEKEN_TURNING,	//draaien naar de volgende ass
	LICHTZOEKEN_DONE,	  //als klaar dan staat hij hier

	DANCE
};

enum Axis{
	X_AXES,
	Y_AXES,
	DONE_AXES
};


#endif /* HEADERS_BITBOTSATES_H_ */
