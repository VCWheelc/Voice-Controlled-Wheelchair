#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

using namespace std;

const uint8_t PWM_MAX = 70;
const uint8_t ENA = 25; // Pin 40   //enableMotor Pin
const uint8_t IN1 = 24; // Pin 38    //forwardPin
const uint8_t IN2 = 23; // Pin 36   //backwardPin

void init() {
    gpioSetMode(ENA, PI_OUTPUT);
    gpioSetMode(IN1, PI_OUTPUT);
    gpioSetMode(IN2, PI_OUTPUT);
    gpioSetMode(IN1, PI_LOW);
    gpioSetMode(IN2, PI_LOW);
    gpioSetPWMfrequency(ENA, 60);
    gpioSetPWMrange(ENA, 100);
    gpioPWM(ENA, 0);
}

void setMotorMode(const string &mode) {
    printf("set motor mode to %s \n", mode.c_str());
    if(mode == "forward") {
        gpioSetMode(IN1, PI_LOW);
        gpioSetMode(IN2, PI_HIGH);
    } else if(mode == "reverse") {
        gpioSetMode(IN1, PI_HIGH);
        gpioSetMode(IN2, PI_LOW);
    } else {
        gpioSetMode(IN1, PI_LOW);
        gpioSetMode(IN2, PI_LOW);
    }
}

void setMotor(const double &power) {
    uint8_t pwm;
    if(power > 0) {
        setMotorMode("forward");
        pwm = (int)(PWM_MAX * power);
    } else if(power < 0) {
        setMotorMode("reverse");
        pwm = -(int)(PWM_MAX * power);
    } else {
        setMotorMode("stopp");
        pwm = 0;
    }

    if(pwm > PWM_MAX) {
        pwm = PWM_MAX;
    }

    printf("set pwm to %d \n", pwm);
    gpioPWM(ENA, pwm);
}

int main()
{
    if (gpioInitialise() == -1)
        return -1;

    printf("Driving forward:\n");
    double speed;
    for (int i = 0; i < 10; i++) {
        speed = 0.1 * i;
        printf("set speed to %f \n", speed);
        setMotor(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    setMotor(speed);

    usleep(3000000);

    printf("Driving reverse:\n");
    for (int i = 0; i < 10; i++) {
        speed = -0.1 * i;
        printf("set speed to %f \n", speed);
        setMotor(speed);
        usleep(1000000);
    }

    usleep(3000000);

    speed = 0;
    setMotor(speed);
}
