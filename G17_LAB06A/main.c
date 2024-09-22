#include <stdint.h>
#include "tm4c123gh6pm.h"

volatile uint32_t dutyCycle = 50;  // Initial duty cycle: 50%
volatile uint32_t count = 160;    // Count Value Using 16MHz clock frequency

void init(void);               // init function declaration
void Systick_Init(void);       //Systick_Init function declaration
void GPIO_Handler(void);      //GPIO Function declaration
void Systick_Handler(void);   //Systick_handler function declaration

int main(void) {

}

