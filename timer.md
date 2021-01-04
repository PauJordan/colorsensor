The power reduction Timer/Counter1 bit must be written to zero to enable the T/C1 module.
16Bit Registers: interrupts MUST be disabled when accessing. Atomicity.
TCNTn Timer/Counter Register (Here number is counted) n = 1,3,4,5
OCRnX X = A,B,C  Output Compare Registers
ICRn  Input Capture Register

8 Bit registers:
TCCRnA Timer/Counter Control Register n 
TCCRnB
TCCRnC

Modes of operation:
Defined by
WGMn3:0 Waveform Generation mode bits (affects counting seq)
COMnX1:0 Compare Output Mode bits (only affects output)


Pins registers:
Tn External clock source
ICPn Input Capture Pin n
OCnX Output Compare Pin n

Interrupts related registers: (Int. Req)
OCFnX Output Compare Match Flag 
TOVn

Shared registers:
TIFRn Timer Interrupt Flag Register
TIMSKn Timer Interrupt Mask Register

Values:
TOP  maximum Timer/Counter value. Can be assigned fixed values or values stored in registers.
BOTTOM 0x0000.
MAX 0xFFFF. 

Clock sources:
Bits CSn2:0 Clock Select bits located in TCCRnB.
CSn2:0 = 
	0 clock halted.
	1 system clock.
	2 clk/8
	3 clk/64
	4 clk/256
	5 clk/1024
	6 external clk negative edge
	7 external clk positive edge


Readung TCNTn C example:
unsigned int TIM16_ReadTCNTn( void ) {
	unsigned char sreg;
	unsigned int i;
	/* Save global interrupt flag */ sreg = SREG;
	/* Disable interrupts */ __disable_interrupt();
	/* Read TCNTn into i */
	i = TCNTn;
	/* Restore global interrupt flag */ SREG = sreg;
	return i;
}



