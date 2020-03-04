#ifndef __COMSTACK_TYPES_H
#define __COMSTACK_TYPES_H
#include "Std_Types.h"

typedef uint16 Com_SignalIdType ;
typedef uint16 Com_PduIdType ;

typedef enum
{
    RECIEVE,
    SEND
} ComIPduDirection_type;
typedef enum{
    PENDING,
    TRIGGERED,
    TRIGGERED_ON_CHANGE_WITHOUT_REPETITION,
    TRIGGERD_ON_CHANGE
}signalType;

typedef enum{
    MIXED,
    PERIODIC,
    DIRECT

}pduType;

#endif