#ifndef ZAGREB_INPUTS_BUTTON_HPP
#define ZAGREB_INPUTS_BUTTON_HPP

#include <AceRoutine.h>

namespace zagreb::inputs {

class Button : public ace_routine::Coroutine {
	private:
		const uint8_t pin;

    uint8_t last = LOW;

    void (*onClick)(void* data);
    void* data;
	public:
		Button(const uint8_t pin, void (*onClick)(void*), void* data): pin(pin), onClick(onClick), data(data) {
			pinMode(pin, INPUT);
      digitalWrite(pin, HIGH);

      last = digitalRead(pin);
		}

    int runCoroutine() override {
      COROUTINE_LOOP() {
			  uint8_t current = digitalRead(pin);
        if (current != last && last == LOW)
          onClick(data);
        last = current;

        // Unfortunately, the Uno does not have enough pins that support
        // interrupts so we have to poll somewhat frequently to not miss button
        // presses.
        COROUTINE_DELAY(10);
      }
    }
};

}

#endif
