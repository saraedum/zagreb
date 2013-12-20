#ifndef LINEAR_ROTARY_ENCODER_H
#define LINEAR_ROTARY_ENCODER_H

#include "delay_module.h"

#define ROTARY_ENCODER_DELAY 0

template<typename T> class LinearRotaryEncoder : public DelayModule {
	private:
		const uint8_t pin0,pin1;
		uint8_t last_pin0;
		const T min_value,max_value,step;
	protected:
		T*const value;
		virtual void on_change(){}
	public:
		LinearRotaryEncoder(const int pin0, const int pin1, const T min, const T max, T*const value, const T step=1):pin0(pin0),pin1(pin1),min_value(min),max_value(max),step(step),value(value){
			pinMode(pin0,INPUT);
			last_pin0 = digitalRead(pin0);
			pinMode(pin1,INPUT);
		}
		virtual uint16_t loop_delayed(){
			uint8_t current_pin0 = digitalRead(pin0);
			if (last_pin0==LOW && current_pin0==HIGH){
				if(digitalRead(pin1) == HIGH){
					if (max_value == *value);
					else if (max_value - *value <= step){
						*value = max_value;
						on_change();
					}else{
						*value += step;
						on_change();
					}
				}else{
					if (min_value == *value);
					else if (*value - min_value <= step){
						*value = min_value;
						on_change();
					}else{
						*value -= step;
						on_change();
					}
				}
				Serial.print("value= ");
				Serial.println(*value);
			}
			last_pin0 = current_pin0;

			return ROTARY_ENCODER_DELAY;
		}
};

#endif
