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
	LICHTZOEKEN_X,		//lopen op de x ass
	LICHTZOEKEN_X_TO_Y, //draaien van x naar y ass
	LICHTZOEKEN_Y,		//lopen op y ass
	LICHTZOEKEN_Y_TO_X,	//draaien van y naar x ass
	LICHTZOEKEN_DONE,	//als klaar dan staat hij hier

	DANCE
};


#endif /* HEADERS_BITBOTSATES_H_ */
