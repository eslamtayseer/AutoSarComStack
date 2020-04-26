#include "Com/Com.h"
#include "PduR/PduR.h"
#include "CanIf/CanIf.h"
#include "Can_Tiva/Can.h"

/**
 * main.c
 */

int main(void)
{
    Com_Init (&configuration);
    CanIf_Init(&CanIfConfiguration);
    Can_Init (&CanConfiguration);
	return 0;
}
