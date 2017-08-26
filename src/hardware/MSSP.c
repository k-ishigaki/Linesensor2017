#include <xc.h>
#include "Hardware.h"


const struct I2C_SlewRateControl I2C_SlewRateControl = {
	0, // ENABLE
	1, // DISABLE
};

const struct I2C_InputThreshold I2C_InputThreshold = {
	0, // DEFAULT
	1, // SMBUS
};

const struct I2C_GeneralCallInterrupt I2C_GeneralCallInterrupt = {
	0, // DISABLE
	1, // ENABLE
};

const struct I2C_ConditionInterrupt I2C_ConditionInterrupt = {
	0b00, // DISABLE
	0b01, // START
	0b10, // STOP
	0b11, // START_AND_STOP
};

const struct I2C_SDAHoldTime I2C_SDAHoldTime = {
	0, // ONE_HUNDRED_NS
	1, // THREE_HUNDRED_NS
};

const struct I2C_SlaveBusCollisionDetect I2C_SlaveBusCollisionDetect = {
	0, // DISABLE
	1, // ENABLE
};

#define this_(name) MSSPI2C_##name

static uint8_t this_(sspm_slave);
static uint8_t this_(sspm_master);
static uint8_t this_(sspadd_slave);
static uint16_t this_(slaveAddress);

static void this_(generateStartCondition)() {
	SSP1CON2bits.SEN = 1;
}

static void this_(generateStopCondition)() {
	SSP1CON2bits.PEN = 1;
}

static void this_(generateRestartCondition)() {
	SSP1CON2bits.RSEN = 1;
}

static bool this_(isPending)() {
	bool result;
	if ((SSP1CON1bits.SSPM & 0b1110) == 0b1110) {
		// in slave mode
		result = !(PIR1bits.SSP1IF);
	} else {
		// in master mode
		result = !(PIR1bits.SSP1IF) || SSP1CON2bits.PEN || SSP1CON2bits.RSEN || SSP1CON2bits.SEN;
	}
	if (result == false) {
		PIR1bits.SSP1IF = 0;
	}
	return result;
}

static void this_(startTransmission)(uint8_t data) {
	// store data to buffer and start transmission
	SSP1BUF = data;
}

static bool this_(wasAcknowledged)() {
	return !(SSP1CON2bits.ACKSTAT);
}

static void this_(startReception)(bool nextAck) {
	PIR1bits.SSP1IF = 0;
	// next acknowledge is enabled by ACKDT = 0
	SSP1CON2bits.ACKDT = nextAck == true ? 0 : 1;
	// start reception
	SSP1CON2bits.RCEN = 1;
}

static uint8_t this_(read)() {
	// read data from buffer
	return SSP1BUF;
}

static const struct I2C this_(instance) = {
	this_(generateStartCondition),
	this_(generateStopCondition),
	this_(generateRestartCondition),
	this_(isPending),
	this_(startTransmission),
	this_(wasAcknowledged),
	this_(startReception),
	this_(read),
};

const struct I2C* this_(constructor)(
		char slewRateControll,
		char inputThreshold,
		unsigned int clockPeriod,
		uint16_t slaveAddress,
		char generalCallInterrupt,
		char conditionInterrupt,
		char sdaHoldTime) {
	SSP1STATbits.SMP = slewRateControll;
	SSP1STATbits.CKE = inputThreshold;
	
	this_(slaveAddress) = slaveAddress;
	this_(sspm_slave) = this_(slaveAddress) > 0x7F ? 0b0111 : 0b0110;


	return &this_(instance);
}

