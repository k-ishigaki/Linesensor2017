#ifndef CAPTURE_H
#define CAPTURE_H

#include <stdint.h>

/**
 * Captures pin event and gets timer count value of that time.
 *
 * The got timer count is obtained at Capture#getCapturedCount.
 */
struct Capture {
	/**
	 * Get the captured timer count value/
	 *
	 * If capture event occured when reading captured count,
	 * the value may be uncorrect.
	 */
	uint16_t (*getCapturedCount)(void);
};

#endif /* CAPTURE_H */
