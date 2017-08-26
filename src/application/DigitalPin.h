#ifndef DIGITAL_PIN_H
#define DIGITAL_PIN_H

#include <stdbool.h>

struct DigitalPin {
	void (*setDirection)(bool);
	bool (*read)(void);
	void (*write)(bool);
};

#endif /* DIGITAL_PIN_H */
