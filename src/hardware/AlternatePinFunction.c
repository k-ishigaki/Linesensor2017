#include <xc.h>
#include "Hardware.h"

#define AlternatePinFunction_(name) AlternatePinFunction_##name

enum AlternatePinFunction_(RXAndDT_Constant) {
	RX_DT_RC5 = 0,
	RX_DT_RA1 = 1,
};
const struct AlternatePinFunction_(RXAndDT) AlternatePinFunction_(RXAndDT) = {
	RX_DT_RC5,
	RX_DT_RA1,
};

enum AlternatePinFunction_(SDO_Constant) {
	SDO_RC2 = 0,
	SDO_RA4 = 1,
};
const struct AlternatePinFunction_(SDO) AlternatePinFunction_(SDO) = {
	SDO_RC2,
	SDO_RA4,
};

enum AlternatePinFunction_(SS_Constant) {
	SS_RC3 = 0,
	SS_RA3 = 1,
};
const struct AlternatePinFunction_(SS) AlternatePinFunction_(SS) = {
	SS_RC3,
	SS_RA3,
};

enum AlternatePinFunction_(T1G_Constant) {
	T1G_RA4 = 0,
	T1G_RA3 = 1,
};
const struct AlternatePinFunction_(T1G) AlternatePinFunction_(T1G) = {
	T1G_RA4,
	T1G_RA3,
};

enum AlternatePinFunction_(TXAndCK_Constant) {
	TX_CK_RC4 = 0,
	TX_CK_RA0 = 1,
};
const struct AlternatePinFunction_(TXAndCK) AlternatePinFunction_(TXAndCK) = {
	TX_CK_RC4,
	TX_CK_RA0,
};

enum AlternatePinFunction_(P1D_Constant) {
	P1D_RC2 = 0,
	P1D_RC0 = 1,
};
const struct AlternatePinFunction_(P1D) AlternatePinFunction_(P1D) = {
	P1D_RC2,
	P1D_RC0,
};

enum AlternatePinFunction_(P1C_Constant) {
	P1C_RC3 = 0,
	P1C_RC1 = 1,
};
const struct AlternatePinFunction_(P1C) AlternatePinFunction_(P1C) = {
	P1C_RC3,
	P1C_RC1,
};

enum AlternatePinFunction_(P2B_Constant) {
	P2B_RC2 = 0,
	P2B_RA4 = 1,
};
const struct AlternatePinFunction_(P2B) AlternatePinFunction_(P2B) = {
	P2B_RC2,
	P2B_RA4,
};

enum AlternatePinFunction_(CCP2_Constant) {
	CCP2_RC3 = 0,
	CCP2_RA5 = 1,
};
const struct AlternatePinFunction_(CCP2) AlternatePinFunction_(CCP2) = {
	CCP2_RC3,
	CCP2_RA5,
};

void AlternatePinFunction_(configure)(
		char RXAndDT,
		char SDO,
		char SS,
		char T1G,
		char TXAndCK,
		char P1D,
		char P1C,
		char P2B,
		char CCP2) {
	APFCON0bits.RXDTSEL = RXAndDT;
	APFCON0bits.SDOSEL = SDO;
	APFCON0bits.SSSEL = SS;
	APFCON0bits.T1GSEL = T1G;
	APFCON0bits.TXCKSEL = TXAndCK;
	APFCON1bits.P1DSEL = P1D;
	APFCON1bits.P1CSEL = P1C;
	APFCON1bits.P2BSEL = P2B;
	APFCON1bits.CCP2SEL = CCP2;
}


