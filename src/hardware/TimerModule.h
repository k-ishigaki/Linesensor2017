#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Timer module interface.
 * If you want to use timer overflow interrupt, use InterruptService
 * interface.
 */
typedef struct {

	/**
	 * Get counter value of timer module.
	 *
	 * At several device, countup operation is stoped temporarily to
	 * set accurate counter value.
	 * So you should pay attention to the temporary timer stop.
	 *
	 * @return counter value of timer module<br>
	 * 	(8bit timer) 0~255<br>
	 * 	(16bit timer) 0~65535
	 */
	uint16_t (*getCount)(void);

	/**
	 * Set counter value of timer module.
	 *
	 * At several device, countup operation is stoped temporarily to
	 * get accurate counter value.
	 * So you should pay attention to the temporary timer stop.
	 *
	 * @param counter value of timer module<br>
	 * 	(8bit timer) 0~255<br>
	 * 	(16bit timer) 0~65535
	 */
	void (*setCount)(uint16_t);

	/**
	 * Start Counting.
	 *
	 * When timer module constructor called, the counting is disabled.
	 * So this method is needed to start timer operation.
	 * But timer counting is always enabled at timer module which counting
	 * cannot be stoped. (see datasheet)
	 */
	void (*start)(void);

	/**
	 * Stop Counting.
	 *
	 * If you stop timer counting operation temporarily, use this method.
	 * TimerModule#start method can be used for resumption operation.
	 * But timer counting is always enabled at timer module which counting
	 * cannot be stoped. (see datasheet)
	 */
	void (*stop)(void);
} TimerModule;

/**
 * Timer gate control interface.
 */
typedef struct {
	/**
	 * Get current state of gate value.
	 *
	 * @return true if high-level, false if low-level
	 */
	bool (*getState)(void);

	/**
	 * Start single pulse aquisition.
	 *
	 * This method can be used when gate control mode is SINGLE_PULSE.
	 * If interrupt is enabled at
	 * TimerGateControlInterruptService#enableInterrupt, a interrupt
	 * occur at the end of aquisition.
	 * If you don't use interrupt, TimerGateControl#isWaitingSinglePulse
	 * is can be used for aquisition of a single pulse.
	 *
	 * example:
	 * {@code
	 * // timer module setup
	 * const TimerModule* tm = Hardware.Timer1Module;
	 * tm->enable();
	 * tm->selectClockSource(Timer1Module_ClockSource.XXX);
	 * tm->selectPrescaler(Timer1Module_Prescaler.XXX);
	 * tm->setMode(Timer1Module_Mode.COUNTER);
	 * tm->stop();
	 * tm->setCount(0);
	 * // timer gate control setup
	 * const TimerGateControl* tgc = tm->Timer1GateControl;
	 * tgc->selectSource(Timer1GateControl_Source.XXX);
	 * tgc->selectMode(Timer1GateControl_Mode.SINGLE_PULSE);
	 * // do single pulse aquisition and get result value
	 * tm->start();
	 * tgc->startSinglePulseAquisition();
	 * while(tgc->isWaitingSinglePulse());
	 * uint16_t result = tm->getCount();
	 * }
	 */
	void (*startSinglePulseAquisition)(void);

	/**
	 * Represent single pulse aquisition state.
	 *
	 * @return true if waiting single pulse edge<br>
	 * 	false if aquisition is completed or not conducted.
	 */
	bool (*isWaitingSinglePulse)(void);
} TimerGateControl;

#endif /* TIMER_MODULE_H */
