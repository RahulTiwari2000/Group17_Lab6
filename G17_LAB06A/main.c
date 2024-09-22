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
                       GPIO_PORTF_CR_R |= 0x10;          // Allow changes to PF4

                           // Configure PF1 as output (LED)
                           GPIO_PORTF_DIR_R = 0x02;
                           GPIO_PORTF_DEN_R = 0x13;

                           GPIO_PORTF_PUR_R = 0x11;


                       GPIO_PORTF_IS_R = 0x00;   //  edge-sensitive
                          GPIO_PORTF_IBE_R = 0x00;  // Interrupt controlled by IEV
                          GPIO_PORTF_IEV_R = 0x00;  // Falling edge trigger
                          GPIO_PORTF_ICR_R = 0x11;   // removing prior interrupt
                          GPIO_PORTF_IM_R = 0x11;    // Unmask interrupt for PF4

                          NVIC_EN0_R = 0x40000000;
}
void Systick_Init(void) {

    NVIC_ST_RELOAD_R = count - 1;
    NVIC_ST_CTRL_R = 0x07;
}
