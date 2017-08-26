#ifndef APPLICATION_H
#define APPLICATION_H

/**
 * Initialize almost all instances and ready for application.
 *
 * This method is called by main method.
 */
void initilize(void);

/**
 * This method called by main loop when any other interrupts or tasks running.
 */
void idle(void);

#endif /* APPLICATION_H */
