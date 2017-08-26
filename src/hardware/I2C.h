#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdbool.h>

struct I2C {
	/**
	 * Generate start consdition as a master.
	 */
	void (*generateStartCondition)(void);

	/**
	 * Generate stop condition as a master.
	 */
	void (*generateStopCondition)(void);

	/**
	 * Generate restart condition as a master.
	 */
	void (*generateRestartCondition)(void);

	/**
	 * Check if I2C operation is pending.
	 *
	 * @return true if module is pending<br>
	 * 	false if not
	 */
	bool (*isPending)(void);

	/**
	 * Write to buffer and start transmission.
	 *
	 * In master mode, this method is 
	 */
	void (*startTransmission)(uint8_t);

	/**
	 * Check if acknowledge existed at last transmission.
	 *
	 * @return true if acknowledge was received<br>
	 * 	false if not
	 */
	bool (*wasAcknowledged)(void);

	/**
	 * Start reception.
	 *
	 * A acknowledge reservation must be determined so that
	 * the slave device can detect reception ending.
	 * The received value can be read I2CMaster#read method
	 * after reception sequence finished.
	 * {@code
	 * const struct I2CMaster* i2c = Hardware.I2CMaster(...);
	 * i2c->generateStartCondition();
	 * while (i2c->isPending());
	 * // send slave address and read bit
	 * i2c->startTransmission(ADDRESS << 1 | 0b00000001);
	 * while (i2c->isPending());
	 * // check slave acknowledge
	 * if (!(i2c->wasAcknowledged())) goto ERROR;
	 * // first byte reception
	 * i2c->startReception(true);
	 * while (i2c->isPending());
	 * uint8_t result1 = i2c->read();
	 * // second byte reception
	 * i2c->startReception(false);
	 * while (i2c->isPending());
	 * uint8_t result2 = i2c->read();
	 * i2c->generateStopCondition();
	 * while (i2c->isPending());
	 * }
	 *
	 * @param acknowledge reservation<br>
	 * 	acknowledge will be transmitted if true<br>
	 * 	not acknowledge will be transmitted if false
	 */
	void (*startReception)(bool);

	/**
	 * Read from buffer.
	 *
	 * This method does not need waiting by I2CMaster#isPending method.
	 *
	 * @param buffer value
	 */
	uint8_t (*read)(void);
};

#endif /* I2C_H */
