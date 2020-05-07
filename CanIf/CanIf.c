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
   return Can_Write(CanIfTxPdu.CanIfTxPduBufferRef->CanIfBufferHthRef[0].CanIfHthIdSymRef[0].CanHwType.Hoh,&canPdu);

  }
  else{
      return E_NOT_OK;
    }
}

boolean FindCanPduBySduId (PduIdType Id, CanIfTxPduCfg *CanIfPdu)
{
  CanIfTxPduCfg *CanIfConfigTxPdus = Configuration->InitConfig->CanIfTxPdusCfgs;
  uint8 CanIfConfigTxPdusNumber = Configuration->InitConfig->CanIfMaxTxPduCfg;
  int i = 0;
  for (i = 0; i < CanIfConfigTxPdusNumber; i++)
  {
    if (Id == CanIfConfigTxPdus[i].CanIfTxPduId)
    {
      (*CanIfPdu) = CanIfConfigTxPdus[i];
      return TRUE;
    }
  }
  
  return FALSE;
}
void CanIf_RxIndication(const Can_HwType* Mailbox,const PduInfoType* PduInfoPtr)
{
  CanIfTxPduCfg *CanIfConfigRxPdus = Configuration->InitConfig->CanIfRxPdusCfgs;
  uint8 CanIfConfigRxPdusNumber = Configuration->InitConfig->CanIfMaxRxPduCfg;
  uint8 CanId = Mailbox->CanId;
  int i = 0;
  for(i = 0; i < CanIfConfigRxPdusNumber; i++)
  {
  	if(CanId == CanIfConfigRxPdus[i].CanIfRxPduCanId)
  	{
  	  PduR_CanIfRxIndication(CanIfConfigRxPdus[i].CanIfRxPduId, PduInfoPtr);
  	}
  }
}

