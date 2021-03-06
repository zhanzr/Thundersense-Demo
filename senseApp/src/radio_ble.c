#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "em_system.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_i2c.h"
#include "em_ldma.h"
#include "em_prs.h"
#include "em_rtcc.h"

#include "bsp/util.h"
#include "bsp/ccs811.h"
#include "bsp/si7021.h"
#include "bsp/si1133.h"
#include "bsp/bmp.h"
#include "bsp/board.h"
#include "bsp/imu/imu.h"
#include "bsp/mic.h"

#include "main.h"

#include "services/aio.h"
#include "services/imus.h"

/* BG stack headers */
/*#include "bg_types.h"*/
#include "native_gecko.h"
#include "gatt_db.h"

/* application specific files */
#include "app.h"

#include "app_ble_adv.h"
#include "radio.h"
#include "radio_ble.h"

/* Each iteration is 100 ms  */
#define APP_ADV_SLEEP_TIMEOUT_ITERATIONS           300

#define APP_STATE_UNKNOWN     0
#define APP_STATE_ADVERTISING 1
#define APP_STATE_CONNECTED   2

#define MAX_CONNECTIONS 4
uint8_t bluetooth_stack_heap[DEFAULT_BLUETOOTH_HEAP(MAX_CONNECTIONS)];


// Use this macro to check if Packet Trace Interface plugin is included
#define SILABS_AF_PLUGIN_PTI
// User options for plugin Packet Trace Interface
#define SILABS_AF_PLUGIN_PTI_BAUD 1600000
#define SILABS_AF_PLUGIN_PTI_D_OUT_LOC 6
#define GPIOPORTA 0
#define GPIOPORTB 1
#define GPIOPORTC 2
#define GPIOPORTD 3
#define GPIOPORTE 4
#define GPIOPORTF 5
#define GPIOPORTG 6
#define GPIOPORTH 7
#define SILABS_AF_PLUGIN_PTI_DOUT_PORT GPIOPORTB
#define SILABS_AF_PLUGIN_PTI_DOUT_PIN 12
#define SILABS_AF_PLUGIN_PTI_DFRAME_LOC 6
#define SILABS_AF_PLUGIN_PTI_DFRAME_PORT GPIOPORTB
#define SILABS_AF_PLUGIN_PTI_DFRAME_PIN 13



#ifdef SILABS_AF_PLUGIN_PTI
#include "pti.h"

static const RADIO_PTIInit_t ptiInit =
{
   RADIO_PTI_MODE_UART,
   SILABS_AF_PLUGIN_PTI_BAUD,
   SILABS_AF_PLUGIN_PTI_D_OUT_LOC,
   (GPIO_Port_TypeDef)SILABS_AF_PLUGIN_PTI_DOUT_PORT,
   SILABS_AF_PLUGIN_PTI_DOUT_PIN,
   /* SPI Data clock (DCLK) settings are not relevant for UART mode */
   0,(GPIO_Port_TypeDef)0,0,
   SILABS_AF_PLUGIN_PTI_DFRAME_LOC,
   (GPIO_Port_TypeDef)SILABS_AF_PLUGIN_PTI_DFRAME_PORT,
   SILABS_AF_PLUGIN_PTI_DFRAME_PIN
};
#endif /* SILABS_AF_PLUGIN_PTI */

#if defined SILABS_AF_PLUGIN_PTI || defined SILABS_AF_PLUGIN_IDLE_SLEEP
/* Gecko configuration parameters (see gecko_configuration.h) */
static gecko_configuration_t config =
{
   /* USARTs can be configured (see datasheet for signal location options */

   /* I2C can be configured (see datasheet for signal location options. flags field must be set to
      I2C_FLAGS_ENABLED to enable peripheral */

   /* GPIO default configuration can be set (see EFR Reference Manual)
      CTRL - Port Control Register
      MODEL - Port Pin Mode Low Register
      MODEH - Port Pin Mode High Register
      DOUT - Port Data Out Register */

   /* Power management (DC/DC regulator) can be configured, for initial setting see EFR Reference
    * Manual and em_emu.h file */

   /* High Frequency Oscillator and Low Frequency Oscillators  can be configured, for initial setting
    *  see Clock Management in reference manual and em_cmu.h file */

   /* Packet Trace Interface can be enabled by giving here the boards specific settings
    * or disabled by giving here NULL */
#ifdef SILABS_AF_PLUGIN_PTI
   .pti = &ptiInit,
#endif /* SILABS_AF_PLUGIN_PTI */

#ifdef SILABS_AF_PLUGIN_IDLE_SLEEP
   .sleep =
   {
      0, 0, 0
   }
#endif /* SILABS_AF_PLUGIN_IDLE_SLEEP */

};
#else /* !defined SILABS_AF_PLUGIN_PTI && !defined SILABS_AF_PLUGIN_IDLE_SLEEP */
static gecko_configuration_t config;
#endif /* defined SILABS_AF_PLUGIN_PTI || defined SILABS_AF_PLUGIN_IDLE_SLEEP */

uint16_t RADIO_eco2 = 0;
uint16_t RADIO_tvoc = 0;
uint32_t RADIO_rhData = 50000;
int32_t  RADIO_tempData = 25000;
uint8_t  RADIO_uvIndex = 0;
uint32_t RADIO_ambLight = 0;
float    RADIO_pressure = 0;

float    RADIO_soundLevel            = -60;
uint32_t RADIO_soundLevelBufferCount = 0;
float    RADIO_soundLevelAccumulated = 0;

EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
gecko_sleep_config_t sleepConfig;

static void advertisingIteration( uint32_t loopCount );
static void connectionActiveIteration( uint32_t loopCount );
static void mainEfr32StackInitCallback( void );
const void *RADIO_bleGetSleepConfig( void );

static int blinkCount;

void advBlink( void );

void RADIO_bleStackInit( void )
{

   blinkCount = 0;

   RADIO_bleChipInit();

   /* Perform initialisation of the stack. */
   mainEfr32StackInitCallback();

   return;

}

void RADIO_bleStackLoopIteration( void )
{

   static uint32_t loopCount = 0;
   static uint8_t appState = APP_STATE_UNKNOWN;
   bool imuIntIsActive = false;

   ++loopCount;

   if( IMU_isDataReadyFlag() ){
      IMU_clearDataReadyFlag();
      imuIntIsActive = true;
   }

   if( appBleAdvIsActive() ){
      if (appState != APP_STATE_ADVERTISING ){
         if( UTIL_isLowPower() ){
            MAIN_deInitSensors();
         }
         appState = APP_STATE_ADVERTISING;
      }

      advertisingIteration( loopCount );
   }
   else{
      if( appState != APP_STATE_CONNECTED ){
         if( UTIL_isLowPower() ){
            MAIN_initSensors();
         }
         appState = APP_STATE_CONNECTED;
         BOARD_ledSet( 0 );
      }
      connectionActiveIteration( loopCount );
   }

   RADIO_readImuData( imuIntIsActive );
}

void advertisingIteration( uint32_t loopCount )
{

   uint32_t sleepTimeout;
   static uint32_t previousAdvLC = 0;
   static uint32_t advStartedLC = 0;

   if( previousAdvLC + 1 != loopCount ){
     advStartedLC = loopCount;
   }
   previousAdvLC = loopCount;

   sleepTimeout = APP_ADV_SLEEP_TIMEOUT_ITERATIONS;

   advBlink();

#ifndef DEBUG
   if( (loopCount - advStartedLC) > sleepTimeout ){

     /* printf("\r\nSleep! %u %u", loopCount, advStartedLC); */
     if( !UTIL_isLowPower() ){
       MAIN_deInitSensors();
     }
     BOARD_picWriteReg( BOARD_PIC_REG_INT_CLEAR, 0 );
     BOARD_ledSet( 0x00 );
     UTIL_shutdown();
   }
#endif

   return;
}

#define RADIO_BLE_ADV_ON_COUNT  ( 1 )
#define RADIO_BLE_ADV_OFF_COUNT ( 10 )
void advBlink( void )
{

   int onCount = RADIO_BLE_ADV_ON_COUNT;
   int offCount = RADIO_BLE_ADV_OFF_COUNT;

   if( blinkCount == onCount ){
      BOARD_ledSet( 0x00 );
   }
   else if( blinkCount >= offCount || blinkCount == 0 ){
      BOARD_ledSet( 0x02 );
      blinkCount = 0;
   }
   blinkCount++;

   return;

}

void connectionActiveIteration( uint32_t loopCount )
{

   static bool expectAlsData = false;
   static uint8_t buttonState = 0;
   uint8_t irqStatus = 0;
   uint8_t state;
   float   lux = 0;
   float   uv = 0;
   float   micVar;

   blinkCount = 0;

   /* Check if the button state has changed */
   state = BOARD_pushButtonGetState();
   if( state != buttonState ){
      buttonState = state;
      aioDigitalInUpdate();
   }

   /* RH / T sensor read */
   if( (loopCount % 30) == 0 ){

      /* Measure the environmental temp and RH */
      /* If there is an error during the measurement use 25C and 50% RH */
      if( SI7021_measure( &RADIO_rhData, &RADIO_tempData ) != SI7021_OK )
      {
         RADIO_tempData = 25000;
         RADIO_rhData = 50000;
      }

      if( BMP_getPressure( &RADIO_pressure ) != BMP_OK) {
         RADIO_pressure = 0;
      }

      /* Perform CCS811 measurement if not gated by supply */
      if( UTIL_isLowPower() == false ){

         if( CCS811_isDataAvailable() ){
            CCS811_getMeasurement( &RADIO_eco2, &RADIO_tvoc );
            CCS811_setEnvData( RADIO_tempData, RADIO_rhData );
         }

      }

      /* Start an ALS measurement */
      SI1133_measurementForce();
      expectAlsData = true;

      printf("\r\n.");
   }

   if( expectAlsData ){
      /* Check if the conversion finished on all channels */
      SI1133_registerRead( SI1133_REG_IRQ_STATUS, &irqStatus );
      if (irqStatus == 0x0F) {
         expectAlsData = false;
         SI1133_getMeasurement( &lux, &uv );
         RADIO_ambLight = (uint32_t)(lux * 100);
         RADIO_uvIndex = (uint8_t)uv;
      }

   }

   if( !MIC_isBusy() ){

      MIC_getSoundLevel( &micVar );
      MIC_start( 512 );

      RADIO_soundLevelAccumulated += micVar;
      RADIO_soundLevelBufferCount++;

      RADIO_soundLevel = RADIO_soundLevelAccumulated / RADIO_soundLevelBufferCount;
      RADIO_soundLevel = 10.0f * log10f( RADIO_soundLevel );
      RADIO_soundLevel += 101.33f;
   }

   return;

}

void RADIO_readImuData( bool imuIntIsActive )
{
   if( IMU_isDataReadyFlag() ){
      IMU_clearDataReadyFlag();
      imuIntIsActive = true;
   }

   if( imuIsAccelerationNotification() || imuIsOrientationNotification() ){

      if( imuIntIsActive ){
         if( IMU_isDataReady() ){
            IMU_update();
         }
      }
   }
}

void RADIO_bleChipInit( void )
{

   CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;
   CMU_LFXOInit_TypeDef lfxoInit = CMU_LFXOINIT_DEFAULT;

   sleepConfig.pin  = 0;
   sleepConfig.port = 0;
   if( UTIL_isLowPower() == true ){
      printf("BLE stack sleep enabled!\r\n");
      sleepConfig.flags = SLEEP_FLAGS_DEEP_SLEEP_ENABLE;
   }
   else{
      sleepConfig.flags = 0;
   }

   /*************************************************************************/
   /* DC/DC */
   /*************************************************************************/
   dcdcInit.powerConfig = emuPowerConfig_DcdcToDvdd;
   dcdcInit.dcdcMode = emuDcdcMode_LowNoise;
   dcdcInit.mVout = 1800;
   dcdcInit.em01LoadCurrent_mA = 5;
   dcdcInit.em234LoadCurrent_uA = 10;
   dcdcInit.maxCurrent_mA = 160;
   dcdcInit.anaPeripheralPower = emuDcdcAnaPeripheralPower_AVDD;
   dcdcInit.reverseCurrentControl = emuDcdcLnFastTransient;

   EMU_DCDCInit(&dcdcInit);

   /*************************************************************************/
   /* HFXO */
   /*************************************************************************/
   hfxoInit.autoStartEm01 = 1;
   CMU_HFXOInit( &hfxoInit );

   SystemHFXOClockSet( 38400000 );
   CMU_ClockSelectSet( cmuClock_HF, cmuSelect_HFXO );
   CMU_OscillatorEnable( cmuOsc_HFRCO, false, false );
   CMU_ClockEnable( cmuClock_CORELE, true );

   /*************************************************************************/
   /* LFXO */
   /*************************************************************************/
   CMU_LFXOInit(&lfxoInit);

   CMU_OscillatorEnable( cmuOsc_LFXO, true, true );
   CMU_ClockSelectSet( cmuClock_LFE, cmuSelect_LFXO );

   CMU_ClockEnable( cmuClock_GPCRC, true );
   CMU_ClockEnable( cmuClock_LDMA,  true );
   CMU_ClockEnable( cmuClock_PRS,   true );
   CMU_ClockEnable( cmuClock_RTCC,  true );

   return;

}

const void *RADIO_bleChipGetDCDCConfig( void )
{
   return (const void *)&dcdcInit;
}

const void *RADIO_bleGetSleepConfig( void )
{
   return (const void *)&sleepConfig;
}

static void mainEfr32StackInitCallback( void )
{

   gecko_sleep_config_t *gsc;

   /* Put the SPI flash into Deep Power Down mode for those radio boards where it is available */
   BOARD_flashDeepPowerDown();

   config.dcdc  = RADIO_bleChipGetDCDCConfig();

   gsc          = (gecko_sleep_config_t *) RADIO_bleGetSleepConfig();
   config.sleep.flags = gsc->flags;
   config.sleep.pin   = gsc->pin;
   config.sleep.port  = gsc->port;

   config.gattdb=&bg_gattdb_data;
   config.bluetooth.max_connections=MAX_CONNECTIONS;
   config.bluetooth.heap=bluetooth_stack_heap;
   config.bluetooth.heap_size=sizeof(bluetooth_stack_heap);

   gecko_init(&config);

   return;

}
