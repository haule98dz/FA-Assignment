#include "MKL46Z4.h"                    // NXP::Device:Startup
void BlinkLED3(void){
/*This method turns the LED off, then back on using a single command.  It must be run twice in order to blink the LED.*/
    uint32_t i = 0; //Create a loop variable
     
    PTD->PTOR = (1u<<5); //Toggles PTD5 and the LED
    for(i=0; i < 3000000; i++){}; //Burn some time
}
