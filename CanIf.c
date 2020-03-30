#include "CanIf.h"

void FindCanPduBySduId (PduIdType Id, CanIfTxPduCfg *CanIfPdu); /*Private function shouldn't be part of the exposed API*/

const CanIf_ConfigType *Configuration;

void CanIf_Init (CanIf_ConfigType *ConfigPtr)
{
  Configuration = ConfigPtr;
  
  // TODO: Should set the mode of each Controller
}

Std_ReturnType CanIf_Transmit (PduIdType CanIfTxSduId, const PduInfoType *CanIfTxInfoPtr)
{
  CanIfTxPduCfg *CanIfTxPdu;
  if (FindCanPduId (CanIfTxSduId, CanIfTxPdu) == TRUE)
  {
    
  }
}

boolean FindCanPduBySduId (PduIdType Id, CanIfTxPduCfg *CanIfPdu)
{
  CanIfTxPduCfg *CanIfConfigTxPdus = Configuration->CanIfInitCfg->CanIfTxPdusCfgs;
  uint8 CanIfConfigTxPdusNumber = Configuration->CanIfInitCfg->CanIfMaxTxPduCfg;
  
  for (int i = 0; i < CanIfConfigTxPdusNumber; i++)
  {
    if (Id == CanIfConfigTxPdus[i]->CanIfTxPduId)
    {
      CanIfPdu = &CanIfConfigTxPdus[i];
      return TRUE;
    }
  }
  
  return FALSE;
}
