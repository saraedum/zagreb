#ifndef ZAGREB_INPUTS_LINEAR_ROTARY_ENCODER_HPP
#define ZAGREB_INPUTS_LINEAR_ROTARY_ENCODER_HPP

#include <AceRoutine.h>

namespace zagreb::inputs {

template<typename T>
class LinearRotaryEncoder : public ace_routine::Coroutine {
	private:
		const uint8_t pin0, pin1;

		uint8_t last_pin0, last_pin1;

		const T min_value, max_value, step;

		T* value;
	public:
		LinearRotaryEncoder(const uint8_t pin0, const uint8_t pin1, const T min, const T max, T* value, const T step=1):
      pin0(pin0),
      pin1(pin1),
      min_value(min),
      max_value(max),
      step(step),
      value(value) {

			pinMode(pin0, INPUT);
      digitalWrite(pin0, HIGH);

			pinMode(pin1,INPUT);
      digitalWrite(pin1, HIGH);

			last_pin0 = digitalRead(pin0);
			last_pin1 = digitalRead(pin1);
		}

    int runCoroutine() override {
      COROUTINE_LOOP() {
			  uint8_t current_pin0 = digitalRead(pin0);
        uint8_t current_pin1 = digitalRead(pin1);

        uint8_t state = (last_pin0 << 3) | (last_pin1 << 2) | (current_pin0 << 1) | (current_pin1 << 0);

        switch(state) {
          case 0b1101:
          case 0b0100:
          case 0b0010:
          case 0b1011:
            increment();
            break;
          case 0b1100:
          case 0b0111:
          case 0b0001:
          case 0b1000:
            decrement();
            break;
        }

        last_pin0 = current_pin0;
        last_pin1 = current_pin1;

        // Unfortunately, the Uno does not have enough pins that support
        // interrupts so we have to poll frequently to find out when a linear
        // encoder has been moved. (Otherwise, we'll misread them and see
        // erratic behavior.)
        COROUTINE_DELAY(0);
      }
    }

    void increment() {
			if (max_value == *value);
			else if (max_value - *value <= step){
				*value = max_value;
				// on_change();
			}else{
				*value += step;
				// on_change();
			}
    }

    void decrement() {
			if (min_value == *value);
			else if (*value - min_value <= step){
				*value = min_value;
				// on_change();
			}else{
				*value -= step;
				// on_change();
			}
    }
};

}

#endif
