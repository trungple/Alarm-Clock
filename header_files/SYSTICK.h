typedef struct systick {
		volatile unsigned int SYST_CSR; 		//control and status register
		volatile unsigned int SYST_RVR;			//reload value register
		volatile unsigned int SYST_CVR;			//current value register
		volatile unsigned int SYST_CALIB;		//cabliration  value register
}SYSTICK;

#define SYST   ((volatile SYSTICK *) 0xE000E010)
	
extern void set_SYSTICK_interrupt(unsigned int loaded_value);

