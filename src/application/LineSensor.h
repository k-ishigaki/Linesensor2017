#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include "LED.h"
#include "PhotoTransistor.h"

struct LineSensor {
	const struct LED* (*getLED0)(void);    // left edge
	const struct PhotoTransistor* (*getPhotoTransistor0)(void);
	const struct LED* (*getLED1)(void);
	const struct PhotoTransistor* (*getPhotoTransistor1)(void);
	const struct LED* (*getLED2)(void);
	const struct PhotoTransistor* (*getPhotoTransistor2)(void);
	const struct LED* (*getLED3)(void);
	const struct PhotoTransistor* (*getPhotoTransistor3)(void);
	// const struct LED* (*getLED0)(void); // right edge
};
extern const struct LineSensor LineSensor;

#endif /* LINE_SENSOR_H */
