/*
 * Util.h
 *
 *  Created on: 6 jan. 2015
 *      Author: Sijmen
 */

#ifndef CONTROLLERS_UTIL_H_
#define CONTROLLERS_UTIL_H_

static int add360(int x, int toRotate) {
	x += toRotate;
	while (x > 360)
		x -= 360;
	while (x < 0)
		x = 360 + x;
	return x;
}

/**
 * In een linair stelsel zou "x < max && x > min" voldoende zijn,
 * maar wat als x = 1, max = 10 en min is 370... Dan is er een probleem.
 * Dit probleem wordt hier opgelost.
 */
static bool between360(int x, int min, int max){
	if(x < max && x > min)
		return true;
	x = add360(x, 180);
	min = add360(min, 180);
	max = add360(max, 180);
	return x < max && x > min;
}



#endif /* CONTROLLERS_UTIL_H_ */
