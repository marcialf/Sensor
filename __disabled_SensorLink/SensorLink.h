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

#ifndef SensorLink_h
#define SensorLink_h

#include <Arduino.h>
//#include "printf.h"

//Defines Address
#define CB_ADDRESS 0x01

#define YIELD yield();

// Messsage Type Code
const uint8_t CONFIG_MSG = 0x01;
const uint8_t TEST_CB_MSG = 0x02;
const uint8_t ALARM_MSG = 0x03;
const uint8_t DATA_MSG = 0x04;
const uint8_t COMMAND_MSG = 0x05;


/*********************************************************************
**                                                                  **
**                   SensorLink Class                               **
**                                                                  **
*********************************************************************/


class SensorLink
{
  public:
     SensorLink();

     uint32_t homeID;
     uint8_t nodeID;

     uint8_t cbID;
     uint8_t msgID;
     uint8_t msgCode;
	 
     bool snConfigure();
     //busca canal, configura velocidade envia end 0, recebe node ID e home ID

     bool cbConfigure();
     //ode ID e home ID, envia dados

     bool snSend(String& message, uint16_t messageLength);
     // envia para CB

     bool snReceive(String& message, uint16_t messageLength);
     // recebe da CB

     bool cbIncludeNode();
     // busca sensor e configura 

     bool cbRun(); 

	 virtual bool send(const char *subMsg, uint8_t subMsgLength);   // basic send primitive: one MTU
	 
	 virtual bool recv(char *subMsg, uint8_t subMsgLength);   // basic receive primitive: one MTU
	 
	 
};


/*********************************************************************
**                                                                  **
**                   nRF2400L01 Class                               **
**                                                                  **
*********************************************************************/
/*
 Uses RH24 Library from Stanley Seow
 https://github.com/stanleyseow/RF24
 */

//#include "nRF24L01.h"
#include "RF24.h"
//#include "RF24_config.h"

// Defines NRF24 parameters
#define NRF24_MTU 32
#define NRF24_SDU 29
#define NRF24_MAX_MTU_LEN 32
#define NRF24_MAX_SDU_LEN 29
#define FIRST_CHANNEL_NRF24 0   // 2400 MHz
#define CHANNEL_SPACE_NRF24 1   // 1 MHz
#define LAST_CHANNEL_NRF24 127   // 2525 MHz
#define MAX_CHANNEL_NRF24 128
#define TEST_CHANNEL_REP 100

// set NRF24 MTU and SDU
const uint8_t MTULength = NRF24_MTU;
const uint8_t SDULength = NRF24_SDU;

//Defines Length
const uint8_t maxMTULength = 16 * NRF24_MTU; 
const uint8_t maxSDULength = 16 * NRF24_SDU;

const uint8_t numChannel = MAX_CHANNEL_NRF24; 

const long txTimeoutInterval = 500;
const long rxTimeoutInterval = 500;

const uint64_t ctlAddr = '0x0000000000';

class SL_NRF24 : public SensorLink
{
  public:
     /// Constructor
     SL_NRF24(uint8_t chipEnablePin, uint8_t slaveSelectPin);

//	 uint8_t checkChannel[MAX_CHANNEL_NRF24];
	 
     uint8_t selectedChannel;       // communication channel
	 uint8_t dataRate; 
	 uint8_t powerLevel;

//	 uint64_t TXdataAddr;
//	 uint64_t RXdataAddr;
	 
 	 uint8_t TXdataAddr[5];
 	 uint8_t RXdataAddr[5];

	 bool configSN(uint8_t selectedChannel, uint8_t homeID[], uint8_t nodeID);
  	 bool configCB(uint8_t selectedChannel, uint8_t homeID[]);

	 //  bool write( const void* buf, uint8_t len );
	 bool send(const char *subMsg, uint8_t subMsgLength);   // basic send primitive: one MTU
	 bool recv(char *subMsg, uint8_t subMsgLength);   // basic receive primitive: one MTU

//	 bool send(const char** subMsg, uint8_t subMsgLength);   // basic send primitive: one MTU
//	 bool recv(char** subMsg, uint8_t subMsgLength);   // basic receive primitive: one MTU

	 void findChannel(uint8_t checkChannel[]);  // find free and active channels
     void printDetails();
	 
 private:
      RF24 radio;
  };

#endif









