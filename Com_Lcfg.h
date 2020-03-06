#ifndef __COM_LCFG_H
#define __COM_LCFG_H

#include "Com_Pbcfg.h"

typedef struct
{
  const Com_ConfigSignalType *signals;
  const Com_ConfigPDUType    *pdus;
} Com_ConfigType;

extern const Com_ConfigType configuration;

#endif
