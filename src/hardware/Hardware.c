#include "Hardware.h"

// declared at InterruptVector.c
extern const struct InterruptService* ADConverterModuleInterruptService_constructor();
extern const struct InterruptService* Timer0ModuleInterruptService_constructor();
extern const struct InterruptService* Timer1ModuleInterruptService_constructor();
extern const struct InterruptService* Timer1GateControlInterruptService_constructor();
extern const struct InterruptService* Timer2ModuleInterruptService_constructor();
extern const struct InterruptService* Timer4ModuleInterruptService_constructor();
extern const struct InterruptService* Timer6ModuleInterruptService_constructor();
extern const struct InterruptService* CCP1ModuleInterruptService_constructor();
extern const struct InterruptService* CCP2ModuleInterruptService_constructor();
extern const struct InterruptService* CCP3ModuleInterruptService_constructor();
extern const struct InterruptService* CCP4ModuleInterruptService_constructor();
extern const struct InterruptService* CCP5ModuleInterruptService_constructor();
// declared at OscillatorModule.c
extern void OscillatorModule_configure(char, char, char);
// declared at AlternatePinFunction.c
extern void AlternatePinFunction_configure(char, char, char, char, char, char, char, char, char);
// declared at IOPort.c
extern const struct IOPort* PortA_constructor();
extern const struct IOPort* PortC_constructor();
// declared at ADConverterModule.c
extern const struct ADConverter* ADConverterModule_constructor(char, char, char);
// declared at TimerModule.c
extern const TimerModule* Timer0Module_constructor(char, char);
extern const TimerModule* Timer1Module_constructor(char, char);
extern const TimerGateControl* Timer1GateControl_constructor(char, char);
extern const TimerModule* Timer2Module_constructor(char, char, uint8_t);
extern const TimerModule* Timer4Module_constructor(char, char, uint8_t);
extern const TimerModule* Timer6Module_constructor(char, char, uint8_t);
// declared at CCPModule.c
extern const struct Capture* CaptureModule1_constructor(char);
extern const struct Capture* CaptureModule2_constructor(char);
extern const struct Capture* CaptureModule3_constructor(char);
extern const struct Capture* CaptureModule4_constructor(char);
extern const struct Compare* CompareModule1_constructor(char);
extern const struct Compare* CompareModule2_constructor(char);
extern const struct Compare* CompareModule3_constructor(char);
extern const struct Compare* CompareModule4_constructor(char);
extern const struct PWM* PWMModule1_constructor(char, char, char);
extern const struct PWM* PWMModule2_constructor(char, char, char);
extern const struct PWM* PWMModule3_constructor(char, char);
extern const struct PWM* PWMModule4_constructor(char, char);
// declared at FixedVoltageReference.c
extern void FixedVoltageReference_configure(char, char);
// declared at EUSART.c
extern const struct USART* EUSART_constructor(char, char, char, char, unsigned long);

const struct Hardware Hardware = {
	ADConverterModuleInterruptService_constructor,
	Timer0ModuleInterruptService_constructor,
	Timer1ModuleInterruptService_constructor,
	Timer1GateControlInterruptService_constructor,
	Timer2ModuleInterruptService_constructor,
	Timer4ModuleInterruptService_constructor,
	Timer6ModuleInterruptService_constructor,
	CCP1ModuleInterruptService_constructor,
	CCP2ModuleInterruptService_constructor,
	CCP3ModuleInterruptService_constructor,
	CCP4ModuleInterruptService_constructor,
	AlternatePinFunction_configure,
	OscillatorModule_configure,
	PortA_constructor,
	PortC_constructor,
	ADConverterModule_constructor,
	Timer0Module_constructor,
	Timer1Module_constructor,
	Timer1GateControl_constructor,
	Timer2Module_constructor,
	Timer4Module_constructor,
	Timer6Module_constructor,
	CaptureModule1_constructor,
	CaptureModule2_constructor,
	CaptureModule3_constructor,
	CaptureModule4_constructor,
	CompareModule1_constructor,
	CompareModule2_constructor,
	CompareModule3_constructor,
	CompareModule4_constructor,
	PWMModule1_constructor,
	PWMModule2_constructor,
	PWMModule3_constructor,
	PWMModule4_constructor,
	FixedVoltageReference_configure,
	EUSART_constructor,
};
