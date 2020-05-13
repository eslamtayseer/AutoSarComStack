#ifndef __CAN_API_H
#define __CAN_API_H

extern void hw_init(void);
void Sysclk_Init(void);
 void GPIO_Init(void);
 void FlexCAN_1_Init();
 void Configure_RX_MessageBuffer(void);
 void Transmit_Message();

#endif
