typedef struct LPIT_memory_map 
{
		volatile int VERID;    // Version ID Register
    volatile int PARAM;    // Parameter Register
    volatile int MCR;      // Module Control Register
    volatile int MSR;      // Module Status Register
    volatile int MIER;     // Module Interrupt Enable Register
    volatile int SETTEN;   // Set Timer Enable Register
    volatile int CLRTEN;   // Clear Timer Enable Register
    volatile int TVAL0;    // Timer Value Register for Channel 0
    volatile int CVAL0;    // Current Timer Value Register for Channel 0
    volatile int TCTRL0;   // Timer Control Register for Channel 0
    volatile int TVAL1;    // Timer Value Register for Channel 1
    volatile int CVAL1;    // Current Timer Value Register for Channel 1
    volatile int TCTRL1;   // Timer Control Register for Channel 1
    volatile int TVAL2;    // Timer Value Register for Channel 2
    volatile int CVAL2;    // Current Timer Value Register for Channel 2
    volatile int TCTRL2;   // Timer Control Register for Channel 2
    volatile int TVAL3;    // Timer Value Register for Channel 3
    volatile int CVAL3;    // Current Timer Value Register for Channel 3
    volatile int TCTRL3;   // Timer Control Register for Channel 3
}LPIT_REGISTER;

#define LPIT ((LPIT_REGISTER*) 0X40037000)