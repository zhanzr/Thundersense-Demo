/**************************************************************************//**
 * @file
 * @brief VCOM example for EFR32MG1
 * @version 4.3.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "retargetserial.h"
#include "bspconfig.h"


#if !defined(__CROSSWORKS_ARM) && defined(__GNUC__)
/* iprintf does not process floats, but takes less flash memory. */
#define printf iprintf
#endif

/** RS232 input buffer size */
#define ECHOBUFSIZE    80
/** RS232 Input buffer */
static char echoBuffer[ECHOBUFSIZE];

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_TBSENSE_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_TBSENSE_DEFAULT;
  int c;
  int index;

  /* Chip errata */
  CHIP_Init();

  /* Init DCDC regulator and HFXO with WSTK radio board specific parameters
     from bspconfig.h */
  EMU_DCDCInit(&dcdcInit);
  CMU_HFXOInit(&hfxoInit);

  /* Switch HFCLK to HFXO and disable HFRCO */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

  /* Initialize LEUART/USART and map LF to CRLF */
  RETARGET_SerialInit();
  RETARGET_SerialCrLf(1);

  printf("\nEFR32 VCOM example\n");

  for (index = 0; index < ECHOBUFSIZE; index++)
  {
    echoBuffer[index] = (char) 'a' + index;
  }

  /* Retrieve characters, print local echo and full line back */
  index = 0;
  while (1)
  {
    /* Retrieve new character */
    c = getchar();
    if (c > 0)
    {
      /* Output character - most terminals use CRLF */
      if (c == '\r')
      {
        echoBuffer[index] = '\0';
        /* Output entire line */
        printf("\n%s\n", echoBuffer);
        index = 0;
      }
      else
      {
        /* Filter non-printable characters */
        if ((c < ' ') || (c > '~'))
          continue;

        /* Enter into buffer */
        echoBuffer[index] = c;
        index++;
        if (index == ECHOBUFSIZE)
        {
          /* Flush buffer */
          index = 0;
        }
        /* Local echo */
        putchar(c);
      }
    }
  }
}
