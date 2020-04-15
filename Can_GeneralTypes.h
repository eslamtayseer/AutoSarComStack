#ifndef __CAN_GENERALTYPES_H
#define __CAN_GENERALTYPES_H
#include "ComStack_Types.h"
#include "Std_Types.h"

#define Can_IdType uint16

typedef uint8 Can_HwHandleType;

typedef enum
{
  EXTENDED,
  MIXED,
  STANDARD
} Can_CanIdType;

typedef enum
{
  BASIC,
  FULL
} Can_CanHandleType;

typedef enum
{
  POLLING,
  INTERRUPT
} can_Processing;

typedef enum {
  RECEIVE,
  TRANSMIT
}Can_ObjectType;

typedef struct
{
  Can_IdType CanId;
  Can_HwHandleType Hoh;
  uint8 ControllerId;
} Can_HwType;

typedef struct
{
  PduIdType swPduHandle;
  uint8 length;
  Can_IdType id;
  uint8 *sdu;
} Can_PduType;

typedef struct
{
  boolean CanControllerActivation;
  uint32 CanControllerBaseAddress;
  uint8 CanControllerId;
  can_Processing CanRxProcessing;
  can_Processing CanTxProcessing;
  Can_CanControllerBaudrateConfig *CanControllerDefaultBaudrate;
  // CanCpuClockRef CanCpuClockRef;

} Can_CanController;

typedef struct
{
  uint8 CanControllerBaudRate;
  uint8 CanControllerBaudRateConfigID;
  uint8 CanControllerPropSeg;
  uint8 CanControllerSeg1;
  uint8 CanControllerSeg2;
  uint8 CanControllerSyncJumpWidth;

} Can_CanControllerBaudrateConfig;

typedef struct
{
  Can_CanHandleType CanHandleType;
  uint16 CanHwObjectCount;
  Can_CanIdType CanIdType;
  uint16 CanObjectId;
  Can_ObjectType CanObjectType; 
  Can_CanController* CanControllerRef;
  
  Can_HwType CanHwType;
} Can_CanHardwareObject;

typedef struct
{
  Can_CanController* CanController;
  Can_CanHardwareObject * CanHardwareObject;

} CanConfigSet;

typedef struct
{
  // CanGeneral * CanGeneralConfig;
  CanConfigSet *CanConfigSetConfig;
} Can_ConfigType;

extern const Can_ConfigType CanConfiguration;

#endif
