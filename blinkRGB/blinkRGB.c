/**************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for EFR32MG1P
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

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bspconfig.h"
#include "bsp/board.h"
#include "bsp/util.h"


/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
   int i;

   EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_TBSENSE_DEFAULT;
   CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_TBSENSE_DEFAULT;

   /* Chip errata */
   CHIP_Init();

   /* Init DCDC regulator and HFXO with WSTK radio board specific parameters
      from bspconfig.h */
   EMU_DCDCInit(&dcdcInit);
   CMU_HFXOInit(&hfxoInit);

   /* Switch HFCLK to HFXO and disable HFRCO */
   CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
   CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

   /* Initialize board bsp */
   UTIL_init();
   BOARD_init();

   /* Enable RGB LEDs */
   BOARD_rgbledEnable(true, 0x04);

   /* Infinite blink loop */
   while (1)
   {
      for (i = 0; i < 128; i++)
      {
         BOARD_rgbledSetColor(i, 0, 127-i);
         UTIL_delay(5);
      }
      for (i = 0; i < 128; i++)
      {
         BOARD_rgbledSetColor(127-i, i, 0);
         UTIL_delay(5);
      }
      for (i = 0; i < 128; i++)
      {
         BOARD_rgbledSetColor(0, 127-i, i);
         UTIL_delay(5);
      }
   }
}
