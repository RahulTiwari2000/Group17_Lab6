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
void init(void) {

    SYSCTL_RCGCGPIO_R |= 0x020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x10;
    GPIO_PORTF_DIR_R = 0x02;
    GPIO_PORTF_DEN_R = 0x12; // Digital enable for PF1 and PF4
    GPIO_PORTF_PUR_R |= 0x01;  // Enable pull-up resistor for the switch


}
