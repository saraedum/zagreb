#ifndef FPS_H
#define FPS_H

#include "module.h"
#include "../util/now.h"

#define FPS_RESOLUTION 5000

class FPS : public Module{
	private:
		uint32_t start;
		uint32_t frames;
	public:
		FPS():start(now()),frames(0){
			Serial.begin(9600);
			Serial.println("FPS: Enabled.");
		}
		virtual void loop(){
			frames++;
			if (now()-start>FPS_RESOLUTION){
				Serial.print("FPS: ");
				Serial.println(frames/(float)(now()-start)*1000.);
				start=now();
				frames=0;
			}
		}
};

#endif
