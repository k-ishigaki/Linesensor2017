#ifndef ANALOG_INPUT_PIN_H
#define ANALOG_INPUT_PIN_H

struct AnalogInputPin {
	int (*read)(void);
};

#endif /* ANALOG_INPUT_PIN_H */
