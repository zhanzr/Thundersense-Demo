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
  uint8_t ledMask;

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

  /* Setup SysTick Timer for 1 msec interrupts  */
  UTIL_init();
  BOARD_init(); 

  ledMask = 1;
  BOARD_ledSet(ledMask);

  /* Infinite blink loop */
  while (1)
  {
    ledMask ^= 0x3;
    BOARD_ledSet(ledMask);
    UTIL_delay(100);
  }
}
