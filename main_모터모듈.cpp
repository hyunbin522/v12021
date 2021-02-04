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

// /* mbed Microcontroller Library
//  * Copyright (c) 2019 ARM Limited
//  * SPDX-License-Identifier: Apache-2.0
//  */

// #include "mbed.h"
// #include "PinNames.h"
// #include "ThisThread.h"
// #include <cctype>
// #include <chrono>
// #include <cstdio>
// #include "Unitconversion.h"

// // Blinking rate in milliseconds
// //#define BLINKING_RATE     500ms

// ParameterRange range(-95.5f, 95.5f, -45.0f, 45.0f, -18.0f, 18.0f, 0.0f, 500.0f, 0.0f, 5.0f);
// float position[12];
// float velocity[12];
// float kp[12]={10,10,10,10,10,10,10,10,10,10,10,10};
// float kd[12]={1,1,1,1,1,1,1,1,1,1,1,1};
// float torque[12];
// unsigned char data[8];
// unsigned char data1[8];
// unsigned char data2[8];
// unsigned char data3[8];
// unsigned char data4[8];
// unsigned char data5[8];
// unsigned char data6[8];
// unsigned char data7[8];
// unsigned char data8[8];
// unsigned char data9[8];
// unsigned char data10[8];
// unsigned char data11[8];
// unsigned char data12[8];
// float rdata[4];

// // FF FF FF FF FF FF FF FC,(MOTOR ON), FF FF FF FF FF FF FF FD(MOTOR OFF), FF FF FF FF FF FF FF FE(ZERO POSITION), 7F FF 7F F0 00 00 07 FF(위치 조정)
// int main()
// {
//     CAN can(PD_0, PD_1,1000000);
//     EventQueue queue;

//     enum State {
//         Prompt = 0, MessageSent
//     } state = Prompt;
//     enum MotorState
//     {
//         Off = 0, Active, OffRequested
//     } motorState = Off;

//     while (true) {
//         switch(state)
//         {
//             case Prompt:
//             {
//                 switch(motorState)
//                 {
//                     case Off:
//                     {
//                         printf("press 'c' to turn on motor or 'q' to exit program ,,,, \n please locate each motor position at zero position before turn on motor\n");
//                         char key;
//                         scanf("%c", &key);  
//                         switch(tolower(key))
//                         {
//                             case 'c':
//                             {
//                                 unsigned char datazp[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe};
//                                 if(can.write(CANMessage(1, datazp))&&can.write(CANMessage(2,datazp)))//&&can.write(CANMessage(3,datato))//&&can.write(CANMessage(4,datato))
//                                 //&&can.write(CANMessage(5,datato))&&can.write(CANMessage(6,datato))&&can.write(CANMessage(7,datato))&&can.write(CANMessage(8,datato))
//                                 //&&can.write(CANMessage(9,datato))&&can.write(CANMessage(10,datato))&&can.write(CANMessage(11,datato))&&can.write(CANMessage(12,datato)))
//                                 {   
//                                     printf("All zero position messages sent\n");
//                                     state = MessageSent;
//                                     unsigned char datato[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
//                                     if(can.write(CANMessage(1, datato))&&can.write(CANMessage(2,datato)))//&&can.write(CANMessage(3,datato))&&can.write(CANMessage(4,datato))
//                                     //&&can.write(CANMessage(5,datato))&&can.write(CANMessage(6,datato))&&can.write(CANMessage(7,datato))&&can.write(CANMessage(8,datato))
//                                     //&&can.write(CANMessage(9,datato))&&can.write(CANMessage(10,datato))&&can.write(CANMessage(11,datato))&&can.write(CANMessage(12,datato)))
//                                     {   
//                                         printf("All turn on messages sent\n");
//                                         state = MessageSent;
//                                     }
//                                     else
//                                     {
//                                         printf("sending some turn on message failed\n");
//                                     }
//                                 }
//                                 else 
//                                 {
//                                     printf("sending some zero position message failed\n");
//                                 }
//                             }
//                             break;

//                             case 'q':
//                             return 0;

//                             default:
//                                 printf("wrong key!\n");
//                             break;
//                         }      
//                     }                        
//                     break;

//                     case Active:
//                     {
//                         printf("press 'p' for Position Mode or press 't' for Torque Mode or press 'o' to turn off motor or 'q' to exit program");
//                         char key;
//                         scanf("%c", &key);  
//                         switch(tolower(key))
//                         {
//                             case 'c':       //printf "모터 3 일단 두개만 1번 w위로 s작게 2번 e위로 d작게 position "
//                              {  
//                                 unsigned char data[8] = {0x7f, 0xff, 0x7f, 0xf0, 0x00, 0x00, 0x07, 0xff};
//                                 if(can.write(CANMessage(1, data)))
//                                 {
//                                     printf("a set position message sent\n");
//                                     state = MessageSent;
//                                 }
//                                 else {
//                                     printf("sending a set position message failed\n");
//                                 }
//                             }
//                             break;

//                             case 'o':
//                             {
//                                 unsigned char data[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd};
//                                 if(can.write(CANMessage(1, data)))
//                                 {
//                                     state = MessageSent;
//                                     motorState = OffRequested;
//                                 }
//                                 else {
//                                     printf("a turn off message sent\n");
//                                     printf("sending a turn off message failed\n");
//                                 }
//                             }
//                             break;

//                             case 'q':
//                             return 0;

//                              default:
//                                 printf("wrong key!\n");
//                             break;
//                         }      
//                     }
//                     break;

//                     default:
//                     break;
//                 }
//             }
//             break;

//             case MessageSent:
//             {
//                 printf("waiting for message..\n");
//                 CANMessage message;
//                 if(can.read(message))
//                 {
//                     switch(motorState)
//                     {
//                         case Off:
//                         printf("a turn on message received\n");
//                         motorState = Select;
//                         break;
                       
//                         case Active:
//                         printf("reply recieived:");
//                         for(size_t receive = 0; receive < message.len; ++receive)
//                         {
//                             printf(" 0x%02x", message.data[receive]);
//                         }
//                         RevMiniCheetahCANData(message.data,range,rdata);
//                         printf("motor id: %f , position: %f , velocity: %f , torque: %f \n",rdata[0],rdata[1],rdata[2],rdata[3]);
//                         printf("\n");
//                         break;
                                                
//                         case OffRequested:
//                         printf("a turn off message received\n");
//                         motorState = Off;
//                         break;
//                     }
//                     state = Prompt;
//                 }
//                 else {
//                     ThisThread::sleep_for(Kernel::Clock::duration_u32(200));
//                 }
//             }
//             break;
//         }
//     }
// }
