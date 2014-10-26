#ifndef CONTROL_H
#define CONTROL_H

#include "delay_module.h"
#include "../composition/random_dist_fade.h"
#include "../composition/vertical_fade.h"
#include "../composition/horizontal_fade.h"
#include "../composition/central_fade.h"
#include "../composition/solid.h"
#include "../composition/enumerate.h"
#include "../composition/align.h"

#define CONTROL_DELAY HZ(60)

class Control : public DelayModule {
	private:
		uint8_t last_button0=LOW;
		uint8_t last_button1=LOW;

		void on_button0(){
			if (is_cycle()){
				MODE = FIRST_NON_BOOT_MODE-1; // clear cycle flag and start on the first mode
				BRIGHTNESS = 255;
				wall.setBrightness(BRIGHTNESS);
			}else{
				if (mode() == MODES - 1){
					MODE = CYCLE_MASK | (FIRST_NON_BORING_MODE - 1); // set the cycle flag and start on the first non-boring mode
				}
			}
			next();
			STATS_UNTIL = now();
		}

		Composition* current;
		void on_button1(){
			if (BRIGHTNESS_MODE == 0){
				BRIGHTNESS_MODE = 1;
				BRIGHTNESS_DECAY = 0;
			}else if (BRIGHTNESS_MODE == 3 && BRIGHTNESS_DECAY == 6){
				BRIGHTNESS_MODE = 0;
				BRIGHTNESS_DECAY = 0;
			}else if (BRIGHTNESS_DECAY == 6){
				BRIGHTNESS_MODE += 1;
				BRIGHTNESS_DECAY = 0;
			}else{
				BRIGHTNESS_DECAY += 1;
			}
			STATS_UNTIL = now();
		}

		void next(){
			if (current){
				delete(current);
				current = 0;
			}
			MODE = (MODE&CYCLE_MASK) | (MODE&BOOT_MASK) | ((mode()+1)%MODES);
			if (mode() >= FIRST_NON_BOOT_MODE){
				MODE &= ~BOOT_MASK; // clear boot flag
			}
			if ((is_cycle() && mode() < FIRST_NON_BORING_MODE) || ((!is_boot()) && mode() < FIRST_NON_BOOT_MODE)){
				next();
				return;
			}
			if (is_cycle())
				NEXT_CYCLE = now() + CYCLE_LENGTH; // every minute
			switch(mode()){
				case 0:
					current = new Enumerate(&wall);
					break;
			    case 1:
					current = new Align(&wall);
					break;
				case 2:
					current = new Solid(&wall, Color(255,179,48));
					break;
				case 3:
					current = new Solid(&wall, Color(hash(hwrandom(UNCONNECTED_ANALOG_PIN))));
					break;
				case 4:
					current = new VerticalFade(&wall);
					break;
				case 5:
					current = new HorizontalFade(&wall);
					break;
				case 6:
					current = new CentralFade(&wall);
					break;
				case 7:
					current = new RandomDistFade(&wall);
					break;
				default:
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

			if (is_cycle()){
				if (now() > NEXT_CYCLE)
					next();
				else if(now() + CYCLE_DELAY > NEXT_CYCLE){
					BRIGHTNESS = (NEXT_CYCLE - now())*255/CYCLE_DELAY;
					if (BRIGHTNESS < 2*CYCLE_INCREASE)
						BRIGHTNESS = 0;
					wall.setBrightness(BRIGHTNESS);
				}else if(BRIGHTNESS != 255){
					if (255-BRIGHTNESS <= CYCLE_INCREASE)
						BRIGHTNESS = 255;
					else
						BRIGHTNESS += CYCLE_INCREASE;
					wall.setBrightness(BRIGHTNESS);
				}
			}

			return CONTROL_DELAY;
		}
};

Module* Control::main;

#endif
