/****************************************************************************************************************************
  ws_common_NativeEthernet.hpp
  For WebSockets2_Generic Library
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52, SAMD21/SAMD51, SAM DUE, Teensy, RP2040 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
  Version: 1.10.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      14/07/2020 Initial coding/porting to support nRF52 and SAMD21/SAMD51 boards. Add SINRIC/Alexa support
  ...
  1.9.0   K Hoang      30/11/2021 Auto detect ESP32 core version. Fix bug in examples
  1.9.1   K Hoang      17/12/2021 Fix QNEthernet TCP interface
  1.10.0  K Hoang      18/12/2021 Supporting case-insensitive headers, according to RFC2616
  1.10.1  K Hoang      26/02/2022 Reduce QNEthernet latency
 *****************************************************************************************************************************/
 
#pragma once

#include <Tiny_Websockets_Generic/ws_config_defs.hpp>
#include <string>
#include <Arduino.h>

namespace websockets2_generic
{
  typedef std::string WSString;
  typedef String WSInterfaceString;
  
  namespace internals2_generic
  {
    WSString fromInterfaceString(const WSInterfaceString& str);
    WSString fromInterfaceString(const WSInterfaceString&& str);
    WSInterfaceString fromInternalString(const WSString& str);
    WSInterfaceString fromInternalString(const WSString&& str);
  }   // namespace internals2_generic 
}     // namespace websockets 2_generic

  #if (defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) && USE_NATIVE_ETHERNET)
        
      // From v1.1.0  
      // Using Teensy 4.1 NativeEthernet
      #warning Using NativeEthernet for Teensy 4.1  in ws_common_NativeEthernet.hpp
      
      #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
      #define _WS_CONFIG_NO_SSL   true
      
      #include <Tiny_Websockets_Generic/network/Teensy41_NativeEthernet/Teensy41_NativeEthernet_tcp.hpp>

      #define WSDefaultTcpClient websockets2_generic::network2_generic::EthernetTcpClient
      #define WSDefaultTcpServer websockets2_generic::network2_generic::EthernetTcpServer
      
      #ifndef _WS_CONFIG_NO_SSL
      // OpenSSL Dependent
      #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredEthernetTcpClient
      #endif //_WS_CONFIG_NO_SSL
      
  #else
      #error This is designed only for Teensy 4.1. Please check your Tools-> Boards          
  #endif  
