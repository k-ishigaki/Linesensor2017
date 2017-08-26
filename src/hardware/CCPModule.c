#include <xc.h>
#include "Hardware.h"

#ifndef CCP_MODULE_COMMON
#define CCP_MODULE_COMMON
// ----------------------------------------------------------------------------
// CaptureModule Constants
// ----------------------------------------------------------------------------
enum CaptureModule_Mode_Constants {
	EVERY_FALLING_EDGE     = 0b0100,
	EVERY_RISING_EDGE      = 0b0101,
	EVERY_4TH_RISING_EDGE  = 0b0110,
	EVERY_16TH_RISING_EDGE = 0b0111,
};
const struct CaptureModule_Mode CaptureModule_Mode = {
	EVERY_FALLING_EDGE,
	EVERY_RISING_EDGE,
	EVERY_4TH_RISING_EDGE,
	EVERY_16TH_RISING_EDGE,
};

enum CompareModule_Mode_Constants {
	LOW_TO_HIGH           = 0b1000,
	HIGH_TO_LOW           = 0b1001,
	SOFTWARE_INTERRUPT    = 0b1010,
	SPECIAL_EVENT_TRIGGER = 0b1011,
};
const struct CompareModule_Mode CompareModule_Mode = {
	LOW_TO_HIGH,
	HIGH_TO_LOW,
	SOFTWARE_INTERRUPT,
	SPECIAL_EVENT_TRIGGER,
};

enum PWMModule_BaseTimer_Constants {
	TIMER2 = 0b00,
	TIMER4 = 0b01,
	TIMER6 = 0b10,
};
const struct PWMModule_BaseTimer PWMModule_BaseTimer = {
	TIMER2,
	TIMER4,
	TIMER6,
};

enum PWMModule_OutputConfig_Constants {
	SINGLE              = 0b00,
	FULL_BRIDGE_FORWARD = 0b01,
	HALF_BRIDGE         = 0b10,
	FULL_BRIDGE_REVERCE = 0b11,
};
const struct PWMModule_OutputConfig PWMModule_OutputConfig = {
	SINGLE,
	FULL_BRIDGE_FORWARD,
	HALF_BRIDGE,
	FULL_BRIDGE_REVERCE,
};

enum PWMModule_OutputPolarity_Constants {
	ACTIVE_HIGH_ACTIVE_HIGH = 0b1100,
	ACTIVE_HIGH_ACTIVE_LOW  = 0b1101,
	ACTIVE_LOW_ACTIVE_HIGH  = 0b1110,
	ACTIVE_LOW_ACTIVE_LOW   = 0b1111,
};
const struct PWMModule_OutputPolarity PWMModule_OutputPolarity = {
	ACTIVE_HIGH_ACTIVE_HIGH,
	ACTIVE_HIGH_ACTIVE_LOW,
	ACTIVE_LOW_ACTIVE_HIGH,
	ACTIVE_LOW_ACTIVE_LOW,
};

#endif

#ifndef CCP1_MODULE_DECLARED
#define CCP1_MODULE_DECLARED

#define CCPxM CCP1CONbits.CCP1M
#define CxTSEL CCPTMRSbits.C1TSEL
#define DCxB CCP1CONbits.DC1B
#define CCPRxL CCPR1L
#define CCPRxH CCPR1H
#define PxM CCP1CONbits.P1M
#define CaptureModule_(name) CaptureModule1_##name
#define CompareModule_(name) CompareModule1_##name
#define PWMModule_(name) PWMModule1_##name

#elif !defined(CCP2_MODULE_DECLARED)
#define CCP2_MODULE_DECLARED

#define CCPxM CCP2CONbits.CCP2M
#define CxTSEL CCPTMRSbits.C2TSEL
#define DCxB CCP2CONbits.DC2B
#define CCPRxL CCPR2L
#define CCPRxH CCPR2H
#define PxM CCP2CONbits.P2M
#define CaptureModule_(name) CaptureModule2_##name
#define CompareModule_(name) CompareModule2_##name
#define PWMModule_(name) PWMModule2_##name

#elif !defined(CCP3_MODULE_DECLARED)
#define CCP3_MODULE_DECLARED

#define CCPxM CCP3CONbits.CCP3M
#define CxTSEL CCPTMRSbits.C3TSEL
#define DCxB CCP3CONbits.DC3B
#define CCPRxL CCPR3L
#define CCPRxH CCPR3H
#define CaptureModule_(name) CaptureModule3_##name
#define CompareModule_(name) CompareModule3_##name
#define PWMModule_(name) PWMModule3_##name

#elif !defined(CCP4_MODULE_DECLARED)
#define CCP4_MODULE_DECLARED

#define CCPxM CCP4CONbits.CCP4M
#define CxTSEL CCPTMRSbits.C4TSEL
#define DCxB CCP4CONbits.DC4B
#define CCPRxL CCPR4L
#define CCPRxH CCPR4H
#define CaptureModule_(name) CaptureModule4_##name
#define CompareModule_(name) CompareModule4_##name
#define PWMModule_(name) PWMModule4_##name

#define EXIT_LOOP
#endif

// ----------------------------------------------------------------------------
// CaptureModule
// ----------------------------------------------------------------------------
static uint16_t CaptureModule_(getCapturedCount)() {
	return ((uint16_t)CCPRxH << 8) + CCPRxL;
}

static const struct Capture CaptureModule_(instance) = {
	CaptureModule_(getCapturedCount),
};

const struct Capture* CaptureModule_(constructor)(
		char mode) {
	CCPxM = mode;
	return &CaptureModule_(instance);
}

void CaptureModule_(destructor)() {
	CCPxM = 0;
}

// ----------------------------------------------------------------------------
// CompareModule
// ----------------------------------------------------------------------------
static void CompareModule_(setComparedCount)(uint16_t count) {
	CCPRxH = count >> 8;
	CCPRxL = count;
}

static const struct Compare CompareModule_(instance) = {
	CompareModule_(setComparedCount),
};

const struct Compare* CompareModule_(constructor)(
		char mode) {
	CCPxM = mode;
	return &CompareModule_(instance);
}

void CompareModule_(destructor)() {
	CCPxM = 0;
}

// ----------------------------------------------------------------------------
// PWMModule
// ----------------------------------------------------------------------------
static void PWMModule_(setDutyCycle)(uint16_t dutyCycle) {
	CCPRxL = dutyCycle >> 2;
	DCxB = dutyCycle;
}

static const struct PWM PWMModule_(instance) = {
	PWMModule_(setDutyCycle),
};

#ifdef PxM
const struct PWM* PWMModule_(constructor)(
		char baseTimer,
		char outputConfig,
		char outputPolarity) {
	CxTSEL = baseTimer;
	PxM = outputConfig;
	CCPxM = outputPolarity;
	return &PWMModule_(instance);
}
#else
const struct PWM* PWMModule_(constructor)(
		char baseTimer,
		char outputPolarity) {
	CxTSEL = baseTimer;
	// CCP4 and CCP5 don't have configurable output (single output only).
	CCPxM = outputPolarity;
	return &PWMModule_(instance);
}
#endif

void PWMModule_(destructor)() {
	CCPxM = 0;
}

#undef CCPxM
#undef CxTSEL
#undef DCxB
#undef CCPRxL
#undef CCPRxH
#undef PxM
#undef CaptureModule_
#undef CompareModule_
#undef PWMModule_

#ifndef EXIT_LOOP
#include "CCPModule.c"
#endif

