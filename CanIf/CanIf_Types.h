#ifndef __CANIF_TYPES_H
#define __CANIF_TYPES_H

typedef enum
{
  EXTENDED_CAN,
  EXTENDED_FD_CAN,
  EXTENDED_NO_FD_CAN,
  STANDARD_CAN,
  STANDARD_FD_CAN,
  STANDARD_NO_FD_CAN
} CanIfPduCanIdType;

typedef enum
{
  DYNAMIC,
  STATIC
} CanIfPduType;

typedef enum
{
  CAN_NM,
  CAN_TP,
  CAN_TSYN,
  CDD,
  J1939NM,
  J1939TP,
  PDUR,
  XCP
} CanIfPduUserConfirmationUL;

#endif

