/*******************************************************************

SensorLink - Data Link library for Sensor devices 

Copyright (C) 2014  Marcial P Fernandez <marcial@larces.uece.br>

This file is part of SensorLink.

SensorLink is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SensorLink is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SensorLink.  If not, see<http://www.gnu.org/licenses/>.

*********************************************************************/

#ifndef SL_NRF24_h
#define SL_NRF24_h

#include <Arduino.h>

//#include <SPI.h>

#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
//#include "printf.h"

#include "SensorLink.h"

// Defines
#define MAX_PAYLOAD_LEN 32
#define FIRST_CHANNEL 2400
#define CHANNEL_SPACE 1
#define LAST_CHANNEL 2525
#define MAX_CHANNEL 128

class SL_NRF24 : public SensorLink
{
  public:
     /// Constructor
    SL_NRF24(uint8_t chipEnablePin, uint8_t slaveSelectPin);

  	bool config();

	bool send();

	uint8_t findChannel();
	
	SensorLink(SL_NRF24& driver);
	SL_NRF24& _driver;

	virtual bool init();
	
	//   byte homeID[4];
 //   byte cbID;
  //  byte snID;

//	protect:
  private:
   // RF24 radio(uint8_t chipEnablePin, uint8_t slaveSelectPin);
   RF24 radio;
	
};
#endif 


















/////////////////////////////////////////////////////////////////////
/// Supported transceivers include:
/// - Nordic nRF24 based 2.4GHz radio modules, such as nRF24L01 http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01
/// and other compatible transceivers.
/// - Sparkfun WRL-00691 module with nRF24L01 https://www.sparkfun.com/products/691 
/// or WRL-00705 https://www.sparkfun.com/products/705 etc.
/// - Hope-RF RFM73 http://www.hoperf.com/rf/2.4g_module/RFM73.htm and 
/// http://www.anarduino.com/details.jsp?pid=121
/// and compatible devices (such as BK2423). nRF24L01 and RFM73 can interoperate
/// with each other.
///
/// The nRF24 transceiver is configured to use Enhanced Shockburst with acknowledgement and retransmits.
///
/// Naturally, for any 2 radios to communicate that must be configured to use the same frequency and 
/// data rate, and with identical network addresses.
///
/// The nRF24L01 (http://www.sparkfun.com/datasheets/Wireless/Nordic/nRF24L01P_Product_Specification_1_0.pdf)
/// is a low-cost 2.4GHz ISM transceiver module. It supports a number of channel frequencies in the 2.4GHz band
/// and a range of data rates.
///
/// This library provides functions for sending and receiving messages of up to 32 octets on any 
/// frequency supported by the nRF24L01, at a selected data rate.
///
/// Several nRF24L01 modules can be connected to an Arduino, permitting the construction of translators
/// and frequency changers, etc.
///
/// Example Arduino programs are included to show the main modes of use.
///
/// Connecting nRF24L01 to Arduino
///
/// The electrical connection between the nRF24L01 and the Arduino require 3.3V, the 3 x SPI pins (SCK, SDI, SDO), 
/// a Chip Enable pin and a Slave Select pin.
/// If you are using the Sparkfun WRL-00691 module, it has a voltage regulator on board and 
/// can be should with 5V VCC if possible.
/// The examples below assume the Sparkfun WRL-00691 module
///
/// Connect the nRF24L01 to most Arduino's like this (Caution, Arduino Mega has different pins for SPI, 
/// see below). Use these same connections for Teensy 3.1 (use 3.3V not 5V Vcc).
/// \code
///                 Arduino      Sparkfun WRL-00691
///                 5V-----------VCC   (3.3V to 7V in)
///             pin D8-----------CE    (chip enable in)
///          SS pin D10----------CSN   (chip select in)
///         SCK pin D13----------SCK   (SPI clock in)
///        MOSI pin D11----------SDI   (SPI Data in)
///        MISO pin D12----------SDO   (SPI data out)
///                              IRQ   (Interrupt output, not connected)
///                 GND----------GND   (ground in)
/// \endcode
///
/// For an Arduino Leonardo (the SPI pins do not come out on the Digital pins as for normal Arduino, but only
/// appear on the ICSP header)
/// \code
///                Leonardo      Sparkfun WRL-00691
///                 5V-----------VCC   (3.3V to 7V in)
///             pin D8-----------CE    (chip enable in)
///          SS pin D10----------CSN   (chip select in)
///      SCK ICSP pin 3----------SCK   (SPI clock in)
///     MOSI ICSP pin 4----------SDI   (SPI Data in)
///     MISO ICSP pin 1----------SDO   (SPI data out)
///                              IRQ   (Interrupt output, not connected)
///                 GND----------GND   (ground in)
/// \endcode
/// and initialise the NRF24 object like this to explicitly set the SS pin
/// NRF24 nrf24(8, 10);
///
/// For an Arduino Mega:
/// \code
///                 Mega         Sparkfun WRL-00691
///                 5V-----------VCC   (3.3V to 7V in)
///             pin D8-----------CE    (chip enable in)
///          SS pin D53----------CSN   (chip select in)
///         SCK pin D52----------SCK   (SPI clock in)
///        MOSI pin D51----------SDI   (SPI Data in)
///        MISO pin D50----------SDO   (SPI data out)
///                              IRQ   (Interrupt output, not connected)
///                 GND----------GND   (ground in)
/// \endcode
/// and you can then use the default constructor RH_NRF24(). 
///
/// For an Itead Studio IBoard Pro http://imall.iteadstudio.com/iboard-pro.html, connected by hardware SPI to the 
/// ITDB02 Parallel LCD Module Interface pins:
/// \code
///  IBoard Signal=ITDB02 pin          Sparkfun WRL-00691
///        3.3V      37-----------VCC  (3.3V to 7V in)
///         D2       28-----------CE   (chip enable in)
///         D29      27----------CSN   (chip select in)
///         SCK D52  32----------SCK   (SPI clock in)
///        MOSI D51  34----------SDI   (SPI Data in)
///        MISO D50  30----------SDO   (SPI data out)
///                              IRQ   (Interrupt output, not connected)
///        GND       39----------GND   (ground in)
/// \endcode
/// And initialise like this:
/// \code
/// RH_NRF24 nrf24(2, 29);
/// \endcode
///
/// For an Itead Studio IBoard Pro http://imall.iteadstudio.com/iboard-pro.html, connected by software SPI to the 
/// nRF24L01+ Module Interface pins. CAUTION: performance of software SPI is very slow and is not
/// compatible with other modules running hardware SPI.
/// \code
///  IBoard Signal=Module pin          Sparkfun WRL-00691
///        3.3V      2-----------VCC  (3.3V to 7V in)
///         D12      3-----------CE   (chip enable in)
///         D29      4----------CSN   (chip select in)
///         D9       5----------SCK   (SPI clock in)
///         D8       6----------SDI   (SPI Data in)
///         D7       7----------SDO   (SPI data out)
///                              IRQ   (Interrupt output, not connected)
///        GND       1----------GND   (ground in)
/// \endcode
///
/// It is possible to have 2 radios conected to one arduino, provided each radio has its own 
/// CSN and CE line (SCK, SDI and SDO are common to both radios)
///
/// \par Radio Performance
///
/// Frequency accuracy may be debatable. For nominal frequency of 2401.000 MHz (ie channel 1), 
/// my Yaesu VR-5000 receiver indicated the center frequency for my test radios
/// was 2401.121 MHz. Its not clear to me if the Yaesu
/// is the source of the error, but I tend to believe it, which would make the nRF24l01 frequency out by 121kHz.
/// 




















