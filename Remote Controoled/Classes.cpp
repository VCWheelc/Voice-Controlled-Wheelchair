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
#include <stdlib.h>
#include <pigpio.h>

#define PWM_MAX 100

Motor::Motor(uint8_t ena_pin, uint8_t in1_pin, uint8_t in2_pin) {
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

void Motor::setSpeed(double speed) {
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

SPIDevice::SPIDevice(int channel, uint32_t speed, uint8_t mode) {
    channel_ = channel;
    speed_ = speed;
    mode_ = mode;
    if (wiringPiSPISetupMode(channel_, speed_, mode_) < 0) {
        printf("SPI Setup failed: %s\n", strerror(errno));
        exit(-1);
    }
}

uint16_t SPIDevice::readSample() {
    uint8_t buf[4] = {0x40, 0x00, 0x00, 0x00};
    wiringPiSPIDataRW(channel_, buf, sizeof(buf));
    uint16_t sample = ((buf[2] & 0x7F) << 8) | buf[3];
    return sample;
}
