#ifndef __CAN_API_H
#define __CAN_API_H

static void HW_Init(void);
static void Sysclk_Init(void);
static void GPIO_Init(void);
static void FlexCAN_1_Init();
static void Configure_RX_MessageBuffer(void);
static void Transmit_Message();

#endif
