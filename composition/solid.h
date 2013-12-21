#ifndef SOLID_H
#define SOLID_H

#include "composition.h"
#include "../module/solid_color.h"

class Solid : public Composition {
	private:
		SolidColor module;
	public:
		Solid(Wall* const wall, const Color color):module(wall, color){
			main = &module;
		}
};

#endif
