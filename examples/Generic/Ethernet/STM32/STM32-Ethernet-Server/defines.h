/****************************************************************************************************************************
  defines.h for STM32-Ethernet-Server.ino
  For STM32 with Ethernet module/shield.
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support nRF52 and SAMD21/SAMD51 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
  Version: 1.0.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      14/07/2020 Initial coding/porting to support nRF52 and SAMD21/SAMD51 boards. Add SINRIC/Alexa support
  1.0.1   K Hoang      16/07/2020 Add support to Ethernet W5x00 to nRF52, SAMD21/SAMD51 and SAM DUE boards
  1.0.2   K Hoang      18/07/2020 Add support to Ethernet ENC28J60 to nRF52, SAMD21/SAMD51 and SAM DUE boards
  1.0.3   K Hoang      18/07/2020 Add support to STM32F boards using Ethernet W5x00, ENC28J60 and LAN8742A
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) )
  #if defined(WEBSOCKETS_ETHERNET_USE_STM32)
    #undef WEBSOCKETS_ETHERNET_USE_STM32
  #endif
  #define WEBSOCKETS_USE_ETHERNET             true
  #define WEBSOCKETS_ETHERNET_USE_STM32      true
#else
  #error This code is intended to run only on the STM32F boards ! Please check your Tools->Board setting.
#endif

#if defined(WEBSOCKETS_ETHERNET_USE_STM32)
  // For STM32
  #if defined(STM32F0)
    #define BOARD_TYPE  "STM32F0"
    #error Board STM32F0 not supported
  #elif defined(STM32L4)
    #define BOARD_TYPE  "STM32L4"
    #error Board STM32L4 not supported
  #elif defined(STM32F2)
    #define BOARD_TYPE  "STM32F2"
  #elif defined(STM32F3)
    #define BOARD_TYPE  "STM32F3"
  #elif defined(STM32F4)
    #define BOARD_TYPE  "STM32F4"
  #elif defined(STM32F7)
    #define BOARD_TYPE  "STM32F7"
  #else
    #warning STM32 unknown board selected
    #define BOARD_TYPE  "STM32 Unknown"
  #endif
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

// Just select one to be true. If all is false, default is Ethernet. 
// If more than one are true, the priority is USE_ETHERNET_LIB, USE_ETHERNET2_LIB, USE_ETHERNET_LARGE_LIB, USE_UIP_ETHERNET, USE_BUILTIN_ETHERNET

#define USE_ETHERNET_LIB              false
#define USE_ETHERNET2_LIB             false
#define USE_ETHERNET_LARGE_LIB        true

#define USE_UIP_ETHERNET              false
#define USE_LAN8742A_ETHERNET         false

#if USE_ETHERNET_LIB
  // Also default to Ethernet library
  #include <Ethernet.h>
  #define ETHERNET_TYPE               "W5x00 and Ethernet Library"
#elif USE_ETHERNET2_LIB
  #include <Ethernet2.h>
  #define ETHERNET_TYPE               "W5x00 and Ethernet2 Library"
#elif USE_ETHERNET_LARGE_LIB
  #include <EthernetLarge.h>
  #define ETHERNET_TYPE               "W5x00 and EthernetLarge Library"
#elif USE_UIP_ETHERNET
  #include <UIPEthernet.h>
  #include <utility/logging.h> 
  #define ETHERNET_TYPE               "ENC28J60 and UIPEthernet Library"
#elif USE_LAN8742A_ETHERNET
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  #define ETHERNET_TYPE               "LAN8742A and STM32Ethernet Library"  
#else
  // Default to Ethernet library
  #include <Ethernet.h>
  #define ETHERNET_TYPE               "W5x00 and Ethernet Library"
#endif

#define DEBUG_WEBSOCKETS_PORT     Serial
// Debug Level from 0 to 4
#define _WEBSOCKETS_LOGLEVEL_     3

uint8_t mac[6] =  { 0xDE, 0xAD, 0xBE, 0xEF, 0x32, 0x04 };

// Select the IP address according to your local network
IPAddress serverIP(192, 168, 2, 95);

#define SDCARD_CS       3

#endif      //defines_h
