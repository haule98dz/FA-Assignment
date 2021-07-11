#include "MKL46Z4.h"                    // NXP::Device:Startup
void BlinkLED2(void){
//This method turns the LED off, then back on using PDOR
    /*Note the use of |= and &=.  This allows you to change the 5th bit of PDOR without disturbing the other bits.  The other methods do not require this as setting PSOR/PCOR/PTOR = 0 does not change the output.*/
    uint32_t i = 0; //Create a loop variable
     
PTD->PDOR |= (1u<<5);
 //Change PTD5 to 1, turns LED OFF (Cathode connected to PTD5)
    for(i=0; i < 3000000; i++){};//Burn some time
PTD->PDOR &= ~((uint32_t)(1u<<5));
 /*Change PTD5 to 0 to turns LED ON.  This line is a bit weird.  First it takes 1u<<5 and typecasts it to a 32 bit value.  It then takes the inverse of it, so all bits are 1 except bit 5.  It then logical ands it with the current PDOR, which will retain all values except bit 5 which will be changed to 0.*/
    for(i=0; i < 3000000; i++){}; //Burn some time
}
