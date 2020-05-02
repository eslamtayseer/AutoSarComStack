//#include "Can_GeneralTypes.h"
#include "Can_PBcfg.h"
Can_CanControllerBaudrateConfig CanControllersBaudRate[] = {
  {
    .CanControllerBaudRate = 500,
    .CanControllerBaudRateConfigID = 0,
    .CanControllerPropSeg = 6,
    .CanControllerSeg1 = 3,
    .CanControllerSeg2 = 3,
    .CanControllerSyncJumpWidth = 1
  }
};

Can_CanController CanControllers[] = {
  {
    .CanControllerActivation = TRUE,
    .CanControllerBaseAddress = 0xFBEC0000,
    .CanControllerId = 0,
    .CanRxProcessing = INTERRUPT,
    .CanTxProcessing = INTERRUPT,
    .CanControllerDefaultBaudrate = &CanControllersBaudRate[0]
  }
};


Can_CanHardwareObject CanHardwareObjects[] = {
  {
    .CanHandleType = FULL,
    .CanHwObjectCount = 1,
    .CanIdType = STANDARD,
    .CanObjectId = 0,
    .CanObjectType = RECEIVE,
    .CanControllerRef = &CanControllers[0],
    .CanHwType = {
      .CanId = 0,
      .Hoh = 0,
      .ControllerId = 0
    }
  },
  {
    .CanHandleType = FULL,
    .CanHwObjectCount = 1,
    .CanIdType = STANDARD,
    .CanObjectId = 1,
    .CanObjectType = TRANSMIT,
    .CanControllerRef = &CanControllers[0],
    .CanHwType = {
      .CanId = 1,
      .Hoh = 1,
      .ControllerId = 0
    }
  }
};

CanConfigSet ConfigSets[] = {
  {
    .CanController = CanControllers,
    .CanHardwareObject = CanHardwareObjects
  }
};

const Can_ConfigType CanConfiguration = {
  .CanConfigSetConfig = ConfigSets
};
