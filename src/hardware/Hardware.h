/*
 * Hardware.h
 * definitions for PIC16F1825
 */
#ifndef HARDWARE_H
#define HARDWARE_H

// ----------------------------------------------------------------------------
// device configurations
// ----------------------------------------------------------------------------
// CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin
#pragma config CLKOUTEN = OFF
// WDT disabled
#pragma config WDTE = OFF
// PWRT disabled
#pragma config PWRTE = OFF
// Program memory code protection is disabled
#pragma config CP = OFF
// Brown-out Reset disabled
#pragma config BOREN = OFF
// Fail-Safe Clock Monitor is disabled
#pragma config FCMEN = OFF
// MCLR/VPP pin function is MCLR
#pragma config MCLRE = ON
// Data memory code protection is disabled
#pragma config CPD = OFF
// Internal/External Switchover mode is disabled
#pragma config IESO = OFF
// INTOSC oscillator: I/O function on CLKIN pin
#pragma config FOSC = INTOSC
// Stack Overflow or Underflow will cause a Reset
#pragma config STVREN = ON
// Brown-out Reset Voltage (Vbor), low trip point selected.
#pragma config BORV = LO
// Low-voltage programming enabled
#pragma config LVP = ON
// Write protection off
#pragma config WRT = OFF
// 4x PLL enabled
#pragma config PLLEN = ON

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------
#define OPERATING_VOLTAGE   5.0
#define OPERATING_FREQUENCY 32000000L

// ----------------------------------------------------------------------------
// NativeInterrupts
// ----------------------------------------------------------------------------
#include "NativeInterrupts.h"

// ----------------------------------------------------------------------------
// AlternatePinFunction
// ----------------------------------------------------------------------------
struct AlternatePinFunction_RXAndDT {
	char RC5;
	char RA1;
};
extern const struct AlternatePinFunction_RXAndDT AlternatePinFunction_RXAndDT;

struct AlternatePinFunction_SDO {
	char RC2;
	char RA4;
};
extern const struct AlternatePinFunction_SDO AlternatePinFunction_SDO;

struct AlternatePinFunction_SS {
	char RC3;
	char RA3;
};
extern const struct AlternatePinFunction_SS AlternatePinFunction_SS;

struct AlternatePinFunction_T1G {
	char RA4;
	char RA3;
};
extern const struct AlternatePinFunction_T1G AlternatePinFunction_T1G;

struct AlternatePinFunction_TXAndCK {
	char RC4;
	char RA0;
};
extern const struct AlternatePinFunction_TXAndCK AlternatePinFunction_TXAndCK;

struct AlternatePinFunction_P1D {
	char RC2;
	char RC0;
};
extern const struct AlternatePinFunction_P1D AlternatePinFunction_P1D;

struct AlternatePinFunction_P1C {
	char RC3;
	char RC1;
};
extern const struct AlternatePinFunction_P1C AlternatePinFunction_P1C;

struct AlternatePinFunction_P2B {
	char RC2;
	char RA4;
};
extern const struct AlternatePinFunction_P2B AlternatePinFunction_P2B;

struct AlternatePinFunction_CCP2 {
	char RC3;
	char RA5;
};
extern const struct AlternatePinFunction_CCP2 AlternatePinFunction_CCP2;

// ----------------------------------------------------------------------------
// OscillatorModule
// ----------------------------------------------------------------------------
struct OscillatorModule_InternalClockFrequency {
	char HF_16MHz;
	char HF_8MHz;
	char HF_4MHz;
	char HF_2MHz;
	char HF_1MHz;
	char HF_500kHz;
	char HF_250kHz;
	char HF_125kHz;
	char MF_500kHz;
	char MF_250kHz;
	char MF_125kHz;
	char MF_62500Hz;
	char HF_31250Hz;
	char MF_31250Hz;
	char LF_31kHz;
};
extern const struct OscillatorModule_InternalClockFrequency OscillatorModule_InternalClockFrequency;

struct OscillatorModule_PhaseLockedLoop {
	char ENABLE;
	char DISABLE;
};
extern const struct OscillatorModule_PhaseLockedLoop OscillatorModule_PhaseLockedLoop;

struct OscillatorModule_SystemClockSource {
	/** Internal oscillator block */
	char INTERNAL;
	/** Secondary (SOSC) oscillator */
	char SECONDARY;
	/** Primary clock (determined by FOSC<3:0> in CONFIG1H)  */
	char DETERMINED_BY_CONFIG;
};
extern const struct OscillatorModule_SystemClockSource OscillatorModule_SystemClockSource;

// ----------------------------------------------------------------------------
// IOPort
// ----------------------------------------------------------------------------
#include "IOPort.h"

struct IOPort_PinMode {
	char DIGITAL_INPUT;
	char DIGITAL_INPUT_WITH_INTERNAL_PULLUP;
	char DIGITAL_OUTPUT;
	char ANALOG_INPUT;
};

/** defined at IOPort.c */
extern const struct IOPort_PinMode IOPort_PinMode;

// ----------------------------------------------------------------------------
// ADConverterModule
// ----------------------------------------------------------------------------
#include "ADConverter.h"

struct ADConverterModule_PositiveReference {
	char FVR;
	char VREF_PLUS;
	char VDD;
};

extern const struct ADConverterModule_PositiveReference ADConverterModule_PositiveReference;

struct ADConverterModule_NegativeReference {
	char VREF_MINUS;
	char VSS;
};

extern const struct ADConverterModule_NegativeReference ADConverterModule_NegativeReference;

struct ADConverterModule_ConversionClock {
	char F_RC;
	char F_OSC_DIV_64;
	char F_OSC_DIV_32;
	char F_OSC_DIV_16;
	char F_OSC_DIV_8;
	char F_OSC_DIV_4;
	char F_OSC_DIV_2;
};

extern const struct ADConverterModule_ConversionClock ADConverterModule_ConversionClock;

struct ADConverterModule_InputChannel {
	char FVR_BUFFER_1;
	char DAC;
	char TEMPERATURE_INDICATOR;
	char AN7;
	char AN6;
	char AN5;
	char AN4;
	char AN3;
	char AN2;
	char AN1;
	char AN0;
};

extern const struct ADConverterModule_InputChannel ADConverterModule_InputChannel;

// ----------------------------------------------------------------------------
// TimerModule
// ----------------------------------------------------------------------------
#include "TimerModule.h"

struct Timer0Module_ClockSource {
	/** external T0CKI pin */
	char T0CKI;
	/** capacitive sensing oscillator */
	char CPSCLK;
	/** internal instruction cycle clock */
	char F_OSC_DIV_4;
};
extern const struct Timer0Module_ClockSource Timer0Module_ClockSource;

struct Timer0Module_Prescaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_4;
	char RATE_1_8;
	char RATE_1_16;
	char RATE_1_32;
	char RATE_1_64;
	char RATE_1_128;
	char RATE_1_256;
};
extern const struct Timer0Module_Prescaler Timer0Module_Prescaler;

// timer0 module postscaler is not selectable

struct Timer1Module_ClockSource {
	/**
	 * delicated low-power 32.768kHz oscillator circuit
	 * between pins T1OSI and T1OSO
	 */
	char T1OSC_SYNC;
	/**
	 * delicated low-power 32.768kHz oscillator circuit
	 * (not sync with Fosc)
	 * between pins T1OSI and T1OSO
	 */
	char T1OSC_NOT_SYNC;
	/** capacitive sensing oscillator */
	char CPSCLK_SYNC;
	/** capacitive sensing oscillator (not sync with Fosc) */
	char CPSCLK_NOT_SYNC;
	/** external clock on T1CKI pin */
	char T1CKI_SYNC;
	/** external clock on T1CKI pin (not sync with Fosc) */
	char T1CKI_NOT_SYNC;
	/** system clock */
	char F_OSC;
	/** internal instruction cycle clock */
	char F_OSC_DIV_4;
};
extern const struct Timer1Module_ClockSource Timer1Module_ClockSource;

struct Timer1Module_Prescaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_4;
	char RATE_1_8;
};
extern const struct Timer1Module_Prescaler Timer1Module_Prescaler;

struct Timer1GateControl_Source {
	/** timer1 gate pin */
	char T1G;
	/** overflow of timer0 */
	char TIMER0_OVERFLOW;
	/** comparator1 output */
	char SYNC_C1OUT;
	/** comparator2 output */
	char SYNC_C2OUT;
};
extern const struct Timer1_GateControlSource Timer1_GateControlSource;

struct Timer1GateControl_Mode {
	char ENABLE_POSITIVE;
	char ENABLE_NEGATIVE;
	char TOGGLE_POSITIVE;
	char TOGGLE_NEGATIVE;
	char SINGLE_PULSE_POSITIVE;
	char SINGLE_PULSE_NEGATIVE;
	char TOGGLE_AND_SINGLE_PULSE_POSITIVE;
	char TOGGLE_AND_SINGLE_PULSE_NEGATIVE;
};
extern const struct Timer1GateControl_Mode Timer1GateControl_Mode;

// timer2/4/6 module have only one clock source (Fosc/4)

struct Timer2Module_Prescaler {
	char RATE_1_1;
	char RATE_1_4;
	char RATE_1_16;
	char RATE_1_64;
};
extern const struct Timer2Module_Prescaler Timer2Module_Prescaler;

struct Timer2Module_Postscaler {
	char RATE_1_1;
	char RATE_1_2;
	char RATE_1_3;
	char RATE_1_4;
	char RATE_1_5;
	char RATE_1_6;
	char RATE_1_7;
	char RATE_1_8;
	char RATE_1_9;
	char RATE_1_10;
	char RATE_1_11;
	char RATE_1_12;
	char RATE_1_13;
	char RATE_1_14;
	char RATE_1_15;
	char RATE_1_16;
};
extern const struct Timer2Module_Postscaler Timer2Module_Postscaler;

// ----------------------------------------------------------------------------
// CCPModule
// ----------------------------------------------------------------------------
#include "Capture.h"
#include "Compare.h"
#include "PWM.h"

struct CaptureModule_Mode {
	char EVERY_FALLING_EDGE;
	char EVERY_RISING_EDGE;
	char EVERY_4TH_RISING_EDGE;
	char EVERY_16TH_RISING_EDGE;
};
extern const struct CaptureModule_Mode CaptureModule_Mode;

struct CompareModule_Mode {
	/**
	 * initialize ECCPx pin low
	 *
	 * set output on compare match (set CCPxIF)
	 */
	char LOW_TO_HIGH;
	/**
	 * initialize ECCPx pin high
	 *
	 * clear output on compare match (set CCPxIF)
	 */
	char HIGH_TO_LOW;
	/**
	 * generate software interrupt only
	 *
	 * ECCPx pin reverts to I/O state
	 */
	char SOFTWARE_INTERRUPT;
	/**
	 *  Special Event Trigger(not implemented on CCP4 and CCP5)
	 *
	 *  (ECCPx resets Timer, sets CCPxIF bit starts A/D conversion if A/D
	 *  module is enabled)
	 */
	char SPECIAL_EVENT_TRIGGER;
};
extern const struct CompareModule_Mode CompareModule_Mode;

struct PWMModule_BaseTimer {
	char TIMER2;
	char TIMER4;
	char TIMER6;
};
extern const struct PWMModule_BaseTimer PWMModule_BaseTimer;

struct PWMModule_OutputConfig {
	char SINGLE;
	char FULL_BRIDGE_FORWARD;
	char HALF_BRIDGE;
	char FULL_BRIDGE_REVERCE;
};
extern const struct PWMModule_OutputConfig PWMModule_OutputConfig;

struct PWMModule_OutputPolarity {
	/**
	 * PxA, PxC active-high; PxB, PxD active-high
	 */
	char ACTIVE_HIGH_ACTIVE_HIGH;
	/**
	 * PxA, PxC active-high; PxB, PxD active-low
	 */
	char ACTIVE_HIGH_ACTIVE_LOW;
	/**
	 * PxA, PxC active-low; PxB, PxD active-high
	 */
	char ACTIVE_LOW_ACTIVE_HIGH;
	/**
	 * PxA, PxC active-low; PxB, PxD active-low
	 */
	char ACTIVE_LOW_ACTIVE_LOW;
};
extern const struct PWMModule_OutputPolarity PWMModule_OutputPolarity;

// ----------------------------------------------------------------------------
// FixedVoltageReference
// ----------------------------------------------------------------------------
struct FixedVoltageReference_Buffer1Reference {
	char OFF;
	char OUTPUT_1x;
	char OUTPUT_2x;
	char OUTPUT_4x;
};
extern const struct FixedVoltageReference_Buffer1Reference FixedVoltageReference_Buffer1Reference;

struct FixedVoltageReference_Buffer2Reference {
	char OFF;
	char OUTPUT_1x;
	char OUTPUT_2x;
	char OUTPUT_4x;
};
extern const struct FixedVoltageReference_Buffer2Reference FixedVoltageReference_Buffer2Reference;

// ----------------------------------------------------------------------------
// USART
// ----------------------------------------------------------------------------
#include "USART.h"

struct EUSART_Mode {
	/**
	 * Asynchronous mode.
	 */
	char ASYNCHRONOUS;
	/**
	 * Synchronous master mode.
	 */
	char SYNCHRONOUS_MASTER;
	/**
	 * Synchronous slave mode.
	 */
	char SYNCHRONOUS_SLAVE;
};
extern const struct EUSART_Mode EUSART_Mode;

struct EUSART_ReceiveMode {
	/**
	 * 8bit reception mode.
	 */
	char EIGHT_BIT;
	/**
	 * 9bit reception mode.
	 */
	char NINE_BIT;
	/**
	 * 9bit reception mode with address detection (asynchronous mode only)
	 */
	char NINE_BIT_ADDRESS_DETECTION;
};
extern const struct EUSART_ReceiveMode EUSART_ReceiveMode;

struct EUSART_TransmitMode {
	/**
	 * 8bit transmission mode.
	 */
	char EIGHT_BIT;
	/**
	 * 9bit transmission mode.
	 *
	 * This mode is used for address detection.
	 */
	char NINE_BIT;
};
extern const struct EUSART_TransmitMode EUSART_TransmitMode;



struct EUSART_Polarity {
	/**
	 * Non inverted in asynchronous mode, falling edge in synchronous mode.
	 */
	char NON_INVERTED_OR_FALLING_EDGE;
	/**
	 * Inverted in asynchronous mode, rising edge in synchronous mode.
	 */
	char INVERTED_OR_RISING_EDGE;
};
extern const struct EUSART_Polarity EUSART_Polarity;

struct EUSART_Error {
	/**
	 * Framing error mask.
	 */
	char FRAMING;
	/**
	 * Overrun error mask.
	 */
	char OVERRUN;
};
extern const struct EUSART_Error EUSART_Error;

// ----------------------------------------------------------------------------
// MSSP
// ----------------------------------------------------------------------------
#include "I2C.h"

struct I2C_SlewRateControl {
	/**
	 * Slew rate control enabled for high speed mode (400 kHz)
	 */
	char ENABLE;
	/**
	 * Slew rate control disabled for standard speed mode
	 * (100 kHz and 1 MHz)
	 */
	char DISABLE;
};
extern const struct I2C_SlewRateControl I2C_SlewRateControl;

struct I2C_InputThreshold {
	/**
	 * Disable SMbus specific inputs
	 */
	char DEFAULT;
	/**
	 * Enable input logic so that thresholds are compliant
	 * with SMbus specification
	 */
	char SMBUS;
};
extern const struct I2C_InputThreshold I2C_InputThreshold;

struct I2C_GeneralCallInterrupt {
	/**
	 * General call address disabled
	 */
	char DISABLE;
	/**
	 * Enable interrupt when a general call address (0x00 or 00h)
	 * is received in the SSPxSR
	 */
	char ENABLE;
};
extern const struct I2C_GeneralCallInterrupt I2C_GeneralCallInterrupt;

struct I2C_ConditionInterrupt {
	/**
	 * Start and Stop detection interrupts are disabled
	 */
	char DISABLE;
	/**
	 * Enable interrupt on detection of Start or Restart conditions
	 */
	char START;
	/**
	 * Enable interrupt on detection of Stop condition
	 */
	char STOP;
	/**
	 * Enable interrupt on detection of Start or Restart or Stop conditions
	 */
	char START_AND_STOP;
};
extern const struct I2C_ConditionInterrupt I2C_ConditionInterrupt;

struct I2C_SDAHoldTime {
	/**
	 * Minimum of 100 ns hold time on SDAx after the falling edge of SCLx
	 */
	char ONE_HUNDRED_NS;
	/**
	 * Minimum of 300 ns hold time on SDAx after the falling edge of SCLx
	 */
	char THREE_HUNDRED_NS;
};
extern const struct I2C_SDAHoldTime I2C_SDAHoldTime;

struct I2C_SlaveBusCollisionDetect {
	char DISABLE;
	char ENABLE;
};
extern const struct I2C_SlaveBusCollisionDetect I2C_SlaveBusCollisionDetect;

struct I2C_ClockStretch {
	char ADDRESS;
	char DATA;
	char ADDRESS_AND_DATA;
	char DISABLE;
};
extern const struct I2C_ClockStretch I2C_ClockStretch;






/**
 * Hardware peripheral definition.
 */
struct Hardware {
	/**
	 * Interrupt service constructor.
	 */
	const struct InterruptService* (*ADConverterInterruptService)();
	const struct InterruptService* (*Timer0InterruptService)();
	const struct InterruptService* (*Timer1InterruptService)();
	const struct InterruptService* (*Timer1GateControlInterruptService)();
	const struct InterruptService* (*Timer2InterruptService)();
	const struct InterruptService* (*Timer4InterruptService)();
	const struct InterruptService* (*Timer6InterruptService)();
	const struct InterruptService* (*CCP1InterruptService)();
	const struct InterruptService* (*CCP2InterruptService)();
	const struct InterruptService* (*CCP3InterruptService)();
	const struct InterruptService* (*CCP4InterruptService)();

	/**
	 * Configure alternate pin function.
	 *
	 * @param RX and DT
	 * @param SDO
	 * @param SS
	 * @param T1G
	 * @param TX and CK
	 * @param P1D
	 * @param P1C
	 * @param P2B
	 * @param CCP2
	 */
	void (*configureAlternatePinFunction)(char, char, char, char, char, char, char, char, char);

	/**
	 * Configure oscillator module.
	 *
	 * @param identifier of internal clock frequency
	 * @param identifier of phase locked loop
	 * @param identifier of system clock source
	 */
	void (*configureOscillator)(char, char, char);

	const struct IOPort* (*PortA)();
	const struct IOPort* (*PortC)();

	/**
	 * AD converter constructor.
	 *
	 * @param positie reference
	 * @param negative reference
	 * @param conversion clock
	 */
	const struct ADConverter* (*ADConverterModule)(char, char, char);

	/**
	 * Timer0 constructor.
	 *
	 * @param clock source
	 * @param prescaler
	 */
	const TimerModule* (*Timer0)(char, char);

	/**
	 * Timer1 constructor.
	 *
	 * @param clock source
	 * @param prescaler
	 */
	const TimerModule* (*Timer1)(char, char);

	/**
	 * Timer1 gate control constructor.
	 *
	 * @param source
	 * @param mode
	 */
	const TimerGateControl* (*Timer1GateControl)(char, char);

	/**
	 * Timer2/4/6 constructor.
	 *
	 * @param prescaler
	 * @param postscaler
	 * @param period count
	 */
	const TimerModule* (*Timer2)(char, char, uint8_t);
	const TimerModule* (*Timer4)(char, char, uint8_t);
	const TimerModule* (*Timer6)(char, char, uint8_t);

	/**
	 * Capture1/2/3/4 constructor.
	 *
	 * @param mode
	 */
	const struct Capture* (*Capture1Module)(char);
	const struct Capture* (*Capture2Module)(char);
	const struct Capture* (*Capture3Module)(char);
	const struct Capture* (*Capture4Module)(char);

	/**
	 * Compare1/2/3/4 constructor.
	 *
	 * @param mode
	 */
	const struct Compare* (*Compare1Module)(char);
	const struct Compare* (*Compare2Module)(char);
	const struct Compare* (*Compare3Module)(char);
	const struct Compare* (*Compare4Module)(char);

	/**
	 * PWM1/2 constructor.
	 *
	 * @param base timer
	 * @param output config
	 * @param output polarity
	 */
	const struct PWM* (*EnhancedPWM1Module)(char, char, char);
	const struct PWM* (*EnhancedPWM2Module)(char, char, char);
	/**
	 * PWM3/4 constructor
	 *
	 * @param base timer
	 * @param output polarity
	 */
	const struct PWM* (*PWM3Module)(char, char);
	const struct PWM* (*PWM4Module)(char, char);

	/**
	 * Configure fixed voltage reference.
	 *
	 * @param buffer1 reference
	 * @param buffer2 reference
	 */
	void (*configureFixedVoltageReference)(char, char);
	/**
	 * Universal receiver transmitter constructor.
	 *
	 * @param operating mode
	 * @param receive mode
	 * @param transmit mode
	 * @param polarity
	 * @param baudrate
	 */
	const struct USART* (*EUSART)(char, char, char, char, unsigned long);
};

/**
 * Hardware singleton instance.
 * This is declared at Hardware.c
 */
extern const struct Hardware Hardware;

#endif /* HARDWARE_H */
