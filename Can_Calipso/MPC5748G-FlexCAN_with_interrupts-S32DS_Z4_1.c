/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
/*******************************************************************************
* NXP Semiconductors
* (c) Copyright 2016 NXP Semiconductors
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without any
warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be held
liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED
TO THE PROJECT BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES.
IN NO EVENT SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THIS AGREEMENT.
CUSTOMER agrees to hold NXP harmless against any and all claims demands
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result
of the advise or assistance supplied CUSTOMER in connection with product,
services or goods supplied under this Agreement.
********************************************************************************
* File              MPC5748G-FlexCAN_with_interrupts-S32DS_Z4_1.c
* Owner             Martin Kovar
* Version           1.0
* Date              Aug-23-2016
* Classification    General Business Information
* Brief             Simple FlexCAN communication with interrupts
********************************************************************************
* Detailed Description:
* This example shows, how to initialize FlexCAN modules for simple transmission
* and reception using RX interrupt. Both modules are configured for 100kbit/s
* bit rate. CAN_0 module transmits message using MB0. CAN_1 module receives
* message using interrupt via MB0.
*
*
* ------------------------------------------------------------------------------
* Test HW:         MPC5748G-324DS, MPC574XG - Motherboard
* MCU:             PPC5748GMMN6A 1N81M
* Fsys:            PLL0 160MHz
* Debugger:        Lauterbach Trace32
*                  PeMicro USB-ML-PPCNEXUS
* Target:          internal_FLASH (debug mode, release mode)
* EVB connection:  Connect jumpers J15 and J16 on motherboard
* 				   Connect P14 H to P15 H
* 				   Connect P14 L to P15 L
*
********************************************************************************
Revision History:
Version  Date         Author  			Description of Changes
1.0      Aug-23-2016  Martin Kovar  	Initial version


*******************************************************************************/

#include "derivative.h" /* include peripheral declarations */
#include "Can_PBcfg.h"
#include "Can.h"
#include "Can_API.h"
#include "../Com/Com.h"
#include "../PduR/PduR.h"
#include "../CanIf/CanIf.h"


/*******************************************************************************
* Constants and macros
*******************************************************************************/

/*******************************************************************************
* Global variables
*******************************************************************************/
vuint32_t ReceiveBuffer[NO_OF_HRH][2];


/*******************************************************************************
* Function prototypes
*******************************************************************************/
extern void xcptn_xmpl(void);
//extern void hw_init(void);
//static void Sysclk_Init(void);
//static void GPIO_Init(void);
////static void FlexCAN_0_Init();
//static void FlexCAN_1_Init();
//static void Configure_RX_MessageBuffer(void);
//static void Transmit_Message();


/*******************************************************************************
* Local functions
*******************************************************************************/


/*******************************************************************************
Function Name : HW_Init
Engineer      : Martin Kovar
Date          : Jan-21-2016
Parameters    :
Modifies      :
Returns       :
Notes         : initialization of the hw for the purposes of this example
Issues        :
*******************************************************************************/
 void hw_init(void)
{
	xcptn_xmpl ();              /* Configure and Enable Interrupts */
	Sysclk_Init();
	GPIO_Init();
}


/*******************************************************************************
Function Name : Sysclk_Init
Engineer      : Lukas Zadrapa
Date          : Apr-20-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Clock settings - configure 160MHz system clock using
                40MHz crystal
Issues        : NONE
*******************************************************************************/
 void Sysclk_Init(void)
{
    /* enable all modes, enable all peripherals */
    MC_ME.ME.R        = 0x000005FF;
    MC_ME.RUN_PC[0].R = 0x000000FE;
    /* Connect XOSC to PLL */
    MC_CGM.AC5_SC.B.SELCTL = 1;
    /* Configure PLL0 Dividers - 160MHz from 40Mhx XOSC */
    PLLDIG.PLLDV.B.PREDIV  = 2;
    PLLDIG.PLLDV.B.MFD     = 32;
    PLLDIG.PLLDV.B.RFDPHI  = 1;
    PLLDIG.PLLCAL3.R       = 0x09C3C000;
    PLLDIG.PLLFD.B.SMDEN   = 1;       /* Sigma delta modulation disabled */
    /* switch to PLL */
    MC_ME.DRUN_MC.R  = 0x00130172;    /* FLASH in normal mode, PLLON, FXOSC ON, Use PLL_PHI_0 */

    MC_ME.MCTL.R     = 0x30005AF0;    /* DRUN target mode + KEY */
    MC_ME.MCTL.R     = 0x3000A50F;    /* DRUN target mode + KEY Inverted */

    while(MC_ME.GS.B.S_MTRANS == 1); /* Wait for mode transition complete */

    /* Enable CLKOUT signal */
    /* System clock (160MHz divided by 20 = 8MHz) will be visible on pin PG[7] */
    /* Pin PG[7] is configured in SIUL2_Init() function */
    MC_CGM.AC6_DC0.B.DE = 1;		/* Enable output clock devided */
    MC_CGM.AC6_DC0.B.DIV = 0x13;	/* Divide output clock by 20 */
    MC_CGM.AC6_SC.B.SELCTL = 0x2; 	/* PLL_CLKOUT1 */
}


/******************************************************************************
Function Name : SUIL2_Init
Engineer      : Martin Kovar
Date          : Feb-16-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : SIUL2 initialization (ports)
Issues        : NONE
******************************************************************************/
 void GPIO_Init(void)
{
	 SIUL2.MSCR[16].B.SSS = 1;    /* Pad PB0: Source signal is CAN0_TX */
	 SIUL2.MSCR[16].B.OBE = 1;    /* Pad PB0: Output Buffer Enable */
	 SIUL2.MSCR[16].B.SRC = 3;    /* Pad PB0: Maximum slew rate */

	 SIUL2.MSCR[17].B.IBE = 1;    /* Pad PB1: Enable pad for input - CAN0_RXD */
	 SIUL2.IMCR[188].B.SSS = 2;     /* CAN_0_RXD: connected to pad PB1 */

	 SIUL2.MSCR[42].B.SSS = 1;    /* Pad PC10: Source signal is CAN1_TX */
	 SIUL2.MSCR[42].B.OBE = 1;    /* Pad PC10: Output Buffer Enable */
	 SIUL2.MSCR[42].B.SRC = 3;    /* Pad PC10: Maximum slew rate */

	 SIUL2.MSCR[43].B.IBE = 1;    /* Pad PC11: Enable pad for input - CAN1_RXD */
	 SIUL2.IMCR[189].B.SSS = 3;     /* CAN1_RXD: connected to pad PC11 */
}


/******************************************************************************
Function Name : FlexCAN_0_Init
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN_0 basic initialization
Issues        : NONE
******************************************************************************/
// static void FlexCAN_0_Init()
// {
// 	int i = 0;

// 	/*Module enable*/
// 	CAN_0.MCR.B.MDIS = 0;

// 	while(CAN_0.MCR.B.SOFTRST == 1){};

// 	/*individual RX masking*/
// 	CAN_0.MCR.B.IRMQ = 1;
// 	/*Enable 64 message buffers*/
// 	CAN_0.MCR.B.MAXMB = 0x3F;

// 	/*Source clk is oscillator clock (40MHz)*/
// 	CAN_0.CTRL1.B.CLKSRC = 0;

// 	/*CAN bit timing - 40MHz oscillator, 100kbps bitrate,*/
// 	CAN_0.CTRL1.B.PRESDIV = 39;
// 	CAN_0.CTRL1.B.RJW = 3;
// 	CAN_0.CTRL1.B.PSEG1 = 3;
// 	CAN_0.CTRL1.B.PSEG2 = 3;
// 	CAN_0.CTRL1.B.PROPSEG = 0;


// 	/*Clear all RX individual Mask Registers The corresponding bit in the
// 	 * filter is "don't care."*/
// 	for(i = 0; i < 64; i++)
// 	{
// 		CAN_0.RXIMR[i].R = 0x00000000;
// 	}

//     /*Set all message buffers RX inactive*/
// 	for(i = 0; i <64; i++)
// 	{
// 		CAN_0.MB[i].CS.R = 0x0000;
// 	}

// 	/*No freeze mode request*/
// 	CAN_0.MCR.B.HALT = 0;

// }


/******************************************************************************
Function Name : FlexCAN_1_Init
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN_1 basic initialization
Issues        : NONE
******************************************************************************/
 void FlexCAN_1_Init()
{
	int i = 0;

	/*Module enable*/
	CAN_1.MCR.B.MDIS = 0;

	while(CAN_1.MCR.B.SOFTRST == 1){};


	/*individual RX masking*/
	// CAN_1.MCR.B.IRMQ = 1;
	/*Enable 64 message buffers*/
	CAN_1.MCR.B.MAXMB = NO_OF_HOH;

	/*Source clk is oscillator clock (40MHz)*/
	CAN_1.CTRL1.B.CLKSRC = 0;

	/*enable interrupt for MB0*/
	CAN_1.IMASK1.R = 0x00000001;

	/*CAN bit timing - 40MHz oscillator, 100kbps bitrate,*/
	CAN_1.CTRL1.B.PRESDIV = 4;
	CAN_1.CTRL1.B.RJW = CanConfiguration.CanConfigSetConfig->CanController[0].CanControllerDefaultBaudrate->CanControllerSyncJumpWidth;
	CAN_1.CTRL1.B.PSEG1 = CanConfiguration.CanConfigSetConfig->CanController[0].CanControllerDefaultBaudrate->CanControllerSeg1;
	CAN_1.CTRL1.B.PSEG2 =CanConfiguration.CanConfigSetConfig->CanController[0].CanControllerDefaultBaudrate->CanControllerSeg2;
	CAN_1.CTRL1.B.PROPSEG = CanConfiguration.CanConfigSetConfig->CanController[0].CanControllerDefaultBaudrate->CanControllerPropSeg;

	/*Clear all RX individual Mask Registers The corresponding bit in the
	 * filter is "don't care."*/
	// for(i = 0; i < 64; i++)
	// {
	// 	CAN_1.RXIMR[i].R = 0x00000000;
	// }

    /*Set all message buffers RX inactive*/
	for(i = 0; i <NO_OF_HOH; i++)
	{
		CAN_1.MB[CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanObjectId].CS.R = 0x0000;
	}

	/*No freeze mode request*/
	CAN_1.MCR.B.HALT = 0;

}


/******************************************************************************
Function Name : Configure_RX_MessageBuffer
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Configure FlexCAN_1 MB0. Message with any standard ID could be
  	  	  	  	received, because of RXIMR settings (all bits are do not care)
Issues        : NONE
******************************************************************************/
 void Configure_RX_MessageBuffer(void)
{
	int i =0;
	for(i=0;i<NO_OF_HRH;i++){
	CAN_1.MB[CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanObjectId].CS.B.CODE = 0x0;          	//MB inactive
	CAN_1.MB[CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanObjectId].CS.B.IDE =CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanIdType;				//receive STD ID
	CAN_1.MB[CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanObjectId].ID.R =CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanHwType.CanId;                   //set standard ID
	// CAN_1.MB[i].DATA.W[1] = 0x00000000;		//data1 set (optional)
	// CAN_1.MB[i].DATA.W[0] = 0x00000000;		//data0 set (optional)
	CAN_1.MB[CanConfiguration.CanConfigSetConfig->CanHardwareObject[i].CanObjectId].CS.B.CODE = 0x4;			//MB empty - ready for receive
	}
}


/******************************************************************************
Function Name : Transmit_Message
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Configure FlexCAN_0 MB0 for message transmission with STD ID = 0
				Message length is 8 bytes
Issues        : NONE
******************************************************************************/
 void Transmit_Message()
{
	CAN_0.MB[0].CS.B.CODE = 0x8;          //MB TX inactive
	CAN_0.MB[0].CS.B.IDE = 0;			  //send STD ID
	CAN_0.MB[0].ID.R = 0;	      		  //set STD ID to 0
	CAN_0.MB[0].DATA.W[1] = 0x90ABCDEF;	  //data1 set
	CAN_0.MB[0].DATA.W[0] = 0x12345678;	  //data0 set
	CAN_0.MB[0].CS.B.DLC = 8;			  //message length 8 bytes
	CAN_0.MB[0].CS.B.RTR = 0;			  //remote frame disable
	CAN_0.MB[0].CS.B.SRR = 0;			  //not used with STD_ID
	CAN_0.MB[0].CS.B.CODE = 0xC;		  //MB once transmit data
}


/******************************************************************************
Function Name : CAN_1_Receive_InterruptHandler
Engineer      : Martin Kovar
Date          : Feb-18-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Interrupt handler for CAN_1 MB0, clears interrupt flag, executes
				standard receive process according to reference manual
Issues        : NONE
******************************************************************************/
void CAN_1_Receive_InterruptHandler(void)
{
	uint32_t source = CAN_1.IFLAG1.R & 0xffffffff;
	/*Clear interrupt flag*/
	CAN_1.IFLAG1.R = source;


	uint32_t temp = 0;

	 /* mandatory - read control/status word - lock the MB */
	temp = CAN_1.MB[source].CS.R;
	/* check the ID field */
	/* not really needed in this example */
	/* useful in case when multiple IDs are received
	 * by one message buffer (Rx mask feature) */
	temp = CAN_1.MB[source].ID.R;


	/*Read the receive data*/
	ReceiveBuffer[source][0] = CAN_1.MB[source].DATA.W[0];
	ReceiveBuffer[source][1] = CAN_1.MB[source].DATA.W[1];

	/* release the internal lock for all Rx MBs
	 * by reading the TIMER */
	temp = CAN_1.TIMER.R;

}


__attribute__ ((section(".text")))
int main(void)
{
	int counter = 0;
//	INTC.PSR[580].R = 0x8001; //set interrupt core and priority
//
//	hw_init();
//	// FlexCAN_0_Init();
//	FlexCAN_1_Init();
//	Configure_RX_MessageBuffer();
//	Transmit_Message();
    Com_Init (&configuration);
    CanIf_Init(&CanIfConfiguration);
    Can_Init (&CanConfiguration);
    PduR_Init(&PduRConfig);
    Hardware_Init();

	for(;;) {	   
				uint8 Signal_Data = 5;
		        Com_SendSignal(0, &Signal_Data);
		        Com_MainFunctionTx();
	}
	
	return 0;
}
