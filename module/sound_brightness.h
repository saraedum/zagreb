#ifndef SOUND_BRIGHTNESS_H
#define SOUND_BRIGHTNESS_H

#include "sound_energy.h"
#include "delay_module.h"

#define SOUND_BRIGHTNESS_FREQUENCY HZ(30)

class SoundBrightness : public DelayModule {
	private:
		SoundEnergy& energy;
		inline bool strobe(){
			return BRIGHTNESS_MODE == 1;
		}

		inline bool sharp_threshold(){
			return BRIGHTNESS_MODE == 2;
		}

		inline bool sound_brightness(){
			return BRIGHTNESS_MODE != 0;
		}

	public:
		SoundBrightness(SoundEnergy& energy):energy(energy){}
		uint8_t computed_brightness=255;
		uint8_t brightness=255;
		virtual uint16_t loop_delayed(){
			//uint8_t new_brightness = 16+(uint8_t)(energy.energy()*(240)/energy.max_energy);
			uint8_t new_brightness = (uint8_t)(energy.energy()*(255)/energy.max_energy);
			if (sharp_threshold()){
				float relative_brightness = new_brightness/255.;
				relative_brightness = (relative_brightness-.3)/(.7-.3);
				if (relative_brightness<0.)
					relative_brightness = 0.;
				if (relative_brightness>1.)
					relative_brightness = 1.;
				relative_brightness = relative_brightness*relative_brightness*(3-2*relative_brightness);
				new_brightness = relative_brightness*255;
			}
			if (new_brightness < brightness){
				if (brightness - new_brightness > (1<<BRIGHTNESS_DECAY))
					brightness = max(new_brightness, brightness - (brightness>>BRIGHTNESS_DECAY));
			} else {
				if (strobe() && (new_brightness > 245 || new_brightness - computed_brightness > 96)){
					wall.set(Color(255,255,255));
					wall.show();
					brightness = 255;
				}
				else if (new_brightness - brightness < 16)
					brightness = new_brightness;
				else
					brightness = new_brightness;
			}
			computed_brightness = new_brightness;
			energy.max_energy *= .999;
			return SOUND_BRIGHTNESS_FREQUENCY;
		}
};

#endif
