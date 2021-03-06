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
				a = a* this->a;
				c = this->a*c + this->c;
			}else{
				fast_exp(n/2,a,c);
				a*=a;
				c = a*c+c;
			}
		}
		void loop(const uint32_t a, const uint32_t c){
			x = a*x + c;
		}
	public:
		explicit Random(uint32_t seed):x(seed){}
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
		bool randbit(){
			return random()%2;
		}
		double randrange(double a, double b){
			assert(b>a);
			double ret = random();
			ret /= (uint32_t)-1;
			ret *= (b-a);
			ret += a;
			return ret;
		}
		double standard_gauss(){
			double v1,v2,s;
			do {
				v1 = 2.0 * randrange(0.,1.) - 1;
				v2 = 2.0 * randrange(0.,1.) - 1;
				s = v1*v1 + v2*v2;
			}while (s>= 1.0);
			if (s==0.) return 0.;
			return v1*sqrt(-2.*log(s)/s);
		}
		double gauss(double mu, double sigma){
			return standard_gauss()*sigma + mu;
		}
		double gauss_clamp(double mu, double sigma, double lower, double upper){
			double ret = gauss(mu,sigma);
			if (ret<lower)
				ret = lower;
			if (ret>upper)
				ret = upper;
			return ret;
		}
};

uint32_t hwrandom(const uint8_t pin){
	return ((uint32_t)analogRead(pin))<<22 ^ ((uint32_t)analogRead(pin))<<14 ^ ((uint32_t)analogRead(pin))<<7 ^ ((uint32_t)analogRead(pin)); // analog read returns only 10 bits
}

#endif
