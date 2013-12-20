#ifndef CONTROL_H
#define CONTROL_H

#include "delay_module.h"
#include "../composition/random_dist_fade.h"
#include "../composition/vertical_fade.h"
#include "../composition/horizontal_fade.h"
#include "../composition/central_fade.h"

#define CONTROL_DELAY HZ(60)

class Control : public DelayModule {
	private:
		uint8_t last_button0=LOW;
		uint8_t last_button1=LOW;
		int mode = 0;

		void on_button0(){
			next();
		}
		Composition* current;
		void on_button1(){}
		void next(){
			if (current){
				delete(current);
				current = 0;
			}
			switch(++mode){
				case 1:
					current = new RandomDistFade(&wall);
					break;
				case 2:
					current = new VerticalFade(&wall);
					break;
				case 3:
					current = new HorizontalFade(&wall);
					break;
				case 4:
					current = new CentralFade(&wall);
					break;
				default:
					mode=0;
					next();
					return;
			}

			Serial.print("Free RAM: ");
			Serial.println(freeRam());
			main = current->main;
		}
	public:
		static Module* main;
		Control(){
			next();
		}
		virtual uint16_t loop_delayed(){
			uint8_t button0 = digitalRead(BUTTON_PIN_0);
			if (button0 != last_button0 && last_button0 == LOW)
				on_button0();
			last_button0 = button0;
			uint8_t button1 = digitalRead(BUTTON_PIN_1);
			if (button1 != last_button1 && last_button1 == LOW)
				on_button1();
			last_button1 = button1;

			return CONTROL_DELAY;
		}
};

Module* Control::main;

#endif
