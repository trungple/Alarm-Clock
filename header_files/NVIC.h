//Struct to set NVIC 
typedef struct Nested_vector_interrupt_controller  {
	volatile int 	NVIC_ISER0;
	volatile int 	NVIC_ISER1;
	volatile int 	NVIC_ISER2;
	volatile int 	NVIC_ISER3;
	volatile int 	NVIC_ISER4;
	volatile int 	NVIC_ISER5;
	volatile int 	NVIC_ISER6;
	volatile int 	NVIC_ISER7;
}regis_number;

// ADRESS BASE OF NVIC
#define NVIC_BASE 0xE000E100 

#define NVIC   ((regis_number *) NVIC_BASE) 


