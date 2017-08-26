#ifndef PHOTO_TRANSISTOR_H
#define PHOTO_TRANSISTOR_H

struct PhotoTransistor {
	int (*read)(void);
};

#endif /* PHOTO_TRANSISTOR_H */
