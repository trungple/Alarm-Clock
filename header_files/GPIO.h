//////////////////////////////////////////////////////////////////////////////////////////////
/*														SET GENERAL-PURPOSE INPUT/OUTPUT															*/
//////////////////////////////////////////////////////////////////////////////////////////////

// Adress of GPIO of each port 
#define GPIOA_BASE 0X400FF000
#define GPIOB_BASE 0X400FF040
#define GPIOC_BASE 0X400FF080
#define GPIOD_BASE 0X400FF0C0
#define GPIOE_BASE 0X400FF100

//Struct to choose function of each GPIO
typedef struct GPIO{
	volatile unsigned int PDOR;	//Port data output register					RW
	volatile unsigned int PSOR;	//Port set output register					WORZ
	volatile unsigned int PCOR;	//Port clear output register				WORZ
	volatile unsigned int PTOR;	//Port toggle output register				WORZ
	volatile unsigned int PDIR;	//Port data input register					RO
	volatile unsigned int PDDR;	//Port data direction register 			RW
	volatile unsigned int PIDR;	//Port input disable register				RW
}Type;

#define PORTA_GPIO	((Type*) GPIOA_BASE)
#define PORTB_GPIO	((Type*) GPIOB_BASE)
#define PORTC_GPIO	((Type*) GPIOC_BASE)
#define PORTD_GPIO	((Type*) GPIOD_BASE)
#define PORTE_GPIO	((Type*) GPIOE_BASE)

//////////////////////////////////////////////////////////////////////////////////////////////
/*														SET CLOCK FOR PORT																						*/
//////////////////////////////////////////////////////////////////////////////////////////////
// Peripheral clock controller
#define PCC_BASE		0x40065000
typedef struct Peripheral_clock_controller {
				volatile char a[128]; 
				volatile unsigned int     PCC_FTFC       ;
        volatile unsigned int     PCC_DMAMUX     ;  
        volatile unsigned int     fill[2]   ; 
        volatile unsigned int     PCC_FlexCAN0   ;  
        volatile unsigned int     PCC_FlexCAN1   ;  
        volatile unsigned int			PCC_FTM3	;
        volatile unsigned int     PCC_ADC1       ;  
				volatile unsigned int			fill_1[3]			;
        volatile unsigned int     PCC_FlexCAN2   ; 
        volatile unsigned int     PCC_LPSPI0     ;  
        volatile unsigned int     PCC_LPSPI1     ;  
        volatile unsigned int     PCC_LPSPI2     ;  
        volatile unsigned int     reverse_2[2]   ;     
        volatile unsigned int     PCC_PDB1       ; 
        volatile unsigned int     PCC_CRC        ; 
        volatile unsigned int     reverse_3[3]		;     
        volatile unsigned int     PCC_PDB0       ; 
        volatile unsigned int     PCC_LPIT       ;  
        volatile unsigned int     PCC_FTM0       ; 
        volatile unsigned int     PCC_FTM1       ; 
        volatile unsigned int     PCC_FTM2       ; 
        volatile unsigned int     PCC_ADC0       ;  
        volatile unsigned int     reverse_4[1]   ;     
        volatile unsigned int     PCC_RTC        ; 
        volatile unsigned int     reverse_5[2]   ;     
        volatile unsigned int     PCC_LPTMR0     ; 
        volatile unsigned int     reverse_6[8]  ;     
				volatile unsigned int     PCC_PORTA      ; 
        volatile unsigned int     PCC_PORTB      ;  
        volatile unsigned int     PCC_PORTC      ;  
        volatile unsigned int     PCC_PORTD      ;  
        volatile unsigned int     PCC_PORTE      ; 
        volatile unsigned int     reverse_7[6]  ;     
        volatile unsigned int     PCC_SAI0       ; 
        volatile unsigned int     PCC_SAI1       ; 
        volatile unsigned int     reverse_8[4]  ;     
        volatile unsigned int     PCC_FlexIO     ; 
        volatile unsigned int     reverse_9[6]  ;     
        volatile unsigned int     PCC_EWM        ; 
        volatile unsigned int     reverse_10[4] ;     
        volatile unsigned int     PCC_LPI2C0     ; 
        volatile unsigned int     PCC_LPI2C1     ; 
        volatile unsigned int     reverse_11[2]  ;     
        volatile unsigned int     PCC_LPUART0    ; 
        volatile unsigned int     PCC_LPUART1    ; 
        volatile unsigned int     PCC_LPUART2    ; 
        volatile unsigned int     reverse_12[1]  ;     
        volatile unsigned int     PCC_FTM4       ; 
        volatile unsigned int     PCC_FTM5       ; 
        volatile unsigned int     PCC_FTM6       ; 
        volatile unsigned int     PCC_FTM7       ; 
        volatile unsigned int     reverse_13[1]  ;     
        volatile unsigned int     PCC_CMP0       ; 
        volatile unsigned int     reverse_14[2]  ;     
        volatile unsigned int     PCC_QSPI       ; 
        volatile unsigned int     reverse_15[2]  ;
}GCC;
#define	PCC_PORT ((GCC*) PCC_BASE)


//////////////////////////////////////////////////////////////////////////////////////////////
/*														SET PIN CONTROL REGISTER																			*/
//////////////////////////////////////////////////////////////////////////////////////////////

// Peripheral Memory Map
#define PORTA_PMM			0X40049000	
#define PORTB_PMM			0X4004A000
#define PORTC_PMM			0X4004B000
#define PORTD_PMM			0X4004C000
#define PORTE_PMM			0X4004D000
typedef struct Pin_control_register{
	volatile int	pin_0;
	volatile int	pin_1;			// 18 pin in 1 port
	volatile int	pin_2;
	volatile int	pin_3;
	volatile int	pin_4;
	volatile int	pin_5;
	volatile int	pin_6;
	volatile int	pin_7;
	volatile int	pin_8;
	volatile int	pin_9;
	volatile int	pin_10;
	volatile int	pin_11;
	volatile int	pin_12;
	volatile int	pin_13;
	volatile int	pin_14;
	volatile int	pin_15;
	volatile int	pin_16;
	volatile int	pin_17;
	volatile int	pin_18;
}PCR;

#define	PORTA_PCR ((PCR*) PORTA_PMM)
#define	PORTB_PCR ((PCR*) PORTB_PMM)
#define	PORTC_PCR ((PCR*) PORTC_PMM)
#define	PORTD_PCR ((PCR*) PORTD_PMM)
#define	PORTE_PCR ((PCR*) PORTE_PMM)

extern void set_GPIO(char PORT, unsigned int PIN, unsigned int DIRECTION, unsigned int LEVEL);
