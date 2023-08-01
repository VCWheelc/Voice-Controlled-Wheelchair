// TwoMotor1.c
//
// 
// Author: Divya Saravanan
// C

#include <bcm2835.h>
#include <stdio.h>

// RPi Plug P1 pins configuration 
#define INA1 RPI_GPIO_P1_13
#define INA2 RPI_GPIO_P1_15
#define ENA RPI_GPIO_P1_07

#define INB1 RPI_GPIO_P1_23
#define INB2 RPI_GPIO_P1_24
#define ENB RPI_GPIO_P1_18

int main(int argc, char **argv)
{
    
    if (!bcm2835_init())
      return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(INA1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(INA2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);
    
    bcm2835_gpio_fsel(INB1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(INB2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_OUTP);
    
    
    while (1)
    {
	// Turn it off
	printf("Motor1 & 2 OFF");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, LOW);
	
	// wait a bit
	bcm2835_delay(500);
	
	// turn it Forward
	printf("FORWARD");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, HIGH);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, HIGH);
	
	// wait a bit
	bcm2835_delay(5000);
	bcm2835_gpio_write(INA2, LOW);
	bcm2835_gpio_write(INB2, LOW);
	
	
	// turn it backward
	printf("Motor1 BACKWARD");
	bcm2835_gpio_write(INA1, HIGH);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, HIGH);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(5000);
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INB1, LOW);
	
	// turn it LEFT
	printf("Motor1 BACKWARD");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, HIGH);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(5000);
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INB1, LOW);
	
	// turn it RIGHT
	printf("Motor1 BACKWARD");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, HIGH);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(5000);
	bcm2835_gpio_write(INA2, LOW);
	bcm2835_gpio_write(INB1, LOW);
    }
  
    printf("Motor1 OFF_2");
    bcm2835_close();
    return 0;
}

