#ifndef DELAY_MODULE_H
#define DELAY_MODULE_H

#include "module.h"
#include "../util/now.h"

class DelayModule : public Module {
	uint32_t delay_until = 0;
	public:
	virtual uint32_t loop_delayed() = 0;
	virtual void loop(){
		if (NOW > delay_until)
			delay_until = NOW + loop_delayed();
	}
};

#endif
