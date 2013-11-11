#ifndef DELAY_MODULE_H
#define DELAY_MODULE_H

#include "module.h"

class DelayModule : public Module {
	uint32_t delay_until = 0;
	public:
	virtual uint32_t loop_delayed() = 0;
	virtual void loop(){
		uint32_t now = millis();
		if (now > delay_until)
			delay_until = now + loop_delayed();
	}
};

#endif
