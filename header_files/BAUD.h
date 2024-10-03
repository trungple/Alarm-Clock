typedef struct universal_ART
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int GLOBAL;
	volatile unsigned int PINCFG;
	volatile unsigned int BAUD;
	volatile unsigned int STAT;
	volatile unsigned int CTRL;
	volatile unsigned int DATA;
	volatile unsigned int MATCH;
	volatile unsigned int MODIR;
	volatile unsigned int FIFO;
	volatile unsigned int WARTER;
}UART;

#define LPUART0_BASE_ADDRESS 0x4006A000
#define LPUART1_BASE_ADDRESS 0x4006B000
#define LPUART2_BASE_ADDRESS 0x4006C000

#define LPUART0 ((UART *)LPUART0_BASE_ADDRESS)
#define LPUART1 ((UART *)LPUART1_BASE_ADDRESS)
#define LPUART2 ((UART *)LPUART2_BASE_ADDRESS)
