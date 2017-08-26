#include "AnalogInputPin.h"

#include "IOPort.h"
#include "ADConverter.h"

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

static void selectInputChannel_dummy(char channel) {
}
static void startConversion_dummy(void) {
}
static bool isConverting_dummy(void) {
	return false;
}
static uint16_t getResult_dummy(void) {
	return 0;
}
static const struct ADConverter ADConverter_dummy = {
	selectInputChannel_dummy,
	startConversion_dummy,
	isConverting_dummy,
	getResult_dummy,
};

static const struct AnalogInputPin* AnalogInputPin0_constructor(const struct IOPort*, char, char, const struct ADConverter*, char);
static const struct AnalogInputPin* AnalogInputPin1_constructor(const struct IOPort*, char, char, const struct ADConverter*, char);
static const struct AnalogInputPin* AnalogInputPin2_constructor(const struct IOPort*, char, char, const struct ADConverter*, char);
static const struct AnalogInputPin* AnalogInputPin3_constructor(const struct IOPort*, char, char, const struct ADConverter*, char);

static const struct AnalogInputPin* (*AnalogInputPinn_constructor[4])(const struct IOPort*, char, char, const struct ADConverter*, char) = {
	AnalogInputPin0_constructor,
	AnalogInputPin1_constructor,
	AnalogInputPin2_constructor,
	AnalogInputPin3_constructor,
};

const struct AnalogInputPin* createAnalogInputPin(
		const struct IOPort* port,
		char position,
		char analogInputPinMode,
		const struct ADConverter* adc,
		char inputChannel) {
	static char index = 0;
	return AnalogInputPinn_constructor[index++](
			port,
			position,
			analogInputPinMode,
			adc,
			inputChannel);
}
#endif /* COMMON_DECLARATION */

#if !defined(ANALOG_INPUT_PIN0_DECLARED)
#define ANALOG_INPUT_PIN0_DECLARED
#define this_(name) AnalogInputPin0_##name

#elif !defined(ANALOG_INPUT_PIN1_DECLARED)
#define ANALOG_INPUT_PIN1_DECLARED
#define this_(name) AnalogInputPin1_##name

#elif !defined(ANALOG_INPUT_PIN2_DECLARED)
#define ANALOG_INPUT_PIN2_DECLARED
#define this_(name) AnalogInputPin2_##name

#elif !defined(ANALOG_INPUT_PIN3_DECLARED)
#define ANALOG_INPUT_PIN3_DECLARED
#define this_(name) AnalogInputPin3_##name

#define EXIT_LOOP
#endif

static const struct ADConverter* this_(adc) = &ADConverter_dummy;
static char this_(inputChannel);

static int this_(read)() {
	this_(adc)->selectInputChannel(this_(inputChannel));
	this_(adc)->startConversion();
	while (this_(adc)->isConverting());
	return this_(adc)->getResult();
}

static const struct AnalogInputPin this_(instance) = {
	this_(read),
};

static const struct AnalogInputPin* this_(constructor)(
		const struct IOPort* port,
		char position,
		char analogInputPinMode,
		const struct ADConverter* adc,
		char inputChannel) {
	port->setPinModes(position, analogInputPinMode);
	port = &IOPort_dummy;
	this_(adc) = adc;
	this_(inputChannel) = inputChannel;
	return &this_(instance);
}

#undef this_

#if !defined(EXIT_LOOP)
#include "AnalogInputPin.c"
#endif
