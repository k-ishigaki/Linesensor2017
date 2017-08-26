#ifndef AD_CONVERTER_H
#define AD_CONVERTER_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Analog to Digital Converter.
 */
struct ADConverter {

	/**
	 * Select input channel of the AD conveter.
	 *
	 * Please ensure the pin is analog inputable before connect
	 * ad conveter input channel to it.
	 * AD conveter often needs acquisition time, so you should make time
	 * before call {@code ADConverter#startConversion} when input
	 * channel is changed.
	 * The channel identifier is defined at Hardware.h
	 * 
	 * @param input channel identifier
	 */
	void (*selectInputChannel)(char);

	/**
	 * Initiate AD conversion cycle.
	 *
	 * The AD conversion is started if previous conversion is ended.
	 * If previous one continues, wait for it is finished. So, please
	 * note that this method may take time.
	 *
	 * Before start conversion, {@code ADConverter#eneble} and
	 * (if needed) {@code ADConverter#selectInputChannel} should
	 * be called.
	 *
	 * If interrupt is enabled by ADConverterInterruptService,
	 * the registered listener is called at finish of the convertion.
	 */
	void (*startConversion)(void);

	/**
	 * Return whether AD conversion continues or not.
	 *
	 * If you don't use interrupt of AD converter module, it is recommended
	 * using this method after ADConverter#startConversion.
	 *
	 * example:
	 * {@code
	 * adc->startConversion();
	 * while(adc->isConverting()); // wait for finishing conversion
	 * int result = adc->getResult();
	 * }
	 *
	 * @return true if AD conversion continues, false if not
	 */
	bool (*isConverting)(void);

	/**
	 * Get result value of previous AD conversion.
	 *
	 * The resolution of AD conversion can be obtained from
	 * ADConverter#getResolution.
	 *
	 * @return result value of previous AD conversion
	 */
	uint16_t (*getResult)(void);
};

#endif /* AD_CONVERTER_H */
