#ifndef __COM_LCFG_H
#define __COM_LCFG_H

#include "Com_Pbcfg.h"

typedef struct 
{
    const signal * comSignals;
    const pdu * comPdus;
 
}Com_ConfigType;

extern const Com_ConfigType configuration;

#endif
