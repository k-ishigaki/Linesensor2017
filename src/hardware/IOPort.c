#include <xc.h>
#include "Hardware.h"

#ifndef IO_PORT_COMMON_DECRARED
#define IO_PORT_COMMON_DECRARED
// ----------------------------------------------------------------------------
// IOPort_PinMode
// ----------------------------------------------------------------------------
enum IOPort_PinMode_Constants {
	DIGITAL_INPUT,
	DIGITAL_INPUT_WITH_INTERNAL_PULLUP,
	DIGITAL_OUTPUT,
	ANALOG_INPUT,
};

const struct IOPort_PinMode IOPort_PinMode = {
	DIGITAL_INPUT,
	DIGITAL_INPUT_WITH_INTERNAL_PULLUP,
	DIGITAL_OUTPUT,
	ANALOG_INPUT,
};

#endif

// ----------------------------------------------------------------------------
// Port A, Port C
// ----------------------------------------------------------------------------
#if !defined(PORTA_DECLARED)
#define PORTA_DECLARED

#define Portx_(name) PortA_##name
#define PORTx        PORTA
#define ANSELx       ANSELA
#define TRISx        TRISA
#define LATx         LATA
#define WPUx         WPUA

#elif !defined(PORTC_DECLARED)
#define PORTC_DECLARED

#define Portx_(name) PortC_##name
#define PORTx        PORTC
#define ANSELx       ANSELC
#define TRISx        TRISC
#define LATx         LATC
#define WPUx         WPUC

#define EXIT_LOOP
#endif

static void Portx_(setPinModes)(uint8_t bits, char mode) {
	switch((enum IOPort_PinMode_Constants)mode) {
		case DIGITAL_INPUT:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
#ifdef WPUx
			WPUx   &= ~bits;
#endif
			TRISx  |= bits;
			break;
		case DIGITAL_INPUT_WITH_INTERNAL_PULLUP:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
#ifdef WPUx
			OPTION_REGbits.nWPUEN = 0;
			WPUx   |= bits;
#endif
			TRISx  |= bits;
			break;
		case DIGITAL_OUTPUT:
#ifdef ANSELx
			ANSELx &= ~bits;
#endif
			TRISx  &= ~bits;
			break;
		case ANALOG_INPUT:
#ifdef ANSELx
			ANSELx |= bits;
			TRISx  |= bits;
#endif
			break;
	}
}

static uint8_t Portx_(read)() {
	return PORTx;
}

static void Portx_(write)(uint8_t pos, uint8_t bits) {
	LATx = LATx | (pos & bits);
	LATx = LATx & (~pos | bits);
}

static void Portx_(toggle)(uint8_t pos) {
	uint8_t bits = ~LATx;
	LATx = LATx | (pos & bits);
	LATx = LATx & (~pos | bits);
}

static const struct IOPort Portx_(instance) = {
	Portx_(setPinModes),
	Portx_(read),
	Portx_(write),
	Portx_(toggle),
};

const struct IOPort* Portx_(constructor)() {
	return &Portx_(instance);
}

#undef Portx_
#undef PORTx
#undef ANSELx
#undef TRISx
#undef LATx
#undef WPUx

#if !defined(EXIT_LOOP)
#include "IOPort.c"
#endif
