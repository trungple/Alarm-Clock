#include "SYSTICK.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function: void set_SYSTICK_interrupt(unsigned int loaded_value)                                                              //
// Description: Configures the System Tick (SysTick) interrupt by setting the reload value for the timer.                       //
// loaded_value: Specifies																										//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_SYSTICK_interrupt(unsigned int loaded_value)
{
	SYST->SYST_CSR  &=~(1u<<0);				//disable timmer
	SYST->SYST_CSR  &=~(0xFFFFFFu);		//reset current value
	SYST->SYST_RVR	=loaded_value;		// 
	SYST->SYST_CSR |=7;								// 111	
}	

