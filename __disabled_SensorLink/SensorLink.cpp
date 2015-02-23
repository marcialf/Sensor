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
along with SensorLink.  If not, see <http://www.gnu.org/licenses/>.

*********************************************************************/


/*	 
long n;
byte buf[4];  	 

buf[0] = (byte) n;
buf[1] = (byte) n >> 8;
buf[2] = (byte) n >> 16;
buf[3] = (byte) n >> 24;

long value = (unsigned long)(buf[4] << 24) | (buf[3] << 16) | (buf[2] << 8) | buf[1];
*/




#include <Arduino.h>
#include "SensorLink.h"

//String message;
uint8_t sequence = 0;

/*******************************************************************************
***                                                                          ***
***                                SensorLink                                ***
***                                                                          ***
*******************************************************************************/

// Constructor /////////////////////////////////////////////////////////////////

SensorLink::SensorLink() 
{
}

//SensorLink::~SensorLink() 
//{
//}

// Public Methods //////////////////////////////////////////////////////////////

bool SensorLink::snConfigure()
{
//busca canal, envia end 0, recebe node ID e home ID, envia dados

   int tokenPosition;
   int tokenRegister;
   int tokenField;
   
  // channel = .findChannel();  // set avaiable channel
   //send (end 0, configure)
   //waitmsg(end 0, buf)
//   tokenRegister = message.indexOf(';');
   while(tokenPosition != -1)
   {
 //    String submessage;
	  
 //    submessage = message.substring(0, tokenPosition);
//	 tokenField = submessage.indexOf('|');
	   
//	 message= message.substring(tokenPosition+1, message.length());
//	 tokenPosition = message.indexOf(';');
   }
   

   //cbAddress
   //snAddress
   
   return true;
}

// envia para CB
bool SensorLink::snSend(String& message, uint16_t messageLength)
{
 //    String subMsg;
	 
	 uint8_t blockNumber;
     uint8_t fragCtrl;
 	 uint8_t msgID = 0;
	 uint8_t stringPointer = 0;
     long timeOut = millis() + txTimeoutInterval;
 
	 Serial.println(F("Sendind messagem snSend"));
	 
	 if (messageLength>maxSDULength)
	 {
         Serial.println(F("SensorLink ERROR: snSend message length overflow"));
         return false;
	 }

	 if (messageLength < SDULength)  // message less SDU, send only one short message
	 {
         Serial.println(F("SensorLink snSend: sending short message"));
         Serial.print(F("subMsg sent: "));
  //       Serial.println(message); 
 //	     return send(message, messageLength);
	 }
	 
	 // Message length between SDU and maxMessageLength
     if ((messageLength % SDULength) == 0)    // messageLength exactally divided by SDU
	 {
	     blockNumber = messageLength/SDULength;
	 }
	 else
	 {
	     blockNumber = int(messageLength/SDULength)+1; // increment one packet
	 }
     
	 Serial.print(F("Informacoes da mensagem: blockNumber ="));
	 Serial.println(blockNumber);
	 
	 for (uint8_t i=blockNumber; i=0; i--)
	 {
	     fragCtrl = msgID << 4 + blockNumber;
//		 subMsg = nodeID + DATA_MSG + fragCtrl + message.substring(stringPointer, stringPointer+SDULength);
         Serial.print(F("subMsg sent: "));
//		 Serial.println(subMsg); 
//		 if(!send(subMsg, subMsg.length()) || millis() > timeOut)
//         {
             Serial.println(F("SensorLink ERROR: snSend send error"));
		     return false;
 //        }		 

		 Serial.println(F("subMsg sent:"));
         Serial.print(F("nodeID: "));
     	 Serial.print(nodeID);
         Serial.print(F(" msgCode: "));
         Serial.print(msgCode);
         Serial.print(F(" msgID: "));
         Serial.print(msgID);
	     Serial.print(F(" blockNumber: "));
         Serial.println(blockNumber);
		 Serial.print(F("Message: "));
//		 Serial.println(message.substring(stringPointer, stringPointer+SDULength));

         stringPointer += SDULength;
		 blockNumber++;
		 timeOut = millis() + txTimeoutInterval;
	 }	
     Serial.println(F("SensorLink snSend OK"));
     return true;   // snSend message sent OK
}

bool SensorLink::snReceive(String& message, uint16_t messageLength)
{
// recebe da CB
//     String subMsg;
	 
	 uint8_t blockNumber;
     uint8_t fragCtrl;
 	 uint8_t msgID = 0;
	 uint8_t stringPointer = 0;
     long timeOut = millis() + rxTimeoutInterval;
 
	 Serial.println(F("Receiving messagem snReceive"));
	
      while (blockNumber>0)
	 {
    	 for (uint8_t i=blockNumber; i=0; i--)
	     {
	         fragCtrl = msgID << 4 + blockNumber;
//		     subMsg = nodeID + msgCode + fragCtrl + message.substring(stringPointer, stringPointer+SDULength);

             Serial.println(F("subMsg sent:"));
             Serial.print(F("nodeID: "));
			 Serial.print(nodeID);
             Serial.print(F(" msgCode: "));
             Serial.print(msgCode);
             Serial.print(F(" msgID: "));
             Serial.print(msgID);
			 Serial.print(F(" blockNumber: "));
             Serial.println(blockNumber);
			 Serial.print(F("Message: "));
//		     Serial.println(message.substring(stringPointer, stringPointer+SDULength));
			 
//		     if(!recv(subMsg, subMsg.length()) || millis() > timeOut)
//            {
                 Serial.println(F("SensorLink ERROR: snSend send error"));
//		         return false;
 //            }		 
             stringPointer += SDULength;
		     blockNumber++;
		     timeOut = millis() + txTimeoutInterval;
	    }	
         Serial.println(F("SensorLink snSend OK"));
	     return true;   // snSend message sent OK
	 }
}

bool SensorLink::cbIncludeNode()
{
// busca sensor e configura 
	return true;
}

bool SensorLink::cbRun()
{
   Serial.println(F("Return cbRun"));
	return true;
}  

/*******************************************************************************
***                                                                          ***
***                                  SL_NRF24                                ***
***                                                                          ***
*******************************************************************************/

SL_NRF24::SL_NRF24(uint8_t chipEnablePin, uint8_t chipSelectPin)
  : radio(chipEnablePin, chipSelectPin)
{
} 

//SL_NRF24::~SL_NRF24()
//{
//}

bool SL_NRF24::configSN(uint8_t _selectedChannel, uint8_t _homeID[], uint8_t _nodeID )
{
     Serial.println(F("Iniciando SL_NRF24 configSN"));

     // setting TX address
	 for (int i=0;i<=3;i++){TXdataAddr[i]=_homeID[i];} 
	 TXdataAddr[4]=byte(1);

	 // setting RX address
	 for (int i=0;i<=3;i++){RXdataAddr[i]=_homeID[i];} 
	 RXdataAddr[4]=_nodeID;


	 Serial.print(F("configSN channel = "));
	 Serial.println(_selectedChannel);
	 Serial.print(F("configSN homeId = "));
	 for (int i=0;i<=3;i++){Serial.print(_homeID[i],DEC);} Serial.println();
	 Serial.print(F("configSN nodeId = "));
	 Serial.println(_nodeID);
	 Serial.print(F("configSN writingPipe TX = "));
	 for (int i=0;i<=4;i++){Serial.print(TXdataAddr[i],DEC);} Serial.println();
	 Serial.print(F("configSN readingPipe RX = "));
	 for (int i=0;i<=4;i++){Serial.print(RXdataAddr[i],DEC);} Serial.println();

	 
//     msgID = 0;
     radio.begin();
     radio.setAutoAck(1);             // AutoACK is enabled
     radio.enableAckPayload();        // Allow optional ack payloads
     radio.setRetries(2,15);          // Time between retries, max no. of retries
     radio.setChannel(_selectedChannel); // Programming selected channel
     radio.enableDynamicPayloads();      // enable dynamic payload length
     radio.setCRCLength(RF24_CRC_16);	 // Sete CRC length to 16 bits
     radio.setDataRate(RF24_1MBPS);     // Max 2 mbps data rate 
     radio.setPALevel(RF24_PA_HIGH);    // Max power
     radio.openWritingPipe(TXdataAddr);   // Open the default reading and writing pipe
     radio.openReadingPipe(1,RXdataAddr); 
     radio.startListening();                 // Start listening
 //    radio.powerUp();
 
     Serial.print(F("Data rate config SN "));
     Serial.println(radio.getDataRate());
     Serial.print(F("CRC length config SN "));
     Serial.println(radio.getCRCLength());
     Serial.print(F("PA level config SN "));
     Serial.println(radio.getPALevel());
    if (radio.isPVariant())
         Serial.println(F("Config SN : Hardware is nRF24L01+"));
     else
         Serial.println(F("Config SN : Hardware is NOT nRF24L01+"));

      return true;
}


bool SL_NRF24::configCB(uint8_t selectedChannel, uint8_t _homeID[])
{
     Serial.println(F("Iniciando SL_NRF24 config CB"));

	 for (int i=0;i<=3;i++){RXdataAddr[i]=_homeID[i];} 
	 RXdataAddr[4]=byte(1);

	 for (int i=0;i<=3;i++){TXdataAddr[i]=_homeID[i];} 
	 TXdataAddr[4]=byte(5);

	 
	 Serial.print(F("configCB channel = "));
	 Serial.println(selectedChannel);
	 Serial.print(F("configCB homeId = "));
	 for (int i=0;i<=3;i++){Serial.print(_homeID[i],DEC);} Serial.println();
	 Serial.print(F("configCB readingPipe = "));
	 for (int i=0;i<=4;i++){Serial.print(RXdataAddr[i],DEC);} Serial.println();
	 Serial.print(F("configCB writingPipe = "));
	 for (int i=0;i<=4;i++){Serial.print(TXdataAddr[i],DEC);} Serial.println();

	 
 //    msgID = 0;
     radio.begin();
     radio.setAutoAck(1);             // AutoACK is enabled
     radio.enableAckPayload();        // Allow optional ack payloads
     radio.setRetries(2,15);          // Time between retries, max no. of retries
     radio.setChannel(selectedChannel); // Programming selected channel
     radio.enableDynamicPayloads();      // enable dynamic payload length
     radio.setCRCLength(RF24_CRC_16);	 // Sete CRC length to 16 bits
     radio.setDataRate(RF24_1MBPS);     // Max data rate 
     radio.setPALevel(RF24_PA_HIGH);    // Max power

     radio.openWritingPipe(TXdataAddr);   // Open the default writing pipe
     radio.openReadingPipe(1,RXdataAddr); // Open data reading pipe        
//   radio.openReadingPipe(0,ctlAddr);     // Open config reading pipe 
     radio.startListening();  // Start listening
     radio.powerUp();
	 
     Serial.print(F("Data rate config CB "));
     Serial.println(radio.getDataRate());
     Serial.print(F("CRC length config CB "));
     Serial.println(radio.getCRCLength());
     Serial.print(F("PA level config CB "));
     Serial.println(radio.getPALevel());
     if (radio.isPVariant())
         Serial.println(F("Config CB : Hardware is nRF24L01+"));
     else
         Serial.println(F("Config CB : Hardware is NOT nRF24L01+ "));
 
     return true;
}


void SL_NRF24::findChannel(uint8_t checkChannel[])
{
     // Clear measurement vector
     memset(checkChannel,0,sizeof(checkChannel));

     // How many times check each channels?
     uint8_t testChannel = TEST_CHANNEL_REP;

     Serial.println(F("Find Channel SL_NRF24")); 
     radio.begin();
     radio.setAutoAck(false);
 
     // Get into standby mode
     radio.startListening();
     radio.stopListening();

     while (testChannel--)
    {
         for (uint8_t i=FIRST_CHANNEL_NRF24; i<=LAST_CHANNEL_NRF24; i+=CHANNEL_SPACE_NRF24)
	     {
              // Configure radio channel
   	         radio.setChannel(i);

             // Listen for a little
             radio.startListening();
             delayMicroseconds(225);
             
             // Did we get a carrier?
             if (radio.testCarrier())
	         {
                 ++checkChannel[i];
                 Serial.print(F("Find Active Channel SL_NRF24: "));
   		         Serial.println(i);
		     }
             radio.stopListening();
          }
	 }
}


//bool RF24::write( const void* buf, uint8_t len ){
//bool SL_NRF24::send(const char** subMsg, uint8_t subMsgLength)

bool SL_NRF24::send(const char *subMsg, uint8_t subMsgLength)
{

     Serial.println(F("SL_NRF24 entering send method "));
     Serial.print(F("Sendind data address homeID + nodeID: "));
	 Serial.print(F("SL_NRF24 send() to TX address = "));
	 for (int i=0;i<=4;i++){Serial.print(TXdataAddr[i],DEC);} Serial.println();
     Serial.print(F("SL_NRF24 send(): subMsg received by INO: "));
//     for (int i = 0; i < subMsgLength; i++){
// 	     Serial.print(subMsg[i]);
 //    }
//	 Serial.println();
     Serial.println(subMsg); 
 
     for (int i = 0; i < subMsgLength; i++){
	     Serial.print(byte(subMsg[i]),DEC);
     }
     Serial.println();
	 
 	 radio.stopListening();         // stop listening so we can talk   
 
//	 if(subMsgLength> MTULength)
//	 {
 //        Serial.println(F("SL_NRF24 send ERROR: msg length error MTU too big"));
 //        return false;
//	 }
	
/* 	 if(!radio.write(&tag,sizeof(int)))
     {   
         Serial.println(F("ERROR SL_NRF24 send(): number msg send error"));
 	     return false;       // Indicate failure
      }
    
    Serial.print(F("SL_NRF24 send(): number send OK : "));
	Serial.println(tag,DEC);
	
    delay(1000);
*/
//	 if(!radio.write((char *)&subMsg,subMsgLength))
 	 if(!radio.write(&subMsg,subMsgLength))
    {   
         Serial.println(F("ERROR SL_NRF24 send(): msg send error"));
 	     return false;       // Indicate failure
     }

	 delay(500);
     radio.startListening();  // Start listening
     Serial.print(F("SL_NRF24 send(): msg sent OK : "));
	 Serial.println(subMsg);
     Serial.print(F("SL_NRF24 send(): msg width : "));
	 Serial.println(subMsgLength,DEC);

     return true;		 
}




//read( void* buf, uint8_t len )
//   uint8_t* current = reinterpret_cast<uint8_t*>(buf);
//	 bool SL_NRF24::recv(char* subMsg[], uint8_t subMsgLength) 
//	 bool SL_NRF24::recv(char** subMsg, uint8_t subMsgLength) 
   
   
   
bool SL_NRF24::recv(char *subMsg, uint8_t subMsgLength) 
{
     char msg[32];
 
 //    radio.startListening();
     for (int i = 0; i < 32; i++){
  	     msg[i]=' ';
	 }
     msg[32]='\0';
	 
	 Serial.println(F("Receiving message SL_NRF24 recv()"));
     Serial.println(F("SL_NRF24 recv entering receive method "));
	 Serial.print(F("SL_NRF24 recv(): RX address = "));
	 for (int i=0;i<=4;i++){Serial.print(RXdataAddr[i],DEC);}
	 Serial.println();

	 Serial.print(F("Buffer de recepcao : "));
     for (int i = 0; i < 32; i++){
	     Serial.print(msg[i]);
     }
	 Serial.println();
	 
	 
//     radio.openReadingPipe(1,RXdataAddr); // Open data reading pipe      
//     radio.startListening();  // Start listening
 
/*	 Serial.println(F("SL_NRF24 recv(): Receiving number.... "));
 
     if (radio.available())    // check if is there any message in buffer
     {
         // Fetch the payload, and see if this was the last one.
         radio.read(&tag,sizeof(int));
  		 Serial.print(F("NRF24 recv(): Number received : "));
		 Serial.println(tag,DEC);
 	 }
	else
  	{
	     Serial.println(F("ERROR SL_NRF24 recv(): No number msg yet!!!"));
		 return false;              // Indicate no msg
 	}
	 
	 delay(1000);
*/
	 
 	 Serial.println(F("SL_NRF24 recv(): Receiving text.... "));
 
    if (radio.available())    // check if is there any message in buffer
     {
         // Fetch the payload, and see if this was the last one.
         subMsgLength = radio.getDynamicPayloadSize();

  		 Serial.print(F("SL_NRF24 recv(): Message com tamanho : "));
 		 Serial.println(subMsgLength,DEC);

 //        radio.read((char *)&msg,subMsgLength);
         radio.read(&msg,sizeof(msg));
		 Serial.println(msg);

		 //		 delay(3000);
 //  		 Serial.println(F("NRF24 recv: Terminou de ler : "));
//		 msg[subMsgLength]='\0';
//		 Serial.println(subMsgLength,DEC);
         for (int i = 0; i < subMsgLength; i++){
  		     Serial.print(msg[i],DEC);
	     }
		 Serial.println();
         printf("[Reading %u bytes: %s ]",subMsgLength, msg);
//        for (int i = 0; i < subMsgLength; i++){
//  		     msg[i]=' ';
//	     }
		 return true;
    }
	else
  	{
	     Serial.println(F("ERROR SL_NRF24 recv(): No text msg yet!!!"));
		 return false;              // Indicate no msg
 	}
	
}

void SL_NRF24::printDetails()
{
     radio.printDetails();
}	
