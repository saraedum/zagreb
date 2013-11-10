#ifndef MODULE_H
#define MODULE_H

class Module {
	public:
	virtual void loop() = 0;
	virtual void setup(){}
	virtual void shutdown(){}
};

#endif
