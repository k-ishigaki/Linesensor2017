#include "LineSensor.h"

#include <stddef.h>

#include "LED.h"
#include "PhotoTransistor.h"

#include "DigitalPin.h"
#include "AnalogInputPin.h"

#include "Hardware.h"

#ifndef COMMON_DECLARATION
#define COMMON_DECLARATION

// declared at DigitalPin.c
extern const struct DigitalPin* createDigitalPin(const struct IOPort*, char, char, char);
// declared at LED.c
extern const struct LED* createLED(const struct DigitalPin*);
// declared at AnalogInputPin.c
extern const struct AnalogInputPin* createAnalogInputPin(const struct IOPort*, char, char, const struct ADConverter*, char);
// declared at PhotoTransistor.c
extern const struct PhotoTransistor* createPhotoTransistor(const struct AnalogInputPin*);

static const struct LED* LED0_getter() {
	static const struct LED* instance = NULL;
	if (instance == NULL) {
		instance = createLED(createDigitalPin(
					Hardware.PortC(),
					1 << 2,
					IOPort_PinMode.DIGITAL_INPUT,
					IOPort_PinMode.DIGITAL_OUTPUT));
	}
	return instance;
}

static const struct LED* LED1_getter() {
	static const struct LED* instance = NULL;
	if (instance == NULL) {
		instance = createLED(createDigitalPin(
					Hardware.PortC(),
					1 << 3,
					IOPort_PinMode.DIGITAL_INPUT,
					IOPort_PinMode.DIGITAL_OUTPUT));
	}
	return instance;
}

static const struct LED* LED2_getter() {
	static const struct LED* instance = NULL;
	if (instance == NULL) {
		instance = createLED(createDigitalPin(
					Hardware.PortC(),
					1 << 4,
					IOPort_PinMode.DIGITAL_INPUT,
					IOPort_PinMode.DIGITAL_OUTPUT));
	}
	return instance;
}

static const struct LED* LED3_getter() {
	static const struct LED* instance = NULL;
	if (instance == NULL) {
		instance = createLED(createDigitalPin(
					Hardware.PortC(),
					1 << 5,
					IOPort_PinMode.DIGITAL_INPUT,
					IOPort_PinMode.DIGITAL_OUTPUT));
	}
	return instance;
}

static const struct ADConverter* getADConverterModule() {
	static const struct ADConverter* instance = NULL;
	if (instance == NULL) {
		instance = Hardware.ADConverterModule(
				ADConverterModule_PositiveReference.VDD,
				ADConverterModule_NegativeReference.VSS,
				ADConverterModule_ConversionClock.F_OSC_DIV_32);
	}
	return instance;
}

static const struct PhotoTransistor* PhotoTransistor0_getter() {
	static const struct PhotoTransistor* instance = NULL;
	if (instance == NULL) {
		instance = createPhotoTransistor(createAnalogInputPin(
					Hardware.PortA(),
					1 << 0,
					IOPort_PinMode.ANALOG_INPUT,
					getADConverterModule(),
					ADConverterModule_InputChannel.AN0));
	}
	return instance;
}

static const struct PhotoTransistor* PhotoTransistor1_getter() {
	static const struct PhotoTransistor* instance = NULL;
	if (instance == NULL) {
		instance = createPhotoTransistor(createAnalogInputPin(
					Hardware.PortA(),
					1 << 1,
					IOPort_PinMode.ANALOG_INPUT,
					getADConverterModule(),
					ADConverterModule_InputChannel.AN1));
	}
	return instance;
}

static const struct PhotoTransistor* PhotoTransistor2_getter() {
	static const struct PhotoTransistor* instance = NULL;
	if (instance == NULL) {
		instance = createPhotoTransistor(createAnalogInputPin(
					Hardware.PortA(),
					1 << 2,
					IOPort_PinMode.ANALOG_INPUT,
					getADConverterModule(),
					ADConverterModule_InputChannel.AN2));
	}
	return instance;
}

static const struct PhotoTransistor* PhotoTransistor3_getter() {
	static const struct PhotoTransistor* instance = NULL;
	if (instance == NULL) {
		instance = createPhotoTransistor(createAnalogInputPin(
					Hardware.PortA(),
					1 << 4,
					IOPort_PinMode.ANALOG_INPUT,
					getADConverterModule(),
					ADConverterModule_InputChannel.AN3));
	}
	return instance;
}

const struct LineSensor LineSensor = {
	LED0_getter,
	PhotoTransistor0_getter,
	LED1_getter,
	PhotoTransistor1_getter,
	LED2_getter,
	PhotoTransistor2_getter,
	LED3_getter,
	PhotoTransistor3_getter,
};

#endif /* COMMON_DECLARATION */
