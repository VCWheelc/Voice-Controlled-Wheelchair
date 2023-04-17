#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2S.h>

int main(void) {
  // Initialize wiringPi and I2S interface
  wiringPiSetup();
  wiringPiI2SSetup(0, 16000);

  // Main loop to read and print audio data
  while(1) {
    int sample = wiringPiI2SRead(0);
    if(sample != 0) {
      // convert to 18 bit signed
      sample >>= 14;
      printf("%d\n", sample);
    }
  }

  return 0;
}