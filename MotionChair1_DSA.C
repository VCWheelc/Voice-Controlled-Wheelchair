// MotionChair1.c
//
// 
// Author: Divya Saravanan
// 
// This program senses the FORWARD, REVERSE, LEFT and RIGHT Buttons and
//  activates the motors accordingly.

#include <bcm2835.h>
#include <stdio.h>

// RPi Plug P1 pins configuration for Motor 1
#define INA1 RPI_GPIO_P1_16
#define INA2 RPI_GPIO_P1_15
#define ENA RPI_GPIO_P1_07

// RPi Plug P1 pins configuration for Motor 2
#define INB1 RPI_GPIO_P1_21
#define INB2 RPI_GPIO_P1_22
#define ENB RPI_GPIO_P1_18

//Definition for direction

#define LEFT RPI_GPIO_P1_10
#define RIGHT RPI_GPIO_P1_11
#define FORWARD RPI_GPIO_P1_12
#define REVERSE RPI_GPIO_P1_26

int Option=0;



int main(int argc, char **argv)
{
    
    if (!bcm2835_init())
      return 1;

    // Set the output pins
    bcm2835_gpio_fsel(INA1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(INA2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENA, BCM2835_GPIO_FSEL_OUTP);
    
    bcm2835_gpio_fsel(INB1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(INB2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ENB, BCM2835_GPIO_FSEL_OUTP);
    
    // Set the input pins
    
    bcm2835_gpio_fsel(LEFT, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(LEFT,BCM2835_GPIO_PUD_UP);
    
    bcm2835_gpio_fsel(RIGHT,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(RIGHT,BCM2835_GPIO_PUD_UP);
    
    bcm2835_gpio_fsel(FORWARD,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(FORWARD,BCM2835_GPIO_PUD_UP);
    
    bcm2835_gpio_fsel(REVERSE,BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(REVERSE,BCM2835_GPIO_PUD_UP);   
    
    while (1)
    
    {
	// Check for Left button press
	// Read some data
	uint8_t value1 = bcm2835_gpio_lev(LEFT);
	printf("read from pin 10: %d\n", value1);
	
	// Read some data
	uint8_t value2 = bcm2835_gpio_lev(RIGHT);
	printf("read from pin 11: %d\n", value2);
	
	// Read some data
	uint8_t value3 = bcm2835_gpio_lev(FORWARD);
	printf("read from pin 12: %d\n", value3);
	
	// Read some data
	uint8_t value4 = bcm2835_gpio_lev(REVERSE);
	printf("read from pin 13: %d\n", value4);
	if(value1==0)
	   { printf("Left button is pressed\n");
	     Option=1;
	    }
	// Check for Right button press
	if(value2==0)
	   { printf("Right button is pressed\n");
	     Option=2;
	     
	   }
	 // Check for Forward button press
	 if(value3==0)
	   { printf("Forward button is pressed\n");
	     Option=3;
	     
	   }
	// Check for Reverse button press
	if(value4==0)
	   { printf("Reverse button is pressed\n");
	     Option=4;
	      
	   }
	    else
	    //Option=0;
	printf("No button is pressed\n");
	switch(Option)
	{case 0:
	// Turn it off
	printf("OFF\n");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, LOW);
		
	// wait a bit
	bcm2835_delay(500);
	break;
	
	case 1:
	
	// turn it LEFT
	printf("Left Turn\n");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, HIGH);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(500);
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INB1, LOW);
	
	
	
	case 2:
	// turn it RIGHT
	printf("Right Turn\n");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, HIGH);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(500);
	bcm2835_gpio_write(INA2, LOW);
	bcm2835_gpio_write(INB1, LOW);
	
	break;
	
	case 3:
	// turn it Forward
	printf("Move FORWARD\n");
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, HIGH);
	
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, HIGH);
	
	// wait a bit
	bcm2835_delay(500);
	bcm2835_gpio_write(INA2, LOW);
	bcm2835_gpio_write(INB2, LOW);
	break;
	
	case 4:
	// turn it backward
	printf("Move Reverse\n");
	bcm2835_gpio_write(INA1, HIGH);
	bcm2835_gpio_write(INA2, LOW);
	
	bcm2835_gpio_write(INB1, HIGH);
	bcm2835_gpio_write(INB2, LOW);
	
	bcm2835_delay(500);
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INB1, LOW);
	break;
	
	default:
	bcm2835_gpio_write(INA1, LOW);
	bcm2835_gpio_write(INA2, LOW);
	bcm2835_gpio_write(INB1, LOW);
	bcm2835_gpio_write(INB2, LOW);
	}
    }
  
    printf("Motors OFF\n");
    bcm2835_close();
    return 0;
}

