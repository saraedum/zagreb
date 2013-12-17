#ifndef NOW_H
#define NOW_H

uint32_t _now=millis();

inline uint32_t now(){
	return _now;
}

inline void update_now(){
	_now = millis();
}

#endif
