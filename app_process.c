/***************************************************************************//**
 * @file app_tick.c
 * @brief app_tick.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "sl_component_catalog.h"
#include "sl_flex_assert.h"
#include "rail.h"
#include "app_process.h"
#include "env.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "os.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Size of RAIL RX/TX FIFO
#define RAIL_FIFO_SIZE (256u)
/// Transmit data length
#define TX_PAYLOAD_LENGTH (16u)


/// State machine of simple_trx
typedef enum {
  S_PACKET_RECEIVED,
  S_PACKET_SENT,
  S_RX_PACKET_ERROR,
  S_TX_PACKET_ERROR,
  S_CALIBRATION_ERROR,
  S_IDLE,
} state_t;

extern RAIL_Handle_t rail_handle;

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

static OS_TCB tcb;
static CPU_STK stack[RXTX_TASK_STACK_SIZE];

/* Input buffer */
//static char buffer[BUFSIZE];
// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * The function printfs the received rx message.
 *
 * @param rx_buffer Msg buffer
 * @returns None
 *****************************************************************************/
static void printf_rx_packet(const uint8_t * const rx_buffer);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// Flag, indicating transmit request (button has pressed / CLI transmit request has occured)
volatile bool tx_requested = false;
/// Flag, indicating received packet is forwarded on CLI or not
volatile bool rx_requested = true;

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// The variable shows the actual state of the state machine
static volatile state_t state = S_IDLE;

/// Contains the last RAIL Rx/Tx error events
static volatile uint64_t current_rail_err = 0;

/// Contains the status of RAIL Calibration
static volatile RAIL_Status_t calibration_status = 0;

/// RAIL Rx packet handle
static volatile RAIL_RxPacketHandle_t rx_packet_handle;

/// Receive FIFO
static uint8_t rx_fifo[RAIL_FIFO_SIZE];

/// Transmit FIFO
static uint8_t tx_fifo[RAIL_FIFO_SIZE] = {
  0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
  0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE,
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Application state machine, called infinitely
 *****************************************************************************/
void app_process_action(RAIL_Handle_t rail_handle)
{
  RAIL_RxPacketInfo_t packet_info;
  // Status indicator of the RAIL API calls
  RAIL_Status_t rail_status;
  // RAIL FIFO size allocated by RAIL_SetTxFifo() call
  uint16_t allocated_tx_fifo_size = 0;

  switch (state) {
    case S_PACKET_RECEIVED:
      // Packet received:
      //  - Check whether RAIL_HoldRxPacket() was successful, i.e. packet handle is valid
      //  - Copy it to the application FIFO
      //  - Free up the radio FIFO
      //  - Return to IDLE state i.e. RAIL Rx
      APP_WARNING(rx_packet_handle != RAIL_RX_PACKET_HANDLE_INVALID,
                  "RAIL_HoldRxPacket() error: RAIL_RX_PACKET_HANDLE_INVALID\n"
                  "No such RAIL rx packet yet exists or rail_handle is not active");
      rx_packet_handle = RAIL_GetRxPacketInfo(rail_handle, RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE, &packet_info);
      APP_WARNING(rx_packet_handle != RAIL_RX_PACKET_HANDLE_INVALID,
                  "RAIL_GetRxPacketInfo() error: RAIL_RX_PACKET_HANDLE_INVALID\n");
      RAIL_CopyRxPacket(rx_fifo, &packet_info);
      rail_status = RAIL_ReleaseRxPacket(rail_handle, rx_packet_handle);
      APP_WARNING(rail_status == RAIL_STATUS_NO_ERROR, "RAIL_ReleaseRxPacket() result:%d", rail_status);
      rail_status = RAIL_StartRx(rail_handle, CHANNEL, NULL);
      APP_WARNING(rail_status == RAIL_STATUS_NO_ERROR, "RAIL_StartRx() result:%d", rail_status);
      if (rx_requested) {
        printf_rx_packet(&rx_fifo[0]);
      }
      sl_led_toggle(&sl_led_led0);
      state = S_IDLE;
      break;
    case S_PACKET_SENT:
      APP_INFO("Packet has been sent\n");
#if defined(SL_CATALOG_LED1_PRESENT)
      sl_led_toggle(&sl_led_led1);
#else
      sl_led_toggle(&sl_led_led0);
#endif
      state = S_IDLE;
      break;
    case S_RX_PACKET_ERROR:
      // Handle Rx error
      APP_INFO("Radio RX Error occured\nEvents: %lld\n", current_rail_err);
      state = S_IDLE;
      break;
    case S_TX_PACKET_ERROR:
      // Handle Tx error
      APP_INFO("Radio TX Error occured\nEvents: %lld\n", current_rail_err);
      state = S_IDLE;
      break;
    case S_IDLE:
      if (tx_requested) {
        allocated_tx_fifo_size = RAIL_SetTxFifo(rail_handle, tx_fifo, TX_PAYLOAD_LENGTH, RAIL_FIFO_SIZE);
        APP_ASSERT(allocated_tx_fifo_size == RAIL_FIFO_SIZE,
                   "RAIL_SetTxFifo() failed to allocate a large enough fifo (%d bytes instead of %d bytes)\n",
                   allocated_tx_fifo_size,
                   RAIL_FIFO_SIZE);
        rail_status = RAIL_StartTx(rail_handle, CHANNEL, RAIL_TX_OPTIONS_DEFAULT, NULL);
        APP_WARNING(rail_status == RAIL_STATUS_NO_ERROR, "RAIL_StartTx() result:%d ", rail_status);
        printf("send a message\n");
        tx_requested = false;
      }
      break;
    case S_CALIBRATION_ERROR:
      APP_WARNING(true,
                  "Radio Calibration Error occured\nEvents: %lld\nRAIL_Calibrate() result:%d\n",
                  current_rail_err,
                  calibration_status);
      state = S_IDLE;
      break;
    default:
      // Unexpected state
      APP_INFO("Unexpected Simple TRX state occured:%d\n", state);
      break;
  }
}

/******************************************************************************
 * RAIL callback, called if a RAIL event occurs.
 *****************************************************************************/
void sl_rail_app_on_event(RAIL_Handle_t rail_handle, RAIL_Events_t events)
{
  // Handle Rx events
  if ( events & RAIL_EVENTS_RX_COMPLETION ) {
    if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
      // Keep the packet in the radio buffer, download it later at the state machine
      rx_packet_handle = RAIL_HoldRxPacket(rail_handle);
      state = S_PACKET_RECEIVED;
    } else {
      // Handle Rx error
      current_rail_err = (events & RAIL_EVENTS_RX_COMPLETION);
      state = S_RX_PACKET_ERROR;
    }
  }
  // Handle Tx events
  if ( events & RAIL_EVENTS_TX_COMPLETION) {
    if (events & RAIL_EVENT_TX_PACKET_SENT) {
      state = S_PACKET_SENT;
    } else {
      // Handle Tx error
      current_rail_err = (events & RAIL_EVENTS_TX_COMPLETION);
      if (current_rail_err & RAIL_EVENT_TX_UNDERFLOW  )
        printf("tranfer error %x\n",current_rail_err);
      state = S_TX_PACKET_ERROR;
    }
  }

  // Perform all calibrations when needed
  if ( events & RAIL_EVENT_CAL_NEEDED ) {
    calibration_status = RAIL_Calibrate(rail_handle, NULL, RAIL_CAL_ALL_PENDING);
    if (calibration_status != RAIL_STATUS_NO_ERROR) {
      current_rail_err = (events & RAIL_EVENT_CAL_NEEDED);
    }
  }
}

/******************************************************************************
 * Button callback, called if any button is pressed or released.
 *****************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    tx_requested = true;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * The API forwards the received rx packet on CLI
 *****************************************************************************/
static void printf_rx_packet(const uint8_t * const rx_buffer)
{
  uint8_t i = 0;
  APP_INFO("Packet has been received: ");
  for (i = 0; i < TX_PAYLOAD_LENGTH; i++) {
    APP_INFO("0x%02X, ", rx_buffer[i]);
  }
  APP_INFO("\n");
}

void rx_tx_process(void *arg)
{
  while(1) {

      app_process_action(rail_handle);

  }

}

void app_rx_tx_tast(void)
{
  RTOS_ERR err;

  // Create Blink Task
  OSTaskCreate(&tcb,
               "rx tx task",
               rx_tx_process,
               DEF_NULL,
               RXTX_TASK_PRIO,
               &stack[0],
               (RXTX_TASK_STACK_SIZE / 10u),
               RXTX_TASK_STACK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}
