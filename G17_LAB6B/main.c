#include <stdint.h>
#include "tm4c123gh6pm.h"

volatile uint32_t dutyCycle = 50;  // Initial duty cycle: 50%
volatile uint32_t count = 160;    // Count Value Using 16MHz clock frequency
volatile uint32_t pressTime = 0;   // Time the button has been held down
volatile uint8_t bp = 0; // button press detection

void init(void);
void Systick_Init(void);
void GPIO_Handler(void);
void Systick_Handler(void);
void init(void) {

    SYSCTL_RCGCGPIO_R |= 0x020;
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x10;
    GPIO_PORTF_DIR_R = 0x02;
    GPIO_PORTF_DEN_R = 0x12; // Digital enable for PF1 and PF4
    GPIO_PORTF_PUR_R |= 0x01;  // Enable pull-up resistor for the switch


    GPIO_PORTF_IS_R = 0x00;   // Edge-sensitive
    GPIO_PORTF_IBE_R = 0x00;  // Interrupt controlled by IEV
    GPIO_PORTF_IEV_R = 0x00;  // Falling edge trigger (button press)
    GPIO_PORTF_ICR_R = 0x10;   // Clear any prior interrupt
    GPIO_PORTF_IM_R = 0x10;    // Unmask interrupt for PF4

    NVIC_EN0_R = 0x40000000 ;
}
void Systick_Init(void) {
    NVIC_ST_RELOAD_R = count - 1;
    NVIC_ST_CTRL_R = 0x07; //
}
int main(void) {
    init();   // Initialize GPIO for switches and LED
    Systick_Init(); // Initialize SysTick timer
}
void Systick_Handler(void)
{
    static uint32_t onTime = 0; // Count for the "ON" duration


    if (onTime < (dutyCycle * count) / 100)
    {
        GPIO_PORTF_DATA_R |= 0x02; // red led on
    }
    else
    {
        GPIO_PORTF_DATA_R &= ~0x02; // red led off
    }

    onTime++;
    if (onTime >= count)
    {
        onTime = 0;  // Reset onTime after it reaches upto count value
    }

    if (bp) {
        pressTime++;
    }
}

void GPIO_Handler(void) {
    if (GPIO_PORTF_RIS_R & 0x10) {
        bp = 1;

        GPIO_PORTF_ICR_R |= 0x10; // Clear the interrupt
    }

    if ((GPIO_PORTF_DATA_R & 0x10) == 0x10)   // Button is released
    {
        if (bp)
        {
            if (pressTime < 100000)  // Short press
            {

                if (dutyCycle < 100)
                {
                    dutyCycle += 5; // Increase duty cycle by 5%
                }
            }
            else
            {  // Long press

                if (dutyCycle > 0)
                {
                    dutyCycle -= 5; // Decrease duty cycle by 5%
                }
            }

            pressTime = 0;
            bp = 0;
        }
    }
}
