#include <xc.h>
#include "Hardware.h"

#ifndef DECLARED_ONCE
#define DECLARED_ONCE
// ----------------------------------------------------------------------------
// Timer0Module_Constants
// ----------------------------------------------------------------------------
enum Timer0Module_ClockSource_Constants {
	T0_T0CKI       = 0b01,
	T0_CPSCLK      = 0b11,
	T0_F_OSC_DIV_4 = 0b00,
};
const struct Timer0Module_ClockSource Timer0Module_ClockSource = {
	T0_T0CKI,
	T0_CPSCLK,
	T0_F_OSC_DIV_4,
};

enum Timer0Module_Prescaler_Constants {
	T0_RATE_1_1,
	T0_RATE_1_2   = 0b000,
	T0_RATE_1_4   = 0b001,
	T0_RATE_1_8   = 0b010,
	T0_RATE_1_16  = 0b011,
	T0_RATE_1_32  = 0b100,
	T0_RATE_1_64  = 0b101,
	T0_RATE_1_128 = 0b110,
	T0_RATE_1_256 = 0b111,
};
const struct Timer0Module_Prescaler Timer0Module_Prescaler = {
	T0_RATE_1_1,
	T0_RATE_1_2,
	T0_RATE_1_4,
	T0_RATE_1_8,
	T0_RATE_1_16,
	T0_RATE_1_32,
	T0_RATE_1_64,
	T0_RATE_1_128,
	T0_RATE_1_256,
};

// ----------------------------------------------------------------------------
// Timer0Module
// ----------------------------------------------------------------------------
static uint16_t Timer0Module_getCount() {
	return TMR0;
}

static void Timer0Module_setCount(uint16_t count) {
	// note:
	// When TMR0 is written, the increment is inhibited for
	// two instruction cycles immediately following the write
	TMR0 = count;
}

static void Timer0Module_start() {
	// timer0 module is always enabled
}

static void Timer0Module_stop() {
	// timer0 module is always enabled
}

static const TimerModule Timer0Module_instance = {
	Timer0Module_getCount,
	Timer0Module_setCount,
	Timer0Module_start,
	Timer0Module_stop,
};

const TimerModule* Timer0Module_constructor(
		char clockSource,
		char prescaler) {
	// decide clock source
	CPSCON0bits.T0XCS = clockSource;
	OPTION_REGbits.TMR0CS = clockSource >> 1;
	// decide prescaler
	if(prescaler == T0_RATE_1_1) {
		OPTION_REGbits.PSA = 1;
	} else {
		OPTION_REGbits.PSA = 0;
		OPTION_REGbits.PS  = prescaler;
	}
	return &Timer0Module_instance;
}

// ----------------------------------------------------------------------------
// Timer1Module_Constants
// ----------------------------------------------------------------------------
enum Timer1Module_ClockSource_Constants {
	T1_T1OSC_SYNC      = 0b0110,
	T1_T1OSC_NOT_SYNC  = 0b1110,
	T1_CPSCLK_SYNC     = 0b0011,
	T1_CPSCLK_NOT_SYNC = 0b1011,
	T1_T1CKI_SYNC      = 0b0010,
	T1_T1CKI_NOT_SYNC  = 0b1010,
	T1_F_OSC           = 0b0001,
	T1_F_OSC_DIV_4     = 0b0000,
};
const struct Timer1Module_ClockSource Timer1Module_ClockSource = {
	T1_T1OSC_SYNC,
	T1_T1OSC_NOT_SYNC,
	T1_CPSCLK_SYNC,
	T1_CPSCLK_NOT_SYNC,
	T1_T1CKI_SYNC,
	T1_T1CKI_NOT_SYNC,
	T1_F_OSC,
	T1_F_OSC_DIV_4,
};

enum Timer1Module_Prescaler_Constants {
	T1_RATE_1_1 = 0b00,
	T1_RATE_1_2 = 0b01,
	T1_RATE_1_4 = 0b10,
	T1_RATE_1_8 = 0b11,
};
const struct Timer1Module_Prescaler Timer1Module_Prescaler = {
	T1_RATE_1_1,
	T1_RATE_1_2,
	T1_RATE_1_4,
	T1_RATE_1_8,
};

// ----------------------------------------------------------------------------
// Timer1Module
// ----------------------------------------------------------------------------
static uint16_t Timer1Module_getCount() {
	// 16bit read/write mode is not available (pic16f)
	// so it is recommended to stop timer before read count
	bool state = T1CONbits.TMR1ON;
	T1CONbits.TMR1ON = 0;
	uint16_t count = ((uint16_t)TMR1H << 8) + TMR1L;
	T1CONbits.TMR1ON = state;
	return count;
}

static void Timer1Module_setCount(uint16_t count) {
	// 16bit read/write mode is not available (pic16f)
	// so it is recommended to stop timer before write count
	bool state = T1CONbits.TMR1ON;
	T1CONbits.TMR1ON = 0;
	TMR1H = count >> 8;
	TMR1L = count;
	T1CONbits.TMR1ON = state;
}

static void Timer1Module_start() {
	T1CONbits.TMR1ON = 1;
}

static void Timer1Module_stop() {
	T1CONbits.TMR1ON = 0;
}

static const TimerModule Timer1Module_instance = {
	Timer1Module_getCount,
	Timer1Module_setCount,
	Timer1Module_start,
	Timer1Module_stop,
};

const TimerModule* Timer1Module_constructor(
		char clockSource,
		char prescaler) {
	// decide clock source
	T1CONbits.TMR1CS  = clockSource;
	T1CONbits.T1OSCEN = clockSource >> 2;
	T1CONbits.nT1SYNC = clockSource >> 3;
	// decide prescaler
	T1CONbits.T1CKPS = prescaler;
	return &Timer1Module_instance;
}

// ----------------------------------------------------------------------------
// Timer1GateControl_Constants
// ----------------------------------------------------------------------------
enum Timer1GateControl_Source_Constants {
	T1G_T1G             = 0b00,
	T1G_TIMER0_OVERFLOW = 0b01,
	T1G_SYNC_C1OUT      = 0b10,
	T1G_SYNC_C2OUT      = 0b11,
};
const struct Timer1GateControl_Source Timer1GateControl_Source = {
	T1G_T1G,
	T1G_TIMER0_OVERFLOW,
	T1G_SYNC_C1OUT,
	T1G_SYNC_C2OUT,
};

enum Timer1GateControl_Mode_Constants {
	ENABLE_POSITIVE                  = 0b100,
	ENABLE_NEGATIVE                  = 0b000,
	TOGGLE_POSITIVE                  = 0b110,
	TOGGLE_NEGATIVE                  = 0b010,
	SINGLE_PULSE_POSITIVE            = 0b101,
	SINGLE_PULSE_NEGATIVE            = 0b001,
	TOGGLE_AND_SINGLE_PULSE_POSITIVE = 0b111,
	TOGGLE_AND_SINGLE_PULSE_NEGATIVE = 0b011,
};
const struct Timer1GateControl_Mode Timer1GateControl = {
	ENABLE_POSITIVE,
	ENABLE_NEGATIVE,
	TOGGLE_POSITIVE,
	TOGGLE_NEGATIVE,
	SINGLE_PULSE_POSITIVE,
	SINGLE_PULSE_NEGATIVE,
	TOGGLE_AND_SINGLE_PULSE_POSITIVE,
	TOGGLE_AND_SINGLE_PULSE_NEGATIVE,
};

// ----------------------------------------------------------------------------
// Timer1GateControl
// ----------------------------------------------------------------------------
static bool Timer1GateControl_getState() {
	return T1GCONbits.T1GVAL;
}

static void Timer1GateControl_startSinglePulseAquisition() {
	T1GCONbits.T1GGO = 1;
}

static bool Timer1GateControl_isWaitingSinglePulse() {
	return T1GCONbits.T1GGO;
}

static const TimerGateControl Timer1GateControl_instance = {
	Timer1GateControl_getState,
	Timer1GateControl_startSinglePulseAquisition,
	Timer1GateControl_isWaitingSinglePulse,
};

const TimerGateControl* Timer1GateControl_constructor(
		char source,
		char mode) {
	T1GCONbits.T1GSS = source;
	T1GCONbits.T1GPOL = mode >> 2;
	T1GCONbits.T1GTM  = mode >> 1;
	T1GCONbits.T1GSPM = mode;
	T1GCONbits.TMR1GE = 1;
	return &Timer1GateControl_instance;
}

void Timer1GateControl_destructor() {
	T1GCONbits.TMR1GE = 0;
}

// ----------------------------------------------------------------------------
// Timer2/4/6Module_Constants
// ----------------------------------------------------------------------------
enum Timer2Module_Prescaler_Constants {
	T2_PRATE_1_1  = 0b00,
	T2_PRATE_1_4  = 0b01,
	T2_PRATE_1_16 = 0b10,
	T2_PRATE_1_64 = 0b11,
};
const struct Timer2Module_Prescaler Timer2Module_Prescaler = {
	T2_PRATE_1_1,
	T2_PRATE_1_4,
	T2_PRATE_1_16,
	T2_PRATE_1_64,
};

enum Timer2Module_Postscaler_Constants {
	T2_RATE_1_1  = 0b0000,
	T2_RATE_1_2  = 0b0001,
	T2_RATE_1_3  = 0b0010,
	T2_RATE_1_4  = 0b0011,
	T2_RATE_1_5  = 0b0100,
	T2_RATE_1_6  = 0b0101,
	T2_RATE_1_7  = 0b0110,
	T2_RATE_1_8  = 0b0111,
	T2_RATE_1_9  = 0b1000,
	T2_RATE_1_10 = 0b1001,
	T2_RATE_1_11 = 0b1010,
	T2_RATE_1_12 = 0b1011,
	T2_RATE_1_13 = 0b1100,
	T2_RATE_1_14 = 0b1101,
	T2_RATE_1_15 = 0b1110,
	T2_RATE_1_16 = 0b1111,
};
const struct Timer2Module_Postscaler Timer2Module_Postscaler = {
	T2_RATE_1_1,
	T2_RATE_1_2,
	T2_RATE_1_3,
	T2_RATE_1_4,
	T2_RATE_1_5,
	T2_RATE_1_6,
	T2_RATE_1_7,
	T2_RATE_1_8,
	T2_RATE_1_9,
	T2_RATE_1_10,
	T2_RATE_1_11,
	T2_RATE_1_12,
	T2_RATE_1_13,
	T2_RATE_1_14,
	T2_RATE_1_15,
	T2_RATE_1_16,
};

#endif

// ----------------------------------------------------------------------------
// Timer2/4/6Module
// ----------------------------------------------------------------------------
#if !defined(TIMER2_MODULE_DECLARED)
#define TIMER2_MODULE_DECLARED

#define TimerxModule_(name) Timer2Module_##name
#define TMRx TMR2
#define TMRxON T2CONbits.TMR2ON
#define TxCKPS T2CONbits.T2CKPS
#define TxOUTPS T2CONbits.T2OUTPS
#define PRx PR2

#elif !defined(TIMER4_MODULE_DECLARED)
#define TIMER4_MODULE_DECLARED

#define TimerxModule_(name) Timer4Module_##name
#define TMRx TMR4
#define TMRxON T4CONbits.TMR4ON
#define TxCKPS T4CONbits.T4CKPS
#define TxOUTPS T4CONbits.T4OUTPS
#define PRx PR4

#elif !defined(TIMER6_MODULE_DECLARED)
#define TIMER6_MODULE_DECLARED

#define TimerxModule_(name) Timer6Module_##name
#define TMRx TMR6
#define TMRxON T6CONbits.TMR6ON
#define TxCKPS T6CONbits.T6CKPS
#define TxOUTPS T6CONbits.T6OUTPS
#define PRx PR6

#define EXIT_LOOP
#endif

static int TimerxModule_(data);

static uint16_t TimerxModule_(getCount)() {
	return TMRx;
}

static void TimerxModule_(setCount)(uint16_t count) {
	TMRx = count;
}

static void TimerxModule_(start)() {
	TMRxON = 1;
}

static void TimerxModule_(stop)() {
	TMRxON = 0;
}

static const TimerModule TimerxModule_(instance) = {
	TimerxModule_(getCount),
	TimerxModule_(setCount),
	TimerxModule_(start),
	TimerxModule_(stop),
};

const TimerModule* TimerxModule_(constructor)(
		char prescaler,
		char postscaler,
		uint8_t periodCount) {
	TxCKPS = prescaler;
	TxOUTPS = postscaler;
	PRx = periodCount;
	return &TimerxModule_(instance);
}

#undef TimerxModule_
#undef TMRx
#undef TMRxON
#undef TxCKPS
#undef TxOUTPS
#undef PRx

#ifndef EXIT_LOOP
#include "TimerModule.c"
#endif
