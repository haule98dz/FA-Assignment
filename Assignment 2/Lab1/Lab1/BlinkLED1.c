#include "MKL46Z4.h"                    // NXP::Device:Startup

void BlinkLED1(void){
//This method turns the LED off, then back on using two separate commands.
    uint32_t i = 0; //Create a loop variable
     
    PTD->PSOR = (1u<<5); //Set PTD5 = 1, turns LED OFF (Cathode connected to PTD5)
    for(i=0; i < 3000000; i++){}; //Burn some time
    PTD->PCOR = (1u<<5);//Clear PTD5 = 0, turns LED ON
    for(i=0; i < 3000000; i++){};//Burn some time
}
