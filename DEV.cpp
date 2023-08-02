// MotionChair.cpp
// 
// Author: Divya Saravanan
// 

#include <bcm2835.h>
#include <stdio.h>

class GPIO {
public:
    GPIO(int pin, int mode) {
        this->pin = pin;
        bcm2835_gpio_fsel(pin, mode);
    }
    
    void write(int level) {
        bcm2835_gpio_write(pin, level);
    }

private:
    int pin;
};

class Button {
public:
    Button(int pin) : gpio(pin, BCM2835_GPIO_FSEL_INPT) {
        bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
    }

    bool event() {
        if(bcm2835_gpio_eds(pin)) {
            bcm2835_gpio_set_eds(pin); 
            return true;
        } 
        return false;
    }
private:
    GPIO gpio;
    int pin;
};

class Motor {
public:
    Motor(int INA, int INB) : gpio1(INA, BCM2835_GPIO_FSEL_OUTP), gpio2(INB, BCM2835_GPIO_FSEL_OUTP) {}

    void turn_off() {
        gpio1.write(LOW);
        gpio2.write(LOW);
    }

    void forward() {
        gpio1.write(LOW);
        gpio2.write(HIGH);
    }

    void backward() {
        gpio1.write(HIGH);
        gpio2.write(LOW);
    }
    
private:
    GPIO gpio1, gpio2;
};

int main(int argc, char **argv) {
    if (!bcm2835_init())
        return 1;
    
    Button left(RPI_GPIO_P1_10), right(RPI_GPIO_P1_11), forward(RPI_GPIO_P1_12), reverse(RPI_GPIO_P1_13);
    Motor motor1(RPI_GPIO_P1_13, RPI_GPIO_P1_15), motor2(RPI_GPIO_P1_23, RPI_GPIO_P1_24);

    int Option = 0;

    while (1) {
        if (left.event()) {
            Option = 1;
        } else if (right.event()) {
            Option = 2;
        } else if (forward.event()) {
            Option = 3;
        } else if (reverse.event()) {
            Option = 4;
        } else {
            Option = 0;
        }

        switch (Option) {
            case 0:
                printf("Motor1 & 2 OFF");
                motor1.turn_off();
                motor2.turn_off();
                bcm2835_delay(500);
                break;
            case 1:
                printf("Motor1 BACKWARD");
                motor1.backward();
                bcm2835_delay(5000);
                motor1.turn_off();
                break;
            case 2:
                printf("Motor1 BACKWARD");
                motor1.backward();
                bcm2835_delay(5000);
                motor1.turn_off();
                break;
            case 3:
                printf("FORWARD");
                motor1.forward();
                bcm2835_delay(5000);
                motor1.turn_off();
                break;
            case 4:
                printf("Motor1 BACKWARD");
                motor1.backward();
                bcm2835_delay(5000);
                motor1.turn_off();
                break;
            default:
                motor1.turn_off();
                motor2.turn_off();
        }
    }

    printf("Motor1 OFF_2");
    bcm2835_close();
    return 0;
}