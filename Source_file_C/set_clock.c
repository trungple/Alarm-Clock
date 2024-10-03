#include "SCG.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: set_SIRC(unsigned int clock_source_value, unsigned int div1, unsigned int div2)                                    //
// Description: Configures the system clock from SIRC by selecting a clock source and setting division factors.                 //
//              This function allows the user to choose the clock source frequency and configure two divider values.            //
// clock_source_value: Specifies the frequency of the clock source in MHz.                                                      //
// div1:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks).                             //
// div2:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks). 							//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_SIRC (unsigned int clock_source_value, unsigned int div1, unsigned int div2)
{
	unsigned int temp;
	temp = SCG->SIRCCSR;		// clear bit 23 for writing
	temp &= ~(1u<<23);
	SCG->SIRCCSR = temp ;
	
	temp = SCG->SIRCCSR;		// disable
	temp &= ~(1u<<0);				
	SCG->SIRCCSR = temp ;
	
	if (clock_source_value == 2)								// config 
	{
		temp=SCG->SIRCCFG;
		temp &=~(1u<<0);
		SCG->SIRCCFG=temp;
	}
	
	else if(clock_source_value == 8)						//config
	{
		temp=SCG->SIRCCFG;
		temp |=(1<<0);
		SCG->SIRCCFG=temp;
	}
	
	temp=SCG->SIRCDIV;			//config div1
	temp |= (div1<<0);
	SCG->SIRCDIV=temp;
	
	temp=SCG->SIRCDIV;			//config div2
	temp |= (div2<<8);
	SCG->SIRCDIV=temp;
	
	temp = SCG->SIRCCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->SIRCCSR = temp ;
	
	temp = SCG->SIRCCSR;		// enable
	temp |= (1<<0);				
	SCG->SIRCCSR = temp ;
	
	while((SCG->SIRCCSR&(1<<24))!=(1<<24));
}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: set_SOSC(unsigned int num_hz,unsigned int div1, unsigned int div2)                                    				//
// Description: Configures the system clock from SOSC by selecting a clock source and setting division factors.                 //
//              This function allows the user to choose the clock source frequency and configure two divider values.            //
// num_hz: 				Specifies the frequency of the clock source in MHz.                                                     //
// div1:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks).                             //
// div2:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks). 							//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_SOSC(unsigned int num_hz,unsigned int div1, unsigned int div2)
{
	unsigned int temp;
	temp = SCG->SOSCCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->SOSCCSR = temp ;
	
	temp = SCG->SOSCCSR;		// disable
	temp &= ~(1u<<0);				
	SCG->SOSCCSR = temp ;
	
	temp = SCG->SOSCDIV;		
	temp |= (div2<<8);				
	SCG->SOSCDIV = temp ;
	
	temp = SCG->SOSCDIV;		
	temp |= (div1<<0);				
	SCG->SOSCDIV = temp ;
	
	if(num_hz>0 && num_hz<4)
	{
		temp=SCG->SOSCCFG;
		temp |= (1<<2);
		SCG->SOSCCFG=temp;
	}
	else if(num_hz>=4 &&num_hz<8)
	{
		temp=SCG->SOSCCFG;
		temp |= ((1<<2)|(1<<5));
		temp &=~(1u<<4);
		SCG->SOSCCFG=temp;
	}
	else if(num_hz>=8 && num_hz<=40)
	{
		temp=SCG->SOSCCFG;
		temp |= ((1<<2)|(1<<5));
		SCG->SOSCCFG=temp;
	}
	temp = SCG->SOSCCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->SOSCCSR = temp ;
	
	temp = SCG->SOSCCSR;		// enable
	temp |= (1<<0);				
	SCG->SOSCCSR = temp ;
	
	while((SCG->SOSCCSR&(1<<24))!=(1<<24));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: set_FIRC(unsigned int div1, unsigned int div2)                              										//
// Description: Configures the system clock from FIRC by selecting a clock source and setting division factors.                 //
//              This function allows the user to choose the clock source frequency and configure two divider values.            //
// div1:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks).                             //
// div2:                Dividend parameter used for a specific clock aim (e.g., peripheral clocks). 							//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_FIRC(unsigned int div1, unsigned int div2)
{
	unsigned int temp;
	temp = SCG->FIRCCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->FIRCCSR = temp ;
	
	temp = SCG->FIRCCSR;		// disable
	temp &= ~(1u<<0);				
	SCG->FIRCCSR = temp ;
	
	temp=SCG->FIRCDIV;			//DIV 1
	temp |= (div1<<0);
	SCG->FIRCDIV=temp;
	
	temp=SCG->FIRCDIV;			//DIV 2
	temp |= (div2<<8);
	SCG->FIRCDIV=temp;
	
	temp = SCG->FIRCCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->FIRCCSR = temp ;
	
	temp = SCG->FIRCCSR;		// enable
	temp |= (1<<0);				
	SCG->FIRCCSR = temp ;
	
	while((SCG->SIRCCSR&(1<<24))!=(1<<24));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: set_SPLL(unsigned int div1, unsigned int div2, unsigned int mul, unsigned int div)                               	//
//                                                                                                                              //
// Description: Configures the frequency amplifier by selecting a source and setting the necessary parameters for the SPLL.     //
//              This function allows the user to specify division factors and a multiplier for frequency adjustment.            //
//                                                                                                                              //
// div1:               First division parameter used in the frequency configuration.                                            //
// div2:               Second division parameter used in the frequency configuration.                                           //
// mul:               Multiplier of this module, used to amplify the frequency from the source.                                 //
// div:               Division factor of this module, used to reduce the amplified frequency to the desired output.             //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_SPLL(unsigned int div1, unsigned int div2, unsigned int mul,unsigned int div)
{
	unsigned int temp;
	temp = SCG->SPLLCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->SPLLCSR = temp ;
	
	temp = SCG->SPLLCSR;		// disable
	temp &= ~(1u<<0);				
	SCG->SPLLCSR = temp ;
	
	temp=SCG->SPLLDIV;			//DIV 1
	temp |= (div1<<0);
	SCG->SPLLDIV=temp;
	
	temp=SCG->SPLLDIV;			//DIV 2
	temp |= (div2<<8);
	SCG->SPLLDIV=temp;
	
	temp=SCG->SPLLCFG;			// config mul
	temp |=((mul-16)<<16);
	SCG->SPLLCFG=temp;
	
	temp=SCG->SPLLCFG;			// config div
	temp |=((div-1)<<8);
	SCG->SPLLCFG=temp;
	
	temp = SCG->SPLLCSR;		// clear bit 23
	temp &= ~(1u<<23);
	SCG->SPLLCSR = temp ;
	
	temp = SCG->SPLLCSR;		// enable
	temp |= (1<<0);				
	SCG->SPLLCSR = temp ;
	
	while((SCG->SPLLCSR&(1<<24))!=(1<<24));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: set_CCR(unsigned int source_clock, unsigned int divcore, unsigned int divbus, unsigned int divslow)              	//
//                                                                                                                              //
// Description: Controls the system clock source and the system clock dividers for the core, platform, external,                //
//              and bus clock domains when in Run mode only.                                                                    //
//                                                                                                                              //
// source_clock:     Selects the clock source for the system.                                                                   //
// divcore:          Coefficient used to divide the core frequency.                                                             //
// divbus:           Coefficient used to divide the bus frequency.                                                              //
// divslow:          Coefficient used to divide the flash frequency.                                                            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_CCR(unsigned int source_clock,unsigned int divcore,unsigned int divbus,unsigned int divslow)
{
	unsigned int temp;
	temp=SCG->RCCR;
	temp &=~(15u<<24); 			//clear 4bit from bit 24
	temp |=(source_clock<<24);
	temp|=(((divcore-1)<<16)|((divbus-1)<<4)|((divslow-1)<<0));
	SCG->RCCR=temp;
	
}
