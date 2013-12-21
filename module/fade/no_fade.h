#ifndef NO_FADE_H
#define NO_FADE_H

#include "fade.h"

class NoFade : public Fade {
	private:
		const Color only_color;
	public:
		NoFade(const Color color):Fade(0),only_color(color){ }
		virtual Color color(uint32_t t){
			return only_color;
		}
};

#endif
