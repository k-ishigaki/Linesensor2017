#ifndef NATIVE_INTERRUPTS_H
#define NATIVE_INTERRUPTS_H

/**
 * A interface of interrupt listener.
 *
 * When using native interrupt of peripherals, only you have to do is
 * create this instance and register it to interrupt service that you
 * want to listen.
 * example:
 * {@code
 * // creating instance of interrupt listener
 * static void onInterrupt() {
 * 	// do something when interrupt
 * }
 * static InterruptListener listener = {
 * 	onInterrupt,
 * };
 * ...
 * 	const InterruptService* intService;
 * ...
 * 	intService = Hardware.SomeInterruptService(...);
 * ...
 * 	// register listener to service
 * 	intService->registerListener(&listener);
 * 	intService->enableInterrupt();
 * 	// when interrupt occured, onInterrupt method is called
 * }
 */
struct InterruptListener {

	/**
	 * Called on a interrupt occured if registerd by the service.
	 *
	 * This method must be terminated shortly (about within 10 us)
	 * because it is called at interrupt vector and
	 * other any interrupts cannnot occur.
	 */
	void (*onInterrupt)(void);
};

/*+
 * A interface of interrupt vector and interrupt service.
 *
 * Other modules can use the interrupt through
 * {@code
 * intService->registerListener(listener);
 * intService->enableInterrupt();
 * }
 * where the argument are explained below.
 */
struct InterruptService {

	/**
	 * Add a listener handles interrupt.
	 *
	 * If you call this method twice, only one listener is registered.
	 * (First registerd listener is overwriten by second one.)
	 * This method may takes time to register listener to interrupt
	 * vector, so it is recommended calling it at initilization.
	 *
	 * @param interrupt listener
	 */
	void (*registerListener)(const struct InterruptListener*);

	/**
	 * Enable the interrupt.
	 *
	 * This method must be called after calling
	 * InterruptService#registerListener.
	 */
	void (*enableInterrupt)(void);

	/**
	 * Disable the interrupt.
	 *
	 * You should call this method when stop the interrupt
	 * because it is unable to remove registerd listener.
	 */
	void (*disableInterrupt)(void);
};

#endif /* NATIVE_INTERRUPTS_H */
