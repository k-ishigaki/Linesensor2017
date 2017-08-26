#include <xc.h>
#include "Hardware.h"

// ----------------------------------------------------------------------------
// FixedVoltageReference_Constants
// ----------------------------------------------------------------------------
enum FixedVoltageReference_Buffer1Reference_Constants {
	B1_OFF       = 0b00,
	B1_OUTPUT_1x = 0b01,
	B1_OUTPUT_2x = 0b10,
	B1_OUTPUT_4x = 0b11,
};
const struct FixedVoltageReference_Buffer1Reference FixedVoltageReference_Buffer1Reference = {
	B1_OFF,
	B1_OUTPUT_1x,
	B1_OUTPUT_2x,
	B1_OUTPUT_4x,
};

enum FixedVoltageReference_Buffer2Reference_Constants {
	B2_OFF       = 0b00,
	B2_OUTPUT_1x = 0b01,
	B2_OUTPUT_2x = 0b10,
	B2_OUTPUT_4x = 0b11,
};
const struct FixedVoltageReference_Buffer2Reference FixedVoltageReference_Buffer2Reference = {
	B2_OFF,
	B2_OUTPUT_1x,
	B2_OUTPUT_2x,
	B2_OUTPUT_4x,
};

// ----------------------------------------------------------------------------
// FixedVoltageReference
// ----------------------------------------------------------------------------
#define FixedVoltageReference_(name) FixedVoltageReference_##name

void FixedVoltageReference_(configure)(
		char buffer1Output,
		char buffer2Output) {
	FVRCONbits.ADFVR = buffer1Output;
	FVRCONbits.CDAFVR = buffer2Output;
	while(!FVRCONbits.FVRRDY);
}
