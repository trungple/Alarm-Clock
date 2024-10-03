typedef struct SERIAL_PERIPHERAL_INTERFACE
{
	volatile int VERID;             // Version ID Register
  volatile int PARAM;             // Parameter Register
	volatile int a[2];
  volatile int CR;                // Control Register
  volatile int SR;                // Status Register
  volatile int IER;               // Interrupt Enable Register
  volatile int DER;               // DMA Enable Register
  volatile int CFGR0;             // Configuration Register 0
  volatile int CFGR1;             // Configuration Register 1
	volatile int b[2];
  volatile int DMR0;              // Data Match Register 0
  volatile int DMR1;              // Data Match Register 1
	volatile int c[2];
  volatile int CCR;               // Clock Configuration Register
	volatile int d[5];
  volatile int FCR;               // FIFO Control Register
  volatile int FSR;               // FIFO Status Register
  volatile int TCR;               // Transmit Command Register
  volatile int TDR;               // Transmit Data Register
	volatile int e[2];
  volatile int RSR;               // Receive Status Register
  volatile int RDR;               // Receive Data Register
}SPI;

#define LPSPI0_BASE_ADDRESS 0x4002C000
#define LPSPI1_BASE_ADDRESS 0x4002D000
#define LPSPI2_BASE_ADDRESS 0x4002E000

#define LPSPI0 ((SPI *)LPSPI0_BASE_ADDRESS)
#define LPSPI1 ((SPI *)LPSPI1_BASE_ADDRESS)
#define LPSPI2 ((SPI *)LPSPI2_BASE_ADDRESS)