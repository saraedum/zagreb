#ifndef DIST_H
#define DIST_H

class Dist {
	protected:
		void compute_max_dist(){
			max_dist = 0;
			for(uint8_t y=0;y<height;y++)
				for(uint8_t x=0;x<width;x++)
					if (dist(x,y)>max_dist)
						max_dist = dist(x,y);
		}	
		const uint8_t width,height;
		Dist(const uint8_t width, const uint8_t height):width(width),height(height){}
	public:
		virtual uint32_t dist(const uint8_t x, const uint8_t y) = 0;
		uint32_t max_dist;
};

#endif
