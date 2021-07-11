#include "MKL46Z4.h"                    // NXP::Device:Startup
#include "LED.h"                    // NXP::Device:Startup

int main(void){
    InitLED(); //Initialize LED for use
    while(1){ //Main loop
        BlinkLED3(); 
    } //End main loop
}//End main
