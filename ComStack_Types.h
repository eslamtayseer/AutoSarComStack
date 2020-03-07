#ifndef __COMSTACK_TYPES_H
#define __COMSTACK_TYPES_H

#include "Std_Types.h"

typedef uint16 Com_SignalIdType ;
typedef uint16 Com_PduIdType ;

typedef enum
{
    RECIEVE,
    SEND
} Com_PduDirectionType;

typedef enum{
    PENDING,
    TRIGGERED,
    TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
    TRIGGERD_ON_CHANGE
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

#endif
