#include "SYSTICK.h"
#include "SCG.h"
#include "GPIO.h"
#include "BAUD.h"
#include "NVIC.h"
#include "SPI.h"
#include <stdint.h>

static void transferdata(uint8_t address, uint8_t data);										// transfer data for led
static void light(void);																		// init led
static void set_time(char *a);																	// display time 
static void set_day(char *b);																	// display day
static void wrong_input(void);																	// print out when wrong input
void get(char *a, char *b, char *c);															// compare and get value
void clear(char*a);																				// clear array
void set_alarm(char*c);																			// display alarm
void time_to_day(void);																			// 5s time to 3s day mode
void handle_SRS6(void);																			// set flag for SSR6
void handle_SRS7(void);																			// set flag for SSR7
void update_time(char *actual_time);															// got new time per sec
void update_day(char *actual_day);																// got new day per pass through 24h
void alarm_occour(char *a, char *b);															// check whether alarm occour or not
void execute_alarm(void);																		// blink led when alarm occour
void execute_based_mode(void);																	// do statement base on actual mode flag
char isValidTime(char *a);																		// valid time 
char isLeapYear(int year);																		// decide whether it is leapyear or not
char isValidDate(char *a);																		// valid date
int getDaysInMonth(int month, int year);													 	// get number of day for each month
void format(void);
void set_up(void);

void LPUART1_RxTx_IRQHandler(void);
void SysTick_Handler (void);
void PORTC_IRQHandler(void);

static char time[6]={1,8,0,0,0,0};																// time array
static char alarm[6]={0,0,0,0,0,0};																// alarm array	
static char day[8]={0,1,0,1,1,9,9,1};															// day array
static char example[100];																		// buffer to store value when recieve from uart
static volatile int count=0;																	// count to get how many character when finish recieving
static volatile char condition=0;																// recieve new massage or not
static volatile char mode_flag=3;																// mode flag for executed
static volatile char mode_6=0;																	// mode 6 flag
static volatile char mode_7=0;																	// mode 7 flag
static volatile char count_sys=0;																// value of systick 
static volatile char real_time=0;																// realtime to update date and hour
static volatile char day_flag=0;																// indicate pass 1 day
static volatile char check_same_flag=0;															// same array flag
static volatile char time_for_blink=0;															// time for blink led 0.5 s
static volatile char time_within_blink=0;														// time for blink led within 10s
static volatile char status=0;																	// flag to support time to day mode
static volatile char break_flag=0;																// break alarm
static volatile char during_alarm=0;															// decide whether during alarming time or not
static volatile char input=0;																	// if got input
static volatile char time_for_change=0;															// use for show this changed information per 3s 
int main()
{
	set_up();
	while(1)
	{
		alarm_occour(time,alarm);
		if(input==0)   							// if dont input any value
		{
			handle_SRS6();
			handle_SRS7();
		}
		update_time(time);
		update_day(day);
	
		execute_based_mode();
		if(condition==1) 						// if finish recieve
		{
			input=1;
			get(time,alarm,day);
			clear(example);
			condition=0;
			count=0;
		}
	}
}
void execute_based_mode(void)
{
	if(mode_flag==3)
		{
			time_to_day();
		}
		if(mode_flag==0)
		{
			set_time(time);
		}
		else if(mode_flag==1)
		{
			set_alarm(alarm);
		}
		else if(mode_flag==2)
		{
			set_day(day);
		}
}

// when time = alarm
void execute_alarm()
{
	if (check_same_flag==1)
	{
		time_within_blink=0;
		time_for_blink=0;
		while (time_within_blink <60)	//10 S
		{
			if(break_flag==1)
			{
				PORTD_GPIO->PDOR |=(1<<16);
				break;
			}
			else
			{
				during_alarm=1;
				update_time(time);
				update_day(day);
				execute_based_mode();
				if (time_for_blink ==3)				//0.5 S
				{
					PORTD_GPIO->PDOR ^=(1<<16);
					time_for_blink=0;
				}
			}
		}
		break_flag=0;
		count_sys=0;
		during_alarm=0;
		check_same_flag=0;
	}
}
// check whether time equal to alarm or not
void alarm_occour(char *a, char *b)
{
	volatile int check_same_time=0;
	volatile int i=0;
	for (i=0;i<6;i++)
	{
		if(a[i]==b[i])
		{
			check_same_time++;
		}
	}
	if (check_same_time==6)
	{
		check_same_flag =1;
	}
	execute_alarm();
}
// Function to get the number of days in a month for a given year
int getDaysInMonth(int month, int year) 
	{
    // Days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap year
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }

    return daysInMonth[month - 1];
}

void update_day(char *actual_day) 
	{
		if(day_flag==1) // if +1 day
		{
    int days = actual_day[0] * 10 + actual_day[1];
    int month = actual_day[3] * 10 + actual_day[4];
    int year = actual_day[6] * 1000 + actual_day[7] * 100 + actual_day[8] * 10 + actual_day[9];
		
	

    // Increment the day
    days += 1;

    // Get the number of days in the current month
    int daysInCurrentMonth = getDaysInMonth(month, year);

    // Check if the day exceeds the number of days in the current month
    if (days > daysInCurrentMonth) {
        days = 1; // Reset day to 1
        month += 1; // Increment the month

        // Check if the month exceeds 12 (December)
        if (month > 12) {
            month = 1; // Reset month to January
            year += 1; // Increment the year
        }
    }

    // Update the actual_day array with the new values
    actual_day[0] = days / 10;
    actual_day[1] = days % 10;
    actual_day[3] = month / 10;
    actual_day[4] = month % 10;
    actual_day[6] = year / 1000;
    actual_day[7] = (year % 1000) / 100;
    actual_day[8] = (year % 100) / 10;
    actual_day[9] = year % 10;
		day_flag=0;
}
}
void update_time(char * actual_time)
{
	if (real_time==6)
	{
		real_time=0;
		actual_time[5] += 1; // Increment second units place

    if (actual_time[5] == 10) {
        actual_time[5] = 0;
        actual_time[4] += 1; // Increment second tens place

        if (actual_time[4] == 6) {
            actual_time[4] = 0;
            actual_time[3] += 1; // Increment minute units place

            if (actual_time[3] == 10) {
                actual_time[3] = 0;
                actual_time[2] += 1; // Increment minute tens place

                if (actual_time[2] == 6) {
                    actual_time[2] = 0;
                    actual_time[1] += 1; // Increment hour units place

                    if (actual_time[1] == 10) {
                        actual_time[1] = 0;
                        actual_time[0] += 1; // Increment hour tens place

                        if (actual_time[0] == 2 && actual_time[1] == 4) {
                            // Reset to 00:00:00 after 23:59:59
                            actual_time[1] = 0;
                            actual_time[0] = 0;
														day_flag=1;
                        }
                    }
                }
            }
        }
    }
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	if((LPUART1->STAT &(1<<20))!=0)
		{
			LPUART1->STAT|=(1<<20);							// CLEAR FLAG
			condition=1;
		}
	else if((LPUART1->STAT &(1<<21))!=0)
		{
			LPUART1->STAT|=(1<<21);							// CLEAR FLAG
			example[count]=(char)LPUART1->DATA;
			count ++;
		}
}

// handle 5 mode of interrupt 2 
void handle_SRS7(void)
{
	if(mode_7==1)												// mode 1
	{
		transferdata(0xFC,1);
		transferdata(0xFA,0XFF);
	}
	else if(mode_7==2)									// mode 2
	{
		transferdata(0xFA,0XF9);
	}
	else if(mode_7==3)									// mode 3
	{
		transferdata(0xFA,0XF6);
	}
	else if(mode_7==4)									// mode 4
	{
		transferdata(0xFA,0XF1);
	}
	else if(mode_7==5)									// mode 5
	{
		transferdata(0xFC,0);
	}
	else 
	{
		mode_7=1;													// return to mode 1
	}
}

// handle 4 mode of interrupt 1
void handle_SRS6(void)
{
	if(mode_6==0)											// set flag for mode 1 
	{
		mode_flag=3;
	}
	else if (mode_6==1)								// set flag for mode 2
	{
		mode_flag=2;
	}
	else if (mode_6==2)								// set flag for mode 3
	{
		mode_flag=0;
	}
	else if (mode_6==3)								// set flag for mode 4
	{
		mode_flag=1;
	}
	else if(mode_6==4)								// return to mode 1
	{
		mode_6=0;
		count_sys=0;
	}
}
void time_to_day(void)
{
    if (status == 0) 
			{
        if (count_sys == 6 * 5) 				// 5s at time mode
					{
            mode_flag = 2;  // Switch to day mode
            count_sys = 0;
            status = 1;
					} 
				else 
					{
            mode_flag = 0;  // Default to time mode
					}
			} 
		else if (status == 1) 
			{
				if (count_sys == 6 * 3) 				// 3s at day mode
				{
					mode_flag = 0;  // Switch to time mode
					count_sys = 0;
					status = 0;
				} 
				else 
				{
					mode_flag = 2;  // Default to day mode
				}
				}
}

// check function
void get(char *a, char *b, char *c)
{
	if(count ==8&&example[2]==':'&&example[5]==':'&&isValidTime(example)==1)
	{
		a[0]=example[0]-0x30;						// assign value to array
		a[1]=example[1]-0x30;
		a[2]=example[3]-0x30;
		a[3]=example[4]-0x30;
		a[4]=example[6]-0x30;
		a[5]=example[7]-0x30;
		mode_flag=0;
	}
	else if(count ==8&&example[2]=='.'&&example[5]=='.'&&isValidTime(example)==1)
	{
		b[0]=example[0]-0x30;						// assign value to array
		b[1]=example[1]-0x30;
		b[2]=example[3]-0x30;
		b[3]=example[4]-0x30;
		b[4]=example[6]-0x30;
		b[5]=example[7]-0x30;
		mode_flag=1;
	}
	else if(count ==10&&example[2]=='/'&&example[5]=='/'&&isValidDate(example)==1)
	{
		c[7]=example[9]-0x30;					// assign value to array
		c[6]=example[8]-0x30;
		c[5]=example[7]-0x30;
		c[4]=example[6]-0x30;
		c[3]=example[4]-0x30;
		c[2]=example[3]-0x30;
		c[1]=example[1]-0x30;
		c[0]=example[0]-0x30;
		mode_flag=2;
	}
	else
	{
		wrong_input();
	}
}

// show on screen
void format()									
{
	volatile int temp;
	char a[] = "Format for time'hour:minute:second'- EX: 01:01:01\nFormat for day is 'dd/mm/yyyy' EX:01/01/2001\nFormat for alarm 'hour.minute.second EX: 01.01.01";
	for ( temp=0; a[temp]!='\0';temp ++)
	{
		while((LPUART1->STAT &(1<<23)) ==0); //FULL
		LPUART1->DATA|=a[temp];
	}
}


// wrong input function
static void wrong_input()									
{
	volatile int temp;
	char a[] = "Wrong format\r\n";
	for ( temp=0; a[temp]!='\0';temp ++)
	{
		while((LPUART1->STAT &(1<<23)) ==0); //FULL
		LPUART1->DATA|=a[temp];
	}
}

// set time function
void set_time(char *a)
{
	transferdata(1,a[5]);
	transferdata(2,a[4]);
	transferdata(3,10);
	transferdata(4,a[3]);
	transferdata(5,a[2]);
	transferdata(6,10);
	transferdata(7,a[1]);
	transferdata(8,a[0]);
}

//set day funtion
void set_day(char*b)
{
	transferdata(1,b[7]);
	transferdata(2,b[6]);
	transferdata(3,b[5]);
	transferdata(4,b[4]);
	transferdata(5,b[3]+(1<<7));
	transferdata(6,b[2]);
	transferdata(7,b[1]+(1<<7));
	transferdata(8,b[0]);
}
//set alarm
void set_alarm(char*c)
{
	transferdata(1,c[5]);
	transferdata(2,c[4]);
	transferdata(3,10);
	transferdata(4,c[3]);
	transferdata(5,c[2]);
	transferdata(6,10);
	transferdata(7,c[1]);
	transferdata(8,c[0]);
}

// init led
void light()
{
	transferdata(0xFC,1);
	transferdata(0xFB,0X07);
	transferdata(0xF9,0XFF);
	transferdata(0xFA,0XFF);
	transferdata(0xFF,0);
}

void transferdata(uint8_t address, uint8_t data)
{
	uint16_t temp=0;
	temp |=(address<<8);
	temp |=(data<<0);
	while((LPSPI0->SR &(1<<0))==0);
	LPSPI0->TDR = temp;
}

void clear(char*a) // clear value in string
{
	volatile int temp;
	for (temp=0;a[temp]!='\0';temp++)
	{
		a[temp]=0;
	}
}

void SysTick_Handler ()
{
	SYST->SYST_CSR |=(1<<16);					//clear flag
	count_sys ++;
	real_time++;
	time_for_blink ++;
	time_within_blink ++;
	if(input==1)
	{
		time_for_change ++;
		if(time_for_change==6*3)
		{
			input=0;
			time_for_change=0;
		}
	}
}

void PORTC_IRQHandler(void)
{
    // Check and handle pin 12 interrupt
    if (PORTC_PCR->pin_12 & (1 << 24)) {
        PORTC_PCR->pin_12 |= (1 << 24);  // Clear the interrupt flag
        if (during_alarm == 0) {
            mode_6 += 1;
        } else {
            break_flag = 1;
        }
    }

    // Check and handle pin 13 interrupt
    if (PORTC_PCR->pin_13 & (1 << 24)) {
        PORTC_PCR->pin_13 |= (1 << 24);  // Clear the interrupt flag
        if (during_alarm == 0) {
            mode_7 += 1;
        } else {
            break_flag = 1;
        }
    }
}

char isValidTime(char *a) 
		{
    // Extract hours, minutes, and seconds from the array
    int hours = (a[0]-0x30) * 10 + a[1]-0x30;
    int minutes = (a[3]-0x30) * 10 + a[4]-0x30;
    int seconds = (a[6]-0x30) * 10 + a[7]-0x30;
		
    // Validate hours, minutes, and seconds
    if (hours < 0 || hours > 23) {
        return 0;
    }
    if (minutes < 0 || minutes > 59) {
        return 0;
    }
    if (seconds < 0 || seconds > 59) {
        return 0;
    }

    return 1;
}
		
// Function to check if a year is a leap year
char isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

// Function to validate the date
char isValidDate(char *a) {
    int dd = (a[0]-0x30) * 10 + a[1]-0x30;
    int mm = (a[3]-0x30) * 10 + a[4]-0x30;
    int yyyy = (a[6]-0x30) * 1000 + (a[7]-0x30) * 100 + (a[8]-0x30) * 10 + a[9]-0x30;

    // Days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check if the year is valid
    if (yyyy < 0) {
        return 0;
    }

    // Adjust for leap year
    if (isLeapYear(yyyy)) {
        daysInMonth[1] = 29;
    }

    // Check if the month is valid
    if (mm < 1 || mm > 12) {
        return 0;
    }

    // Check if the day is valid for the given month
    if (dd < 1 || dd > daysInMonth[mm - 1]) {
        return 0;
    }

    return 1;
}

void set_up(void)
{
	volatile unsigned int temp;
	
	set_SOSC(8,1,1);								//SOSC 8Mhz
	set_SPLL(1,3,18,1);								// 8*9=72mhz   div2 = 18
	set_CCR(6,1,2,3);								// divcore 72		bus=36
	set_GPIO('D',16,1,1);			
	
	PCC_PORT->PCC_PORTC |=(1<<30);  				// generate clock
	PORTC_PCR->pin_6 |=(2<<8);						// mux is uart
	PORTC_PCR->pin_7 |=(2<<8);						// mux is uart
	
	PCC_PORT->PCC_LPUART1 |=(6<<24); 
	PCC_PORT->PCC_LPUART1 |=(1<<30); 				// ENABLE CLOCK UART
	
	temp=LPUART1->BAUD ;
	temp&=~(1U<<2);
	temp|= (29<<0);									// SET SBR 
	LPUART1->BAUD =temp;
	
	LPUART1->CTRL |=(1<<4);							// 9bit mode
	LPUART1->CTRL |=(2<<0);							// EVEN parity
	NVIC->NVIC_ISER1    |=(1<<1);					// SET INTERRUPT AT REGISTER 1 PIN 1
	LPUART1->CTRL |= (1<<21);						// RECIEVE INTERRUPT ENABLE
	LPUART1->CTRL |= (1<<20);						// Idle interrupt
	LPUART1->CTRL |= (1<<18);						// ENABLE RECIEVER
	LPUART1->CTRL |=	(1<<19); 					// ENABLE TE
	
	// set up spi
	PCC_PORT->PCC_PORTE |=(1<<30);
	PORTE_PCR->pin_0 |=(2<<8);
	PORTE_PCR->pin_1 |=(2<<8);
	PORTE_PCR->pin_2 |=(2<<8);
	PORTE_PCR->pin_6 |=(2<<8);
	
	PCC_PORT->PCC_LPSPI0 |=(6<<24); 
	PCC_PORT->PCC_LPSPI0 |=(1<<30); 	
		
	// setting clock
	temp=LPSPI0->TCR;
	temp &=~(1u<<27);		// set prescale 1
	//LPSPI0->CCR 			// set sckdiv
	
	// config clock phase
	temp &= ~(3u<<30);  	// PHASE AND POLARITY =0
	
	// setting frame
	temp &=~(1u<<4);
	temp |=(15<<0);			// 16 bits frame size 
	temp &=~(1u<<23);		//MSBF
	
	//conf peripheral chip select
	temp |=(2<<24);			//peripheral chip select
	LPSPI0->TCR =temp;

	// setting transmit/ recieve FIFO
	LPSPI0->CFGR1 |=(1<<3);
	
	// config spi mode
	LPSPI0->CFGR1 |=(1<<0);
	LPSPI0->CR |=(1<<3);
	
	//ENABLE SPI
	LPSPI0->CR |=(1<<0); //ENABLE

	// set interrupt
	set_GPIO('C',12,0,0);
	set_GPIO('C',13,0,0);
	NVIC->NVIC_ISER1    |=(1<<29);				// 	SET INTERRUPT AT REGISTER 1 PIN 29
	PORTC_PCR->pin_12		|=(9<<16);			//	SET INTERRUPT RQ CONTROL
	PORTC_PCR->pin_13		|=(9<<16);			//	SET INTERRUPT RQ CONTROL
	light();									// 	init led
	set_SYSTICK_interrupt(11999999);
	
	format();
}