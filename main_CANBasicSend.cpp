#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include <chrono>
 
CAN can1(PD_0, PD_1, 1000000);
char counter = 0;

int main() {
    while(1) {
         unsigned char data[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
        if (can1.write(CANMessage(1, data))) {
            counter++;
            printf("message %d sent\n", counter);

        }
        else {
            printf("message sending failed\n");
        }
         ThisThread::sleep_for(chrono::seconds(2));
    }
}