#ifndef COMPARE_H
#define COMPARE_H

#include <stdint.h>

/**
 * Compare presetting count value with base timer count value.
 *
 * On compare matched, a event occur.
 * The event may be user settable. (ex: software interrupt)
 */
struct Compare {
	/**
	 * Set count value compared with base timer count.
	 *
	 * The count value range depend on that of base timer.
	 */
	void (*setComparedCount)(uint16_t);
};

#endif /* COMPARE_H */
