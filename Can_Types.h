#ifndef __CAN_TYPES_H
#define __CAN_TYPES_H
#include "ComStack_Types.h"
#include "Std_Types.h"

#define  Can_IdType uint16

typedef struct 
    {
      PduIdType  swPduHandle;
      uint8      length;
      Can_IdType id;
      uint8*     sdu;
    } Can_PduType;

#endif