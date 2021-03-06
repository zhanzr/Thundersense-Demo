// This file is generated by Ember Desktop.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __RAIL_CALLBACKS__
#define __RAIL_CALLBACKS__


#include <stdint.h>
#include "rail.h"
#include "rail_types.h"
#include CONFIGURATION_HEADER


/**
 * Callback that lets the app know when the radio has finished init
 * and is ready.
 */
void RAILCb_RfReady(void);

/**
 * Interrupt level callback to signify when the packet was sent
 * @param txPacketInfo Information about the packet that was transmitted.
 * @note that this structure is only valid during the timeframe of the
 * callback.
 */
void RAILCb_TxPacketSent(TxPacketInfo_t *txPacketInfo);

/**
 * Interrupt level callback
 * Allows the user finer granularity in tx radio events.
 *
 * Radio Statuses:
 * RAIL_TX_CONFIG_BUFFER_UNDERFLOW
 * RAIL_TX_CONFIG_CHANNEL_BUSY
 *
 * @param[in] status A bit field that defines what event caused the callback
 */
void RAILCb_TxRadioStatus(uint8_t status);

/**
 * Callback that fires whenever a packet was received
 *
 * @param[in] rxPacketInfo Contains the packet payload and any appended info for
 *   the packet
 */
void RAILCb_RxPacketReceived(RxPacketInfo_t *rxPacketInfo);

/**
 * Called whenever an enabled radio status event occurs
 *
 * Triggers:
 *  RAIL_RX_CONFIG_PREAMBLE_DETECT
 *  RAIL_RX_CONFIG_SYNC1_DETECT
 *  RAIL_RX_CONFIG_SYNC2_DETECT
 *  RAIL_RX_CONFIG_INVALID_CRC
 *  RAIL_RX_CONFIG_BUFFER_OVERFLOW
 *  RAIL_RX_CONFIG_ADDRESS_FILTERED
 *
 * @param[in] status The event that triggered this callback
 */
void RAILCb_RxRadioStatus(uint8_t status);

/**
 * Callback function which is called when the calibration process is complete
 *
 * @param[in] status Define the status of the radio calibration when it
 *   completes
 * @warning RAIL_CalibrateRadioComplete is NOT IMPLEMENTED
 */
void RAILCb_CalibrateRadioComplete(uint8_t status);

/**
 * Interrupt level callback to signify when the radio changes state.
 *
 * @param[in] state Current state of the radio, as defined by EFR32 data sheet
 * TODO: Unify these states with the RAIL_RadioState_t type? (There are much
 *    more than just TX, RX, and IDLE)
 */
void RAILCb_RadioStateChanged(uint8_t state);

/**
 * Callback function used by RAIL to request memory.
 *
 * @param[in] size The amount of memory in bytes that we need for this packet
 * @return A pointer to a block of memory at least size bytes in length.
 *
 * This is used to allocate memory for receive packets and must be implemented
 * by the application. If you return NULL it will be assumed that there is no
 * space available and any waiting packets will be dropped.
 */
void * RAILCb_AllocateMemory(uint32_t size);

/**
 * Callback function used by RAIL to free memory.
 *
 * @param[in] ptr A pointer to the memory block we're done with. This will
 *   correspond exactly with a value returned from RAILCb_AllocateMemory().
 *
 * This is used to free memory that was allocated with the
 * RAILCb_AllocateMemory() function when RAIL is done using it.
 */
void RAILCb_FreeMemory(void *ptr);

/**
 * This function is called when the RAIL timer expires
 *
 * You must implement a stub for this in your RAIL application even if you
 * don't use the timer.
 */
void RAILCb_TimerExpired(void);

#endif // __RAIL_CALLBACKS__
