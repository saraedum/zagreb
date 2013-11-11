#ifndef RANDOM_H
#define RANDOM_H

#include <assert.h>

class Random {
	private:
		uint32_t x;
		const uint32_t a=1103515245;
		const uint32_t c=12345;
		void fast_exp(uint32_t n, uint32_t& a, uint32_t& c){
			a=1;
			c=0;

			if (!n)
				return;
			if (n%2){
				fast_exp(n-1,a,c);
				a*=this->a;
				c+=this->a*c + this->c;
			}else{
				fast_exp(n/2,a,c);
				a*=a;
				c+=a*c+c;
			}
		}
		void loop(const uint32_t a, const uint32_t c){
			x = a*x + c;
		}
	public:
		Random(uint32_t seed):x(seed){}
		uint32_t random(){
			skip();
			return x;
		}
		void skip(){
			loop(a,c);
		}
		void skip(uint32_t n){
			if (!n)
				return;
			uint32_t a,c;
			fast_exp(n,a,c);
			loop(a,c);
		}
		uint32_t randrange(uint32_t a, uint32_t b){ // returns an element of [a,b) -- this is not equally distributed if b-a is large
			assert(b>a);
			uint32_t l=b-a;
			return random()%l + a;
		}
};

#endif
