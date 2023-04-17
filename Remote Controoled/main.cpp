#include "Classes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <unistd.h>
#include <pigpio.h>


int main() {
	if (gpioInitialise() == -1) {
        return -1;
    }
    // create instances of the classes
    Motor motor1(18, 23, 24);  // ENA, IN1, IN2
    Motor motor2(22, 27, 17);  // ENA, IN1, IN2
    //SPIDevice spi_device(0, 5000000, 0);
    
   // uint16_t sample = spi_device.readSample();
    //printf("Sample: %d\n", sample);

    while(true) {
        int x;
        std::cout << "Enter a number: ";
        std::cin >> x;
        std::cout << "You entered: " << x << std::endl;
        
        if(x == 0){
            printf("Moving Forward");
            motor1.setSpeed(0.5);
            motor2.setSpeed(0.5);
            
            unsleep(20000);
            motor1.setSpeed(0);
            motor2.setSpeed(0);
            
        }
        if(x == 1){
            printf("Moving Backwards");
            motor1.setSpeed(-0.5);
            motor2.setSpeed(-0.5);
            
            usleep(20000);
            motor1.setSpeed(0);
            motor2.setSpeed(0);
            
        }
        if(x == 2){
            printf("Moving left");
            motor1.setSpeed(0);
            motor2.setSpeed(0.5);
            
            usleep(20000);
            motor1.setSpeed(0);
            motor2.setSpeed(0);
            
        }
        if(x == 3){
            printf("Moving Right");
            motor1.setSpeed(0.5);
            motor2.setSpeed(0);
            
            usleep(20000);
            motor1.setSpeed(0);
            motor2.setSpeed(0);
            
        }
        // add a delay to prevent the program from constantly reading input
        delay(100);
    }

    return 0;	
}
