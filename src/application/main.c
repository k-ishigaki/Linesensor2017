#include <xc.h>
#include "Hardware.h"
#include "LineSensor.h"

#include <stdbool.h>
#include <stdio.h>

#define _XTAL_FREQ OPERATING_FREQUENCY

// RA0 and RA1 are used for debug serial port
// (RA0 : TX, RA1 : RX)
#define RA0_A0_PIN  0b00000001
#define RA1_A1_PIN  0b00000010
#define RA2_A2_PIN  0b00000100
#define RA4_A3_PIN  0b00010000
#define RA5_nSW_PIN 0b00100000
#define RC0_SCL_PIN 0b00000001
#define RC1_SDA_PIN 0b00000010
#define RC2_D0_PIN  0b00000100
#define RC3_D1_PIN  0b00001000
#define RC4_D2_PIN  0b00010000
#define RC5_D3_PIN  0b00100000

static const struct USART* serial;
static const struct LED* leds[4];
static const struct PhotoTransistor* photoTrs[4];

void putch(char data) {
	serial->write(data);
}

void setup() {
	Hardware.configureAlternatePinFunction(
			AlternatePinFunction_RXAndDT.RA1,
			AlternatePinFunction_SDO.RA4,
			AlternatePinFunction_SS.RA3,
			AlternatePinFunction_T1G.RA3,
			AlternatePinFunction_TXAndCK.RA0,
			AlternatePinFunction_P1D.RC0,
			AlternatePinFunction_P1C.RC1,
			AlternatePinFunction_P2B.RA4,
			AlternatePinFunction_CCP2.RA5);
	Hardware.configureOscillator(
			OscillatorModule_InternalClockFrequency.HF_8MHz,
			OscillatorModule_PhaseLockedLoop.ENABLE,
			OscillatorModule_SystemClockSource.DETERMINED_BY_CONFIG);

	// get line sensor hardware instances
	leds[0] = LineSensor.getLED0();
	leds[1] = LineSensor.getLED1();
	leds[2] = LineSensor.getLED2();
	leds[3] = LineSensor.getLED3();
	photoTrs[0] = LineSensor.getPhotoTransistor0();
	photoTrs[1] = LineSensor.getPhotoTransistor1();
	photoTrs[2] = LineSensor.getPhotoTransistor2();
	photoTrs[3] = LineSensor.getPhotoTransistor3();
	const struct IOPort* portA = Hardware.PortA();
	const struct IOPort* portC = Hardware.PortC();

	// switch input pin
	portA->setPinModes(
			RA5_nSW_PIN,
			IOPort_PinMode.DIGITAL_INPUT_WITH_INTERNAL_PULLUP);

	// debug serial TX pin
	portA->setPinModes(RA0_A0_PIN, IOPort_PinMode.DIGITAL_OUTPUT);
	// debug serial RX pin
	portA->setPinModes(RA1_A1_PIN, IOPort_PinMode.DIGITAL_INPUT);
	// debug serial settings
	serial = Hardware.EUSART(
			EUSART_Mode.ASYNCHRONOUS,
			EUSART_ReceiveMode.EIGHT_BIT,
			EUSART_TransmitMode.EIGHT_BIT,
			EUSART_Polarity.NON_INVERTED_OR_FALLING_EDGE,
			115200L);
	// i2c pins
	portC->setPinModes(
			RC0_SCL_PIN | RC1_SDA_PIN,
			IOPort_PinMode.ANALOG_INPUT);
}

void loop() {
	for (int i = 0; i < 100; i++) {
		__delay_ms(10);
	}
	leds[3]->turnOn();
	for (int i = 0; i < 10; i++) {
		__delay_ms(10);
	}
	printf("res = %d\r\n", photoTrs[2]->read());
	leds[3]->turnOff();

//	if(!(portA->read() & RA5_nSW_PIN)) {
//		printf("pushed\r\n");
//	}

	serial->write('A');
	serial->write('B');
	serial->write('C');
	serial->write('D');
	serial->write('\n');
}

int main(void) {
	setup();
	while(true) {
		loop();
	}
}
