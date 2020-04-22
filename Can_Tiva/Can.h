#include "Can_PBcfg.h"
void Can_Init(
 const Can_ConfigType* Config
);
void Hardware_Init();
Can_ReturnType Can_Write(
 Can_HwHandleType Hth,
 const Can_PduType* PduInfo
);
