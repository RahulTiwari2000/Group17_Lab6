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

int main(void) {
    
}