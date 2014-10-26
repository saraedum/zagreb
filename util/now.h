#ifndef NOW_H
#define NOW_H

#include "bpm.h"

uint32_t _now=millis();
uint32_t _bpm_now=0;

inline uint32_t now(){
	return _now;
}

inline uint32_t mbeat(){
	return _bpm_now;
}

inline void update_now(){
	uint32_t onow = _now;
	_now = millis();
	_bpm_now += (_now-onow)*BPM/60;
}

#endif
