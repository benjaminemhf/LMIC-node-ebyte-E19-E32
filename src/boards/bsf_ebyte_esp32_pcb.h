/*******************************************************************************
 * 
 *  File:           bsf_ebyte_esp32_pcb.h
 * 
 *  Function:       Board Support File for Ebyte E19/E32 LoRa module & ESP32 - custom PCB.
 * 
 *  Copyright:      Copyright (c) 2023 Benjamin Emirhafizovic
 * 
 *  License:        MIT License. See accompanying LICENSE file.
 * 
 *  Author:         Benjamin Emirhafizovic
 * 
 *                  Led                 GPIO 
 *                  ----                ----
 *                  LED   <――――――――――>  2
 *   
 *                  I2C/Display         GPIO
 *                  ---                 ---- 
 *                  SDA   <――――――――――>  26
 *                  SCL   <――――――――――>  25
 *                  RST   <――――――――――>  16    
 * 
 *                  UART/GPS            GPIO
 *                  ---                 ---- 
 *                  TX    <――――――――――>  21
 *                  RX    <――――――――――>  22 
 * 
 *                  SPI/LoRa            GPIO
 *                  ---                 ----
 *                  MOSI  <――――――――――>  23
 *                  MISO  <――――――――――>  19
 *                  SCK   <――――――――――>  18
 *                  NSS   <――――――――――>  5
 *                  RST   <――――――――――>  15
 *                  DIO0  <――――――――――>  27
 *                  DIO1  <――――――――――>  35
 *                  DIO2  <――――――――――>  34
 *                  RXEN  <――――――――――>  32
 *                  TXEN  <――――――――――>  33
 * 
 ******************************************************************************/

#pragma once

#ifndef BSF_EBYTE_ESP32_PCB_H_
#define BSF_EBYTE_ESP32_PCB_H_

#include "LMIC-node.h"

#define DEVICEID_DEFAULT "ebyte-esp32-pcb"   // Default deviceid value

// Wait for Serial
// Can be useful for boards with MCU with integrated USB support.
// #define WAITFOR_SERIAL_SECONDS_DEFAULT 10   // -1 waits indefinitely    

// Pin mappings for LoRa tranceiver
const lmic_pinmap lmic_pins = {
    .nss = 5,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 15,
    .dio = { /*dio0*/ 27, /*dio1*/ 35, /*dio2*/ 34 }
#ifdef MCCI_LMIC
    ,
    .rxtx_rx_active = 0,
    .rssi_cal = 10,
    .spi_freq = 8000000     /* 8 MHz */
#endif    
};

#ifdef USE_SERIAL
    HardwareSerial& serial = Serial;
#endif    

#ifdef USE_LED
    EasyLed led(2, EasyLed::ActiveLevel::High);
#endif

#ifdef USE_DISPLAY
    // Create U8x8 instance for SSD1306 OLED display using hardware I2C.
    U8X8_SSD1306_128X64_NONAME_HW_I2C display( /*rst*/ 16, /*scl*/ 25, /*sda*/ 26);
    // Alternative - software I2C (this also works):
    // U8X8_SSD1306_128X64_NONAME_SW_I2C display( /*scl*/ 25, /*sda*/ 26, /*rst*/ 16);
#endif


bool boardInit(InitType initType)
{
    // This function is used to perform board specific initializations.
    // Required as part of standard template.

    // InitType::Hardware        Must be called at start of setup() before anything else.
    // InitType::PostInitSerial  Must be called after initSerial() before other initializations.    

    bool success = true;
    switch (initType)
    {
        case InitType::Hardware:
            // Note: Serial port and display are not yet initialized and cannot be used use here.

            break;

        case InitType::PostInitSerial:
            // Note: If enabled Serial port and display are already initialized here.
            // No actions required for this board.
            break;       
    }
    return success;
}


#endif  // BSF_EBYTE_ESP32_PCB_H_