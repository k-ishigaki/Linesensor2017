#ifndef INTERRUPT_ON_CHANGE_H
#define INTERRUPT_ON_CHANGE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint8_t positions;
	uint8_t status;
} InterruptOnChange_ChangedPins;

typedef struct {

	/**
	 * Get pin positions which state have been changed.
	 *
	 * The detection of pin state change is conducted after previous
	 * end of interrupt on change (IOC) interrupt or resets.
	 * This method must be called while IOC interrupt so that a you can
	 * detect changed pin positions (and some device must clear interrupt
	 * flags in it).
	 *
	 * You cannnot obtain changed pin status (ex rising edge or falling
	 * edge). If you want to obtain these, use IOPort#read 'before' calling
	 * this method. But the results of these are not under warranty.
	 * (The correctness depends on device hardware structure.)
	 *
	 * A return value represented by bit string. example:
	 * {@code
	 * uint8_t pos = ioc->getChangedPinPositions();
	 * if(pos & 0b00000001) {
	 * 	// bit 0 is changed
	 * }
	 * if(pos & 0b00011000) {
	 * 	// bit 3 and 4 are changed
	 * }
	 * }
	 *
	 * @return changed pin positions and status
	 */
	InterruptOnChange_ChangedPins* (*getChangedPins)();
} InterruptOnChange;


#endif /* INTERRUPT_ON_CHANGE_H */
