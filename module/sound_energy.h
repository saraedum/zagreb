#ifndef SOUND_ENERGY_H
#define SOUND_ENERGY_H

#include "delay_module.h"

#define SAMPLE_SIZE 32
#define SAMPLE_FREQUENCY 0

class SoundEnergy : public DelayModule {
	private:
		inline double sq_(const double x){
			return x*x;
		}
		uint8_t j=0;
		uint16_t sample[SAMPLE_SIZE];
	public:
		SoundEnergy(){
			for(uint8_t k=0;k<SAMPLE_SIZE;k++)
				loop_delayed();
			energy();
		}
		double max_energy;
		virtual uint16_t loop_delayed(){
			double current = analogRead(MIC_PIN);
			j%=SAMPLE_SIZE;
			sample[j++] = current;
			return SAMPLE_FREQUENCY;
		}
		double energy(){
			double mean = 0;
			for (uint8_t i=0;i<SAMPLE_SIZE;i++)
				mean+=sample[i];
			mean /= SAMPLE_SIZE;
			double ret = 0;
			for (uint8_t i=0;i<SAMPLE_SIZE;i++)
				ret+=sq_(sample[i]-mean);
			if(ret>max_energy)
				max_energy = ret;
			return ret;
		}
};

#endif
