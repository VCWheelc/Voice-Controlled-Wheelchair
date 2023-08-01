#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

using namespace std;

const uint8_t PWM_MAX = 70;

class Motor {
private:
    uint8_t ena, in1, in2;
public:
    Motor(uint8_t ena_pin, uint8_t in1_pin, uint8_t in2_pin) {
        ena = ena_pin;
        in1 = in1_pin;
        in2 = in2_pin;
        gpioSetMode(ena, PI_OUTPUT);
        gpioSetMode(in1, PI_OUTPUT);
        gpioSetMode(in2, PI_OUTPUT);
        gpioSetMode(in1, PI_LOW);
        gpioSetMode(in2, PI_LOW);
        gpioSetPWMfrequency(ena, 60);
        gpioSetPWMrange(ena, 100);
        gpioPWM(ena, 0);
    }
    void setSpeed(double speed) {
        uint8_t pwm;
        if(speed > 0) {
            gpioWrite(in1, PI_LOW);
            gpioWrite(in2, PI_HIGH);
            pwm = (uint8_t)(PWM_MAX * speed);
        } else if(speed < 0) {
            gpioWrite(in1, PI_HIGH);
            gpioWrite(in2, PI_LOW);
            pwm = (uint8_t)(PWM_MAX * -speed);
        } else {
            gpioWrite(in1, PI_LOW);
            gpioWrite(in2, PI_LOW);
            pwm = 0;
        }
        if(pwm > PWM_MAX) {
            pwm = PWM_MAX;
        }
        gpioPWM(ena, pwm);
    }
};

int main() {
    if (gpioInitialise() == -1) {
        return -1;
    }

    Motor motor1(25, 23, 24);  // ENA, IN1, IN2
    Motor motor2(22, 27, 17);  // ENA, IN1, IN2

    printf("Driving forward:\n");
    double speed;
    for (int i = 0; i < 10; i++) {
        speed = 0.1 * i;
        printf("set speed to %f \n", speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);

    usleep(3000000);

    printf("Driving reverse:\n");
    for (int i = 0; i < 10; i++) {
        speed = -0.1 * i;
        printf("set speed to %f \n", speed);
        motor1.setSpeed(speed);
        motor2.setSpeed(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    
    printf("Driving left:\n");
    for (int i = 0; i < 10; i++) {
        speed = 0.1 * i;
        printf("set speed to %f \n", speed);
        motor1.setSpeed(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    
    printf("Driving right:\n");
    for (int i = 0; i < 10; i++) {
        speed = 0.1 * i;
        printf("set speed to %f \n", speed);
        motor2.setSpeed(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);

    gpioTerminate();
    return 0;
}
