#include "PhotoTransistor.h"

#include "AnalogInputPin.h"

#ifndef COMMON_DECLARATION
#define COMMON_DECLARATION

static int read_dummy() {
	return 0;
}
static const struct AnalogInputPin AnalogInputPin_dummy = {
	read_dummy,
};

static const struct PhotoTransistor* PhotoTransistor0_constructor(const struct AnalogInputPin*);
static const struct PhotoTransistor* PhotoTransistor1_constructor(const struct AnalogInputPin*);
static const struct PhotoTransistor* PhotoTransistor2_constructor(const struct AnalogInputPin*);
static const struct PhotoTransistor* PhotoTransistor3_constructor(const struct AnalogInputPin*);

static const struct PhotoTransistor* (*PhotoTransistorn_constructor[4])(const struct AnalogInputPin*) = {
	PhotoTransistor0_constructor,
	PhotoTransistor1_constructor,
	PhotoTransistor2_constructor,
	PhotoTransistor3_constructor,
};

const struct PhotoTransistor* createPhotoTransistor(
		const struct AnalogInputPin* pin) {
	static char index = 0;
	return PhotoTransistorn_constructor[index++](
			pin);
}
#endif /* COMMON_DECLARATION */

#if !defined(PHOTO_TRANSISTOR0_DECLARED)
#define PHOTO_TRANSISTOR0_DECLARED
#define this_(name) PhotoTransistor0_##name

#elif !defined(PHOTO_TRANSISTOR1_DECLARED)
#define PHOTO_TRANSISTOR1_DECLARED
#define this_(name) PhotoTransistor1_##name

#elif !defined(PHOTO_TRANSISTOR2_DECLARED)
#define PHOTO_TRANSISTOR2_DECLARED
#define this_(name) PhotoTransistor2_##name

#elif !defined(PHOTO_TRANSISTOR3_DECLARED)
#define PHOTO_TRANSISTOR3_DECLARED
#define this_(name) PhotoTransistor3_##name

#define EXIT_LOOP
#endif

static const struct AnalogInputPin* this_(pin);

static int this_(read)() {
	return this_(pin)->read();
}

static const struct PhotoTransistor this_(instance) = {
	this_(read),
};

static const struct PhotoTransistor* this_(constructor)(
		const struct AnalogInputPin* pin) {
	this_(pin) = &AnalogInputPin_dummy;
	this_(pin) = pin;
	return &this_(instance);
}

#undef this_

#if !defined(EXIT_LOOP)
#include "PhotoTransistor.c"
#endif
