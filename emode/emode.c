/**************************************************************************//**
 * @file
 * @brief Demo for energy mode current consumption testing.
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
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_pcnt.h"
#include "em_msc.h"
#include "em_prs.h"
#include "retargetserial.h"
#include "rtcdriver.h"
#include "bspconfig.h"

#include "bsp/util.h"
#include "bsp/board.h"

/* Number of energy mode tests. */
#define NO_OF_EMODE_TESTS     (7)
/* Number of prime numbers to crunch in EM0. */
#define PRIM_NUMS             (64)

static volatile int      eMode;          /* Selected energy mode.            */
static volatile bool     startTest;      /* Start selected energy mode test. */
static volatile bool     displayEnabled; /* Status of LCD display.           */
static volatile uint32_t seconds = 0;    /* Seconds elapsed since reset.     */
static RTCDRV_TimerID_t  rtcTimerId;     /* RTC timer used to generate 1 second interrupts */

static volatile int      blinkCount;
static RTCDRV_TimerID_t  blinkTimerId;   /* RTC timer used to blink LED to show energy mode */


static void gpioSetup(void);
static void rtcCallback(RTCDRV_TimerID_t id, void *user);
static void blinkCallback(RTCDRV_TimerID_t id, void *user);
static void selectClock(CMU_Select_TypeDef hfClockSelect,
                        uint32_t clockDisableMask);
static void enterEMode(int mode, uint32_t secs);

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  int currentEMode;

  /* Chip errata */
  CHIP_Init();

  EMU_EM4Init_TypeDef em4init = EMU_EM4INIT_DEFAULT;
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_TBSENSE_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_TBSENSE_DEFAULT;
  MSC_ExecConfig_TypeDef mscInit = MSC_EXECCONFIG_DEFAULT;

  /* Initialize HFXO and EM4 with kit specific parameters */
  EMU_EM4Init(&em4init);
  EMU_DCDCInit(&dcdcInit);
  CMU_HFXOInit(&hfxoInit);

  /* Initialize MSC - enable conditional branch target prefetch delay */
  MSC_Init();
  mscInit.scbtEn = true;
  MSC_ExecConfigSet(&mscInit);

  /* Setup board */
  UTIL_init();
  BOARD_init();

  /* Put SPI Flash into deep power down mode */
  BOARD_flashDeepPowerDown();

  /* Select ULFRCO as clock source for LFA */
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);

  /* Setup GPIO for pushbuttons. */
  gpioSetup();

  /* Initialize LEUART/USART and map LF to CRLF */
  RETARGET_SerialInit();
  RETARGET_SerialCrLf(0);

  /* Set RTCDRV to generate an interrupt every second. */
  RTCDRV_Init();
  RTCDRV_AllocateTimer(&rtcTimerId);
  RTCDRV_AllocateTimer(&blinkTimerId);
  RTCDRV_StartTimer(rtcTimerId, rtcdrvTimerTypePeriodic, 1000, rtcCallback, NULL);

  printf("\fPush the left button to cycle through the energy mode tests available\r\n\n");

  startTest    = false;
  eMode        = 0;
  currentEMode = -1;

  /* Disable LFB clock tree. */
  CMU->LFBCLKSEL &= ~(_CMU_LFBCLKSEL_LFB_MASK);

  while (1)
  {
    /* Mode change ? If yes, update the display. */
    if (eMode != currentEMode)
    {
      currentEMode = eMode;
      switch (eMode)
      {
        case 0:
          printf("\r   EM0 38.4MHz (primes calc)");
          break;

        case 1:
          printf("\r                            ");
          printf("\r   EM1 38.4MHz");
          break;

        case 2:
          printf("\r              ");
          printf("\r   EM2 32kHz");
          break;

        case 3:
          printf("\r            ");
          printf("\r   EM3");
          break;

        case 4:
          printf("\r      ");
          printf("\r   EM4");
          break;

        case 5:
          printf("\r      ");
          printf("\r   EM2+RTC");
          break;

        case 6:
          printf("\r          ");
          printf("\r   USER");
          break;
      }

      RTCDRV_StartTimer(blinkTimerId, rtcdrvTimerTypePeriodic, 250, blinkCallback, &currentEMode );
      blinkCount = 0;
    }

    if (startTest)
    {
      /* Get ready to start the energy mode test. Turn off everything we     */
      /* don't need. Use energyAware Profiler to observe energy consumption. */

      /* Disable GPIO. */
      NVIC_DisableIRQ(GPIO_EVEN_IRQn);
      NVIC_DisableIRQ(GPIO_ODD_IRQn);
      GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeDisabled, 0);
      GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeDisabled, 0);

      /* Stop SYSTICK timer */
      SysTick->CTRL = 0;

      printf("\r\n\nEntering energy mode!");

      /* Wait for last character to transmit to complete before entering sleep*/
      while (!(RETARGET_UART->STATUS & USART_STATUS_TXC))
        ;

      BOARD_ledSet(0);

      switch (eMode)
      {
        case 0:           /* EM0 38.4MHz (primes) */
        case 1:           /* EM1 38.4MHz */
        case 2:           /* EM2 32kHz */
        case 3:           /* EM3 */
        case 4:           /* EM4 */
          /* Power down LCD display and disable the RTC. */
          displayEnabled = false;
          NVIC_DisableIRQ(RTCC_IRQn);
          NVIC_DisableIRQ(PCNT0_IRQn);
          break;

        case 5:           /* EM2+RTC */
          /* Power down LCD display. */
          displayEnabled = false;
          break;

        case 6:           /* USER */
          break;
      }

      /* Do the slected energy mode test. */
      switch (eMode)
      {
        case 0:  /* EM0 38.4MHz (primes) */
          selectClock(cmuSelect_HFXO,               /* HF clock           */
                      CMU_OSCENCMD_HFRCODIS |       /* Clock disable mask */
                      CMU_OSCENCMD_LFXODIS  |
                      CMU_OSCENCMD_LFRCODIS);
          {
            uint32_t i, d, n;
            uint32_t primes[PRIM_NUMS];

            /* Find prime numbers forever */
            while (1)
            {
              primes[0] = 1;
              for (i = 1; i < PRIM_NUMS;)
              {
                for (n = primes[i - 1] + 1;; n++)
                {
                  for (d = 2; d <= n; d++)
                  {
                    if (n == d)
                    {
                      primes[i] = n;
                      goto nexti;
                    }
                    if (n % d == 0) break;
                  }
                }
              nexti:
                i++;
              }
            }
          }
          /*break;*/

        case 1:  /* EM1 38.4MHz */
          selectClock(cmuSelect_HFXO,               /* HF clock           */
                      CMU_OSCENCMD_HFRCODIS |       /* Clock disable mask */
                      CMU_OSCENCMD_LFXODIS  |
                      CMU_OSCENCMD_LFRCODIS );
          enterEMode(1, 1);
          break;

        case 2:  /* EM2 32kHz */
          selectClock(cmuSelect_LFRCO,              /* HF clock           */
                      CMU_OSCENCMD_HFXODIS  |       /* Clock disable mask */
                      CMU_OSCENCMD_HFRCODIS |
                      CMU_OSCENCMD_LFXODIS  );
          enterEMode(2, 1);
          break;

        case 3:  /* EM3 */
          enterEMode(3, 1);
          break;

        case 4:  /* EM4 */
          enterEMode(4, 1);
          break;

        case 5:  /* EM2+RTC */
          /* Wake up on each PCNT interrupt. */
          while (1)
          {
            enterEMode(2, 1);
            /* This loop will be visible in the Simplicity Profiler. */
            { volatile int i; for (i=0; i<10000; i++); }
          }
          /*break;*/

        case 6:           /* USER */
          for (;;);
          /*break;*/
      }

      /* We should never end up here ! */
      EFM_ASSERT(false);
    }
  }
}

/**************************************************************************//**
 * @brief   Enter and stay in Energy Mode for a given number of seconds.
 *
 * @param[in] mode  Energy Mode to enter (1..4).
 * @param[in] secs  Time to stay in Energy Mode <mode>.
 *****************************************************************************/
static void enterEMode(int mode, uint32_t secs)
{
  if (secs)
  {
    uint32_t startTime = seconds;

    while ((seconds - startTime) < secs)
    {
      switch (mode)
      {
        case 1: EMU_EnterEM1();       break;
        case 2: EMU_EnterEM2(false);  break;
        case 3: EMU_EnterEM3(false);  break;
        case 4: EMU_EnterEM4();       break;
      default:
        /* Invalid mode. */
        while (1);
      }
    }
  }
}

/**************************************************************************//**
* @brief Setup GPIO interrupt for pushbuttons.
*****************************************************************************/
static void gpioSetup(void)
{
  /* Enable gpio interrupt for push buttons */
  BOARD_pushButtonEnableIRQ(true);

  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);
}

/**************************************************************************//**
* @brief Unified GPIO Interrupt handler (pushbuttons)
*        PB0 Starts selected test
*        PB1 Cycles through the available tests
*****************************************************************************/
void GPIO_Unified_IRQ(void)
{
  /* Get and clear all pending GPIO interrupts */
  uint32_t interruptMask = GPIO_IntGet();
  GPIO_IntClear(interruptMask);

  /* Act on interrupts */
  if (interruptMask & (1 << BSP_GPIO_PB1_PIN))
  {
    /* SW2: Start test */
    startTest = true;
  }

  if (interruptMask & (1 << BSP_GPIO_PB0_PIN))
  {
    /* SW1: cycle through tests */
    eMode = (eMode + 1) % NO_OF_EMODE_TESTS;
  }
}

/**************************************************************************//**
* @brief GPIO Interrupt handler for even pins
*****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
    GPIO_Unified_IRQ();
}

/**************************************************************************//**
* @brief GPIO Interrupt handler for odd pins
*****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
    GPIO_Unified_IRQ();
}

/**************************************************************************//**
 * @brief   This interrupt is triggered at every second by the RTC
 *
 *****************************************************************************/
static void rtcCallback(RTCDRV_TimerID_t id, void *user)
{
  (void) id;
  (void) user;

  seconds++;
}


static void blinkCallback(RTCDRV_TimerID_t id, void *user)
{
  int blinkTarget;

  (void) id;

  blinkTarget = *((int *) user) * 2;  /* Number of on/off transitions */
  blinkTarget += 2;                   /* Blanking period */

  if (blinkCount > blinkTarget)
  {
    /* Number of blinks reached, stop timer and go back to green LED*/
    RTCDRV_StopTimer(blinkTimerId);
    BOARD_ledSet(2);
  }
  else if (blinkCount > 2)
  {
    /* Toggle red LED based on current count */
    BOARD_ledSet(blinkCount & 0x1);
  }
  else
  {
    /* Keep LED off in "blanking" period */
    BOARD_ledSet(0);
  }

  blinkCount++;
}


/**************************************************************************//**
 * @brief   Select a clock source for HF clock, optionally disable other clocks.
 *
 * @param[in] hfClockSelect      The HF clock to select.
 * @param[in] clockDisableMask   Bit masks with clocks to disable.
 *****************************************************************************/
static void selectClock(CMU_Select_TypeDef hfClockSelect,
                        uint32_t clockDisableMask)
{
  /* Select HF clock. */
  CMU_ClockSelectSet(cmuClock_HF, hfClockSelect);

  /* Disable unwanted clocks. */
  CMU->OSCENCMD     = clockDisableMask;

  /* Turn off clock enables. */
  CMU->HFPERCLKEN0  = 0x00000000;
  CMU->HFBUSCLKEN0  = 0x00000000;
  CMU->LFACLKEN0    = 0x00000000;
  CMU->LFBCLKEN0    = 0x00000000;
  CMU->LFACLKSEL    = 0x00000000;
  CMU->LFBCLKSEL    = 0x00000000;
  CMU->LFECLKSEL    = 0x00000000;
}
