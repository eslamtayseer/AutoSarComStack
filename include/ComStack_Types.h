#ifndef __COMSTACK_TYPES_H
#define __COMSTACK_TYPES_H

#include "Std_Types.h"

typedef uint16 Com_SignalIdType ;
typedef uint16 PduIdType ;
typedef uint16 PduLengthType ;

typedef enum
{
    RECIEVE,
    SEND
} Com_PduDirectionType;

typedef enum{
    PENDING,
    TRIGGERED,
    TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
    TRIGGERD_ON_CHANGE,
    TRIGGERED_WITHOUT_REPETITION
} Com_SignalType;

typedef enum{
    MIXED,
    PERIODIC,
    DIRECT
} Com_ComTxModeMode;

typedef enum
{
  STARTED,
  STOPPED
} Com_PDUStatusType;


typedef struct
{
  uint64 *SduDataPtr;
  uint8 *MetaDataPtr;
  PduLengthType SduLength;
} PduInfoType;

#endif
