#include "DigitalPin.h"

#include <stdint.h>
#include "IOPort.h"

#ifndef COMMON_DECLARATION
#define COMMON_DECLARATION

static void setPinModes_dummy(uint8_t pos, char mode) {
}
static uint8_t read_dummy(void) {
	return 0;
}
static void write_dummy(uint8_t pos, uint8_t output) {
}
static void toggle_dummy(uint8_t pos) {
}
static const struct IOPort IOPort_dummy = {
	setPinModes_dummy,
	read_dummy,
	write_dummy,
	toggle_dummy,
};

static const struct DigitalPin* DigitalPin0_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin1_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin2_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin3_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin4_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin5_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin6_constructor(const struct IOPort*, char, char, char);
static const struct DigitalPin* DigitalPin7_constructor(const struct IOPort*, char, char, char);

static const struct DigitalPin* (*DigitalPin_constructor[8])(const struct IOPort*, char, char, char) = {
	DigitalPin0_constructor,
	DigitalPin1_constructor,
	DigitalPin2_constructor,
	DigitalPin3_constructor,
	DigitalPin4_constructor,
	DigitalPin5_constructor,
	DigitalPin6_constructor,
	DigitalPin7_constructor,
};

const struct DigitalPin* createDigitalPin(
		const struct IOPort* port,
		char position,
		char inputPinMode,
		char outputPinMode) {
	static char index = 0;
	return DigitalPin_constructor[index++](
			port,
			position,
			inputPinMode,
			outputPinMode);
}
#endif /* COMMON_DECLARATION */

#if !defined(DIGITAL_PIN0_DECLARED)
#define DIGITAL_PIN0_DECLARED
#define this_(name) DigitalPin0_##name

#elif !defined(DIGITAL_PIN1_DECLARED)
#define DIGITAL_PIN1_DECLARED
#define this_(name) DigitalPin1_##name

#elif !defined(DIGITAL_PIN2_DECLARED)
#define DIGITAL_PIN2_DECLARED
#define this_(name) DigitalPin2_##name

#elif !defined(DIGITAL_PIN3_DECLARED)
#define DIGITAL_PIN3_DECLARED
#define this_(name) DigitalPin3_##name

#elif !defined(DIGITAL_PIN4_DECLARED)
#define DIGITAL_PIN4_DECLARED
#define this_(name) DigitalPin4_##name

#elif !defined(DIGITAL_PIN5_DECLARED)
#define DIGITAL_PIN5_DECLARED
#define this_(name) DigitalPin5_##name

#elif !defined(DIGITAL_PIN6_DECLARED)
#define DIGITAL_PIN6_DECLARED
#define this_(name) DigitalPin6_##name

#elif !defined(DIGITAL_PIN7_DECLARED)
#define DIGITAL_PIN7_DECLARED
#define this_(name) DigitalPin7_##name

#define EXIT_LOOP
#endif

static const struct IOPort* this_(port);
static char this_(position);
static char this_(inputMode);
static char this_(outputMode);

static void this_(setDirection)(bool direction) {
	if (direction == false) {
		this_(port)->setPinModes(
				this_(position),
				this_(inputMode));
	} else {
		this_(port)->setPinModes(
				this_(position),
				this_(outputMode));
	}
}

static bool this_(read)() {
	if ((this_(port)->read() & this_(position)) == 0) {
		return false;
	} else {
		return true;
	}
}

static void this_(write)(bool value) {
	if (value == true) {
		this_(port)->write(
				this_(position),
				0xFF);
	} else {
		this_(port)->write(
				this_(position),
				0x00);
	}
}

static const struct DigitalPin this_(instance) = {
	this_(setDirection),
	this_(read),
	this_(write),
};

static const struct DigitalPin* this_(constructor)(
		const struct IOPort* port,
		char position,
		char inputPinMode,
		char outputPinMode) {
	this_(port) = &IOPort_dummy;
	this_(port) = port;
	this_(position) = position;
	this_(inputMode) = inputPinMode;
	this_(outputMode) = outputPinMode;
	return &this_(instance);
}

#undef this_

#if !defined(EXIT_LOOP)
#include "DigitalPin.c"
#endif
