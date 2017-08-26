#include "LED.h"

#include "DigitalPin.h"

#include <stdbool.h>

#ifndef COMMON_DECLARATION
#define COMMON_DECLARATION

static void setDirection_dummy(bool direction) {
}
static bool read_dummy() {
	return false;
}
static void write_dummy(bool value) {
}
static const struct DigitalPin DigitalPin_dummy = {
	setDirection_dummy,
	read_dummy,
	write_dummy,
};

static const struct LED* LED0_constructor(const struct DigitalPin*);
static const struct LED* LED1_constructor(const struct DigitalPin*);
static const struct LED* LED2_constructor(const struct DigitalPin*);
static const struct LED* LED3_constructor(const struct DigitalPin*);

static const struct LED* (*LEDn_constructor[4])(const struct DigitalPin*) = {
	LED0_constructor,
	LED1_constructor,
	LED2_constructor,
	LED3_constructor,
};

const struct LED* createLED(const struct DigitalPin* pin) {
	static char index = 0;
	return LEDn_constructor[index++](pin);
}
#endif /* COMMON_DECLARATION */

#if !defined(LED0_DECLARED)
#define LED0_DECLARED
#define LEDn_(name) LED0_##name

#elif !defined(LED1_DECLARED)
#define LED1_DECLARED
#define LEDn_(name) LED1_##name

#elif !defined(LED2_DECLARED)
#define LED2_DECLARED
#define LEDn_(name) LED2_##name

#elif !defined(LED3_DECLARED)
#define LED3_DECLARED
#define LEDn_(name) LED3_##name

#define EXIT_LOOP
#endif

static const struct DigitalPin* LEDn_(pin);

static void LEDn_(turnOn)() {
	LEDn_(pin)->write(true);
}

static void LEDn_(turnOff)() {
	LEDn_(pin)->write(false);
}

static const struct LED LEDn_(instance) = {
	LEDn_(turnOn),
	LEDn_(turnOff),
};

static const struct LED* LEDn_(constructor)(const struct DigitalPin* pin) {
	LEDn_(pin) = &DigitalPin_dummy;
	LEDn_(pin) = pin;
	LEDn_(pin)->setDirection(true);

	return &LEDn_(instance);
}

#undef LEDn_

#if !defined(EXIT_LOOP)
#include "LED.c"
#endif
