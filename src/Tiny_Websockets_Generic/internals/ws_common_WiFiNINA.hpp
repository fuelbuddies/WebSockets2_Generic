/****************************************************************************************************************************
  ws_common_WIFININA.hpp
  For WebSockets2_Generic Library
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52, SAMD21/SAMD51, SAM DUE, Teensy, RP2040 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
  Version: 1.10.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      14/07/2020 Initial coding/porting to support nRF52 and SAMD21/SAMD51 boards. Add SINRIC/Alexa support
  ...
  1.9.0   K Hoang      30/11/2021 Auto detect ESP32 core version. Fix bug in examples
  1.9.1   K Hoang      17/12/2021 Fix QNEthernet TCP interface
  1.10.0  K Hoang      18/12/2021 Supporting case-insensitive headers, according to RFC2616
  1.10.1  K Hoang      26/02/2022 Reduce QNEthernet latency
  1.10.2  K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  1.10.3  K Hoang      11/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
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

#if WEBSOCKETS_USE_WIFININA
  #warning Using WIFININA in ws_common_WIFININA.hpp
#endif

  
#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
      
 
    // Using WiFiNINA   
    #warning Using WiFiNINA for SAMD in ws_common_WIFININA.hpp
      
    #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
    
    #include <Tiny_Websockets_Generic/network/SAMD_WiFiNINA/SAMD_WiFiNINA_tcp.hpp>
    #define WSDefaultTcpClient websockets2_generic::network2_generic::WiFiNINATcpClient
    #define WSDefaultTcpServer websockets2_generic::network2_generic::WiFiNINATcpServer
    
    #ifndef _WS_CONFIG_NO_SSL
    // OpenSSL Dependent
    #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredWiFiNINATcpClient
    #endif //_WS_CONFIG_NO_SSL   
  

#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
      defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
      defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
   
    // Using WiFiNINA
    #warning Using WiFiNINA for NRF52 in ws_common_WIFININA.hpp
    
    #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
    
    #include <Tiny_Websockets_Generic/network/nRF52_WiFiNINA/nRF52_WiFiNINA_tcp.hpp>
    #define WSDefaultTcpClient websockets2_generic::network2_generic::WiFiNINATcpClient
    #define WSDefaultTcpServer websockets2_generic::network2_generic::WiFiNINATcpServer
    
    #ifndef _WS_CONFIG_NO_SSL
    // OpenSSL Dependent
    #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredWiFiNINATcpClient
    #endif //_WS_CONFIG_NO_SSL  
        
    
#elif ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
    // From v1.0.1
  
    // Using WiFiNINA
    #warning Using WiFiNINA for SAM DUE in ws_common_WIFININA.hpp
    
    #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
    
    #include <Tiny_Websockets_Generic/network/DUE_WiFiNINA/DUE_WiFiNINA_tcp.hpp>
    #define WSDefaultTcpClient websockets2_generic::network2_generic::WiFiNINATcpClient
    #define WSDefaultTcpServer websockets2_generic::network2_generic::WiFiNINATcpServer
    
    #ifndef _WS_CONFIG_NO_SSL
    // OpenSSL Dependent
    #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredWiFiNINATcpClient
    #endif //_WS_CONFIG_NO_SSL
      
#elif ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
        defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
        defined(STM32WB) || defined(STM32MP1) )
    // From v1.0.4
  
    // Using WiFiNINA
    #warning Using WiFiNINA for STM32F/L/H/G/WB/MP1 in ws_common_WIFININA.hpp
    
    #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
    
    #include <Tiny_Websockets_Generic/network/STM32_WiFiNINA/STM32_WiFiNINA_tcp.hpp>
    #define WSDefaultTcpClient websockets2_generic::network2_generic::WiFiNINATcpClient
    #define WSDefaultTcpServer websockets2_generic::network2_generic::WiFiNINATcpServer
    
    #ifndef _WS_CONFIG_NO_SSL
    // OpenSSL Dependent
    #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredWiFiNINATcpClient
    #endif //_WS_CONFIG_NO_SSL        
        
#elif ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )      

    // Using WiFiNINA
    #warning Using WiFiNINA for RP2040 in ws_common_WIFININA.hpp
    
    #define PLATFORM_DOES_NOT_SUPPORT_BLOCKING_READ
    
    #include <Tiny_Websockets_Generic/network/RP2040_WiFiNINA/RP2040_WiFiNINA_tcp.hpp>
    #define WSDefaultTcpClient websockets2_generic::network2_generic::WiFiNINATcpClient
    #define WSDefaultTcpServer websockets2_generic::network2_generic::WiFiNINATcpServer
    
    #ifndef _WS_CONFIG_NO_SSL
    // OpenSSL Dependent
    #define WSDefaultSecuredTcpClient websockets2_generic::network2_generic::SecuredWiFiNINATcpClient
    #endif //_WS_CONFIG_NO_SSL           
#endif
