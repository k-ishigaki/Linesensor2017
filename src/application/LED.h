#ifndef LED_H
#define LED_H

struct LED {
	void (*turnOn)(void);
	void (*turnOff)(void);
};

#endif /* LED_H */
