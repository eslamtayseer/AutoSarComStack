#include "CanIf.h"

boolean FindCanPduBySduId (PduIdType Id, CanIfTxPduCfg *CanIfPdu); /*Private function shouldn't be part of the exposed API*/

const CanIf_ConfigType *Configuration;

void CanIf_Init (CanIf_ConfigType *ConfigPtr)
{
  Configuration = ConfigPtr;
  
  // TODO: Should set the mode of each Controller
}

Std_ReturnType CanIf_Transmit (PduIdType CanIfTxSduId, const PduInfoType *CanIfTxInfoPtr)
{
  CanIfTxPduCfg CanIfTxPdu;
  if (FindCanPduBySduId (CanIfTxSduId, &CanIfTxPdu) == TRUE && CanIfTxInfoPtr != 0)
  {
      Can_PduType canPdu;
      canPdu.id = CanIfTxPdu.CanIfTxPduCanId;
      canPdu.length =(*CanIfTxInfoPtr).SduLength;
      canPdu.sdu = (*CanIfTxInfoPtr).SduDataPtr;
      canPdu.swPduHandle = CanIfTxPdu.CanIfTxPduId ;
   return E_OK; // can_write((*CanIfTxPdu).CanIfTxPduBufferRef->CanIfBufferHthRef,&canPdu);

  }
  else{
      return E_NOT_OK;
    }
}

boolean FindCanPduBySduId (PduIdType Id, CanIfTxPduCfg *CanIfPdu)
{
  CanIfTxPduCfg *CanIfConfigTxPdus = Configuration->InitConfig->CanIfTxPdusCfgs;
  uint8 CanIfConfigTxPdusNumber = Configuration->InitConfig->CanIfMaxTxPduCfg;
  
  for (int i = 0; i < CanIfConfigTxPdusNumber; i++)
  {
    if (Id == CanIfConfigTxPdus[i].CanIfTxPduId)
    {
      (*CanIfPdu) = CanIfConfigTxPdus[i];
      return TRUE;
    }
  }
  
  return FALSE;
}
