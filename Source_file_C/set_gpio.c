#include"GPIO.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function name: void set_GPIO(char PORT, unsigned int PIN, unsigned int DIRECTION, unsigned int LEVEL)                        //
// Description: Configures the settings of a specified GPIO pin by selecting the port, pin number, direction (input or output), //
//              and the initial output level.                                                                                   //
// PORT:       Selects which GPIO port the pin belongs to.                                                                      //
// PIN:        Determines the specific pin to be configured within the chosen port.                                             //
// DIRECTION:  Represents the direction of the GPIO pin. (0: IN, 1: OUT)                                                        //
// LEVEL:      Represents the output level of the pin if it is configured as an output. (0: LOW, 1: HIGH)                       //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_GPIO(char PORT, unsigned int PIN, unsigned int DIRECTION, unsigned int LEVEL) 
{
    volatile unsigned int *PCC_ref;   // Pointer to set PCC
    volatile unsigned int *PCR_ref;   // Pointer to set PCR
    volatile unsigned int *GPIO_ref;  // Pointer to set GPIO

    // Determine the port and set the corresponding registers
    switch (PORT) 
    {
        case 'A':
        case 'a':
            PCC_ref = &PCC_PORT->PCC_PORTA;
            PCR_ref = (volatile unsigned int *)PORTA_PCR + PIN;
            GPIO_ref = &PORTA_GPIO->PDDR;
            break;
        case 'B':
        case 'b':
            PCC_ref = &PCC_PORT->PCC_PORTB;
            PCR_ref = (volatile unsigned int *)PORTB_PCR + PIN;
            GPIO_ref = &PORTB_GPIO->PDDR;
            break;
        case 'C':
        case 'c':
            PCC_ref = &PCC_PORT->PCC_PORTC;
            PCR_ref = (volatile unsigned int *)PORTC_PCR + PIN;
            GPIO_ref = &PORTC_GPIO->PDDR;
            break;
        case 'D':
        case 'd':
            PCC_ref = &PCC_PORT->PCC_PORTD;
            PCR_ref = (volatile unsigned int *)PORTD_PCR + PIN;
            GPIO_ref = &PORTD_GPIO->PDDR;
            break;
        case 'E':
        case 'e':
            PCC_ref = &PCC_PORT->PCC_PORTE;
            PCR_ref = (volatile unsigned int *)PORTE_PCR + PIN;
            GPIO_ref = &PORTE_GPIO->PDDR;
            break;
        default:
            // Invalid port, do nothing
            return;
    }

    // Generate clock
    *PCC_ref |= (1 << 30);

    // Set mux
    *PCR_ref |= (1 << 8);

    // Disable PE
    *PCR_ref &= ~(1u << 1);

    // Set input or output
    if (DIRECTION == 1) // Output
			{ 
        *GPIO_ref |= (1 << PIN);
        GPIO_ref -= 5; // Move pointer to set output level
        if (LEVEL == 1)
            *GPIO_ref |= (1 << PIN);
        else
            *GPIO_ref &= ~(1 << PIN);
			} 
		else if (DIRECTION == 0) // Input
			{ 
        *GPIO_ref &= ~(1 << PIN);
        GPIO_ref -= 1; // Move pointer to set input level
        if (LEVEL == 1)
            *GPIO_ref |= (1 << PIN);
        else
            *GPIO_ref &= ~(1 << PIN);
			}
}



