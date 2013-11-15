#ifndef PROFILER_H
#define PROFILER_H

class Profiler {
		const char* id;
		uint32_t n = 0;
		uint32_t total = 0;
		uint32_t entry = 0;
	public:
		Profiler(const char* id):id(id){}
		inline void enter(){
			if (n%1000==0){
				Serial.print("Profiler(");
				Serial.print(id);
				Serial.print("): ");
				Serial.print(avg());
				Serial.println(" micros per call");
				n = 0;
				total = 0;
			}
			n++;
			entry = micros();
		}
		inline void exit(){
			total += micros() - entry;
		}
		float avg(){
			if (n==0)
				return 0;
			return total/(float)n;
		}
};

#endif
