#include "PinNames.h"
#include "ThisThread.h"
#include "mbed.h"
#include <chrono>

CAN can1(PD_0, PD_1, 1000000);

int main() {
    CANMessage msg;
    while(1) {
        if (can1.read(msg)) {
            printf("Message received: ");
            for(size_t dataNum = 0; dataNum < msg.len; ++dataNum)
            {
                printf("%02x ", msg.data[dataNum]);
            }
            printf("\n");
        } 
        ThisThread::sleep_for(chrono::seconds(2));
    }
}