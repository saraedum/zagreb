#ifndef SOUND_BRIGHTNESS_H
#define SOUND_BRIGHTNESS_H

#include "sound_energy.h"
#include "delay_module.h"

#define SOUND_BRIGHTNESS_FREQUENCY HZ(30)

class SoundBrightness : public DelayModule {
	private:
		SoundEnergy& energy;
	public:
		SoundBrightness(SoundEnergy& energy):energy(energy){}
		uint8_t computed_brightness=255;
		uint8_t brightness=255;
		virtual uint16_t loop_delayed(){
			uint8_t new_brightness = 16+(uint8_t)(energy.energy()*(255-16)/energy.max_energy);
			if (new_brightness < brightness){
				if (brightness - new_brightness > brightness/10)
					brightness -= brightness/10;
				else
					brightness = new_brightness;
			} else {
				if (STROBO && (new_brightness > 245 || new_brightness - computed_brightness > 96)){
					wall.set(Color(255,255,255));
					wall.show();
					brightness = 255;
				}
				else if (new_brightness - brightness < 16)
					;
				else
					brightness = new_brightness;
			}
			computed_brightness = new_brightness;
			energy.max_energy *= .99;
			return SOUND_BRIGHTNESS_FREQUENCY;
		}
};

#endif
