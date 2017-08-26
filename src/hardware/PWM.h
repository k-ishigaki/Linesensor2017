#ifndef PWM_H
#define PWM_H

#include <stdint.h>

/**
 * Configurator of PWM output.
 */
struct PWM {
	/**
	 * Set duty cycle count.
	 *
	 * @param duty cycle count
	 */
	void (*setDutyCycle)(uint16_t);
};

#endif /* PWM_H */
