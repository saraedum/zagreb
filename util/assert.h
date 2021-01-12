#ifndef ASSERT_H
#define ASSERT_H

#define __ASSERT_USE_STDERR

#include <assert.h>

void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
	// transmit diagnostic informations through serial link.
	Serial.println(__func);
	Serial.println(__file);
	Serial.println(__lineno, DEC);
	Serial.println(__sexp);
	Serial.flush();
  /*
	wall.set(Color(255,0,0));
	wall.setBrightness(255);
	wall.show();
	// abort program execution.
	abort();
  */
}

#endif
