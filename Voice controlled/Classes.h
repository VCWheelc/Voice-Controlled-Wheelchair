#ifndef CLASSES_H_
#define CLASSES_H_

#include <stdint.h>

class Motor {
private:
    uint8_t ena, in1, in2;
public:
    Motor(uint8_t ena_pin, uint8_t in1_pin, uint8_t in2_pin);
    void setSpeed(double speed);
};

class SPIDevice {
public:
    SPIDevice(int channel, uint32_t speed, uint8_t mode);
    uint16_t readSample();
private:
    int channel_;
    uint32_t speed_;
    uint8_t mode_;
};

#endif /* CLASSES_H_ */
