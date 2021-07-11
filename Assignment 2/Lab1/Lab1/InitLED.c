#include "MKL46Z4.h"                    // NXP::Device:Startup
void InitLED(void){ 
/*This function enables the red LED on the FRDM-KL46Z development board*/
/*Note, each chapter from the KL46 Reference Manual is a structure, while each register is a member of that structure, so we address them by Chapter -> Register*/
SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; 
//This enables the clock to PORTD
PORTD->PCR[5] = PORT_PCR_MUX(1u); 
//This sets the Mux control of PTD5 to 001, or GPIO
PTD->PDDR |= (1u<<5); 
/*This sets PTD5 as an output.  There are no masks defined for each pin so we have to do it by hand and just comment well.*/
}
