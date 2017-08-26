#include <xc.h>
#include "Hardware.h"

// ----------------------------------------------------------------------------
// ADConverterModule_PositiveReference
// ----------------------------------------------------------------------------
enum ADConverterModule_PositiveReference_Constants {
	FVR       = 0b11,
	VREF_PLUS = 0b10,
	VDD       = 0b00,
};

const struct ADConverterModule_PositiveReference 
ADConverterModule_PositiveReference = {
	FVR,
	VREF_PLUS,
	VDD,
};

// ----------------------------------------------------------------------------
// ADConverterModule_NegativeReference
// ----------------------------------------------------------------------------
enum ADConverterModule_NegativeReference_Constants {
	VREF_MINUS = 0b1,
	VSS        = 0b0,
};

const struct ADConverterModule_NegativeReference
ADConverterModule_NegativeReference = {
	VREF_MINUS,
	VSS,
};

// ----------------------------------------------------------------------------
// ADConverterModule_ConversionClock
// ----------------------------------------------------------------------------
enum ADConverterModule_ConversionClock_Constants {
	F_RC         = 0b011,
	F_OSC_DIV_64 = 0b110,
	F_OSC_DIV_32 = 0b010,
	F_OSC_DIV_16 = 0b101,
	F_OSC_DIV_8  = 0b001,
	F_OSC_DIV_4  = 0b100,
	F_OSC_DIV_2  = 0b000,
};

const struct ADConverterModule_ConversionClock
ADConverterModule_ConversionClock = {
	F_RC,
	F_OSC_DIV_64,
	F_OSC_DIV_32,
	F_OSC_DIV_16,
	F_OSC_DIV_8,
	F_OSC_DIV_4,
	F_OSC_DIV_2,
};

// ----------------------------------------------------------------------------
// ADConverterModule_InputChannel
// ----------------------------------------------------------------------------
enum ADConverterModule_InputChannel_Constants {
	FVR_BUFFER_1          = 0b11111,
	DAC                   = 0b11110,
	TEMPERATURE_INDICATOR = 0b11101,
	AN7                   = 0b00111,
	AN6                   = 0b00110,
	AN5                   = 0b00101,
	AN4                   = 0b00100,
	AN3                   = 0b00011,
	AN2                   = 0b00010,
	AN1                   = 0b00001,
	AN0                   = 0b00000,
};

const struct ADConverterModule_InputChannel ADConverterModule_InputChannel = {
	FVR_BUFFER_1,
	DAC,
	TEMPERATURE_INDICATOR,
	AN7,
	AN6,
	AN5,
	AN4,
	AN3,
	AN2,
	AN1,
	AN0,
};

// ----------------------------------------------------------------------------
// ADConverterModule
// ----------------------------------------------------------------------------
#define ADConverterModule_(name) ADConverterModule_##name

static void ADConverterModule_(selectInputChannel)(char channel) {
	ADCON0bits.CHS = channel;
}

static void ADConverterModule_(startConversion)() {
	while(ADCON0bits.GO);
	ADCON0bits.GO = 1;
}

static bool ADConverterModule_(isConverting)() {
	return ADCON0bits.GO;
}

static uint16_t ADConverterModule_(getResult)() {
	return ((unsigned int)ADRESH << 2) + (ADRESL >> 6);
}

static const struct ADConverter ADConverterModule_(instance) = {
	ADConverterModule_selectInputChannel,
	ADConverterModule_startConversion,
	ADConverterModule_isConverting,
	ADConverterModule_getResult,
};

const struct ADConverter* ADConverterModule_(constructor)(
		char positiveReference,
		char negativeReference,
		char conversionClock) {
	ADCON1bits.ADPREF = positiveReference;
	ADCON1bits.ADNREF = negativeReference;
	ADCON1bits.ADCS = conversionClock;
	ADCON0bits.ADON = 1;
	return &ADConverterModule_(instance);
}

