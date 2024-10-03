typedef struct SYSTEM_CLOCK_GENERATOR {
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int a[2];
	volatile unsigned int CSR;
	volatile unsigned int RCCR;
	volatile unsigned int VCCR;
	volatile unsigned int HCCR;
	volatile unsigned int CLKOUTCNFG;
	volatile unsigned int a1[55];
	volatile unsigned int SOSCCSR;
	volatile unsigned int SOSCDIV;
	volatile unsigned int SOSCCFG;
	volatile unsigned int a2[61];
	volatile unsigned int SIRCCSR;
	volatile unsigned int SIRCDIV;
	volatile unsigned int SIRCCFG;
	volatile unsigned int a3[61];
	volatile unsigned int FIRCCSR;
	volatile unsigned int FIRCDIV;
	volatile unsigned int FIRCCFG;
	volatile unsigned int a4[189];
	volatile unsigned int SPLLCSR;
	volatile unsigned int SPLLDIV;
	volatile unsigned int SPLLCFG;
}SCGenerate;


#define SCG    ((volatile SCGenerate *) 0x40064000)

extern void set_SIRC (unsigned int clock_source_value,unsigned int div1, unsigned int div2);
/* 		a = 8   => 	8Mz
		a = 2   =>	2Mz
		div1, div2 000 Output disabled
	1	001 Divide by 1
	2	010 Divide by 2
	3	011 Divide by 4
	4	100 Divide by 8
	5	101 Divide by 16
	6	110 Divide by 32
	7	111 Divide by 64
*/
extern void set_SOSC(unsigned int num_hz,unsigned int div1, unsigned int div2);
/*
		num_hz : range of SOSC source from 0->40
		div1, div2 
	1	001 Divide by 1
	2	010 Divide by 2
	3	011 Divide by 4
	4	100 Divide by 8
	5	101 Divide by 16
	6	110 Divide by 32
	7	111 Divide by 64
*/
extern void set_FIRC(unsigned int div1, unsigned int div2);
/*
		div1, div2 
	1	001 Divide by 1
	2	010 Divide by 2
	3	011 Divide by 4
	4	100 Divide by 8
	5	101 Divide by 16
	6	110 Divide by 32
	7	111 Divide by 64
*/
extern void set_SPLL(unsigned int div1, unsigned int div2, unsigned int mul,unsigned int div);
/*
		div1, div2 
	1	001 Divide by 1
	2	010 Divide by 2
	3	011 Divide by 4
	4	100 Divide by 8
	5	101 Divide by 16
	6	110 Divide by 32
	7	111 Divide by 64
	---------------------------------------
		div 1->8
		if u want div it by 1
		just pass 1
	---------------------------------------
		mul 16->47
		if u want MUL it by 16
		just pass 16
*/
extern void set_CCR(unsigned int source_clock,unsigned int divcore,unsigned int divbus,unsigned int divslow);
/*
	source_clock 
	1: SOSC
	2: SIRC
	3: FIRC
	6: SPLL
	divcore: 	1->16
	divbus:		1->16
	divslow:	1->8
*/

