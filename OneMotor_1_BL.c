// OneMotor1.c
//
// 
// Author: Divya Saravanan
// 
// 

#include <bcm2835.h>
#include <stdio.h>

// RPi Plug P1 pins configuration 

#define IN1 RPI_GPIO_P1_13
#define IN2 RPI_GPIO_P1_15
#define ENA RPI_GPIO_P1_07

int main(int argc, char **argv)
{
    
    if (!bcm2835_init())
      return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(IN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(IN2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);
    
    
    while (1)
    {
	// Turn it off
	printf("Motor1 OFF");
	bcm2835_gpio_write(IN1, LOW);
	bcm2835_gpio_write(IN2, LOW);
	
	
	// wait a bit
	bcm2835_delay(500);
	
	// turn it Forward
	printf("Motor1 FORWARD");
	bcm2835_gpio_write(IN1, LOW);
	bcm2835_gpio_write(IN2, HIGH);
	
	// wait a bit
	bcm2835_delay(5000);
	bcm2835_gpio_write(IN2, LOW);
	
	
	// turn it backward
	printf("Motor1 BACKWARD");
	bcm2835_gpio_write(IN1, HIGH);
	bcm2835_gpio_write(IN2, LOW);
	bcm2835_delay(5000);
	bcm2835_gpio_write(IN1, LOW);
	
    }
  
    printf("Motor1 OFF_2");
    bcm2835_close();
    return 0;
}

