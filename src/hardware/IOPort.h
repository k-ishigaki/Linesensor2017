#ifndef IO_PORT_H
#define IO_PORT_H

#include <stdint.h>

/**
 * Defines IO port characteristics includes port configs.
 *
 * A function of ADC is not included because ADC module is not part of
 * IO port module.
 *
 * usage: write to output latch
 * {@code
 * const struct IOPort* port = Hardware.PortA; // get instance of Port A
 * // set all pins to digital output
 * port->setPinModes(0xFF, IOPort_PinMode.DIGITAL_OUTPUT);
 * port->writeDigital(0x55);     // pin 0, 2, 4, 6: output high
 *                               // pin 1, 3, 5, 7: output low
 * }
 *
 * usage: read port status
 * {@code
 * const struct IOPort* port = Hardware.PortA;
 * // set all pins to digital input
 * port->setPinModes(0xFF, IOPort_PinMode.DIGITAL_INPUT);
 * uint8_t result = port->readDigital(); // read port and store
 * }
 */
struct IOPort {

	/**
	 * Apply pin mode to selected pins.
	 *
	 * You can select pins at first argument, and pin mode at second
	 * argument.
	 * The pin mode is defined at Hardware.h.
	 * Please check data sheet not to select unsupported pins.
	 *
	 * For example:
	 * {@code
	 * // set pin 0 and pin 4 to digital input
	 * port->setPinModes(0b00010001, IOPort_PinMode.DIGITAL_INPUT);
	 * }
	 *
	 * @param pin positions
	 * @param pin mode
	 */
	void (*setPinModes)(uint8_t, char);

	/**
	 * Read levels on the digital input pins.
	 *
	 * If a pin is not digital input, the return value is not specified.
	 *
	 * @return 1 if high level , else 0 for respective pins
	 */
	uint8_t (*read)(void);

	/**
	 * Write outputs to digital output pins.
	 *
	 * If a pin is not digital output or not selected by first argument,
	 * its state is unchanged.
	 *
	 * @param pin positions
	 * @param a output levels for respective pins<br>
	 * 	1 = output high<br>
	 * 	0 = output low
	 */
	void (*write)(uint8_t, uint8_t);

	/**
	 * Toggle outputs of digital output pins.
	 *
	 * If a pin is not digital output of not selected by first arguments,
	 * its status is unchanged.
	 *
	 * @param pin positions
	 */
	void (*toggle)(uint8_t);
};

#endif /* IO_PORT_H */
