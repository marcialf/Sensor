#ifndef MyConfig_h
#define MyConfig_h

/****
* Define the Radio hardware used (only one)
*/
#define NRF24
//#define NRF905

/***
 * nRF2401 Configuration
 */
#define RF24_CHANNEL	   76             //RF channel for the sensor net, 0-127
#define RF24_DATARATE 	   RF24_250KBPS   //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
#define RF24_PA_LEVEL 	   RF24_PA_MAX    //Sensor PA Level == RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBM, and RF24_PA_MAX=0dBm
#define RF24_PA_LEVEL_GW   RF24_PA_LOW  //Gateway PA Level, defaults to Sensor net PA Level.  Tune here if using an amplified nRF2401+ in your gateway.
#define BASE_RADIO_ID 	   ((uint64_t)0xA8A8E1FC00LL) // This is also act as base value for sensor nodeId addresses. Change this (or channel) if you have more than one sensor network.

// nRF2401 Pins
#define DEFAULT_CE_PIN 9
#define DEFAULT_CS_PIN 10

/***
 * nRF905 Configuration
 */

// Frequency
#define NRF905_FREQ			433200000UL

// Frequency band
// NRF905_BAND_433
// NRF905_BAND_868
// NRF905_BAND_915
#define NRF905_BAND			NRF905_BAND_433

// Output power
// n means negative, n10 = -10
// NRF905_PWR_n10 (-10dBm = 100uW)
// NRF905_PWR_n2 (-2dBm = 631uW)
// NRF905_PWR_6 (6dBm = 4mW)
// NRF905_PWR_10 (10dBm = 10mW)
#define NRF905_PWR			NRF905_PWR_10

// nRF905 Pins
// Arduino pins
#define TRX_EN		7	// Enable/standby pin
#define PWR_MODE	8	// Power mode pin
#define TX_EN		9	// TX / RX mode pin
#define CD			2	// Carrier detect pin (for collision avoidance, if enabled)
#define CSN			10	// SPI slave select pin

///////////////////
// Interrupt register stuff
// Only needed if NRF905_INTERRUPTS is 1
///////////////////
// Interrupt number (INT0, INT1 etc)
// This must match the INT that is connected to DR
#define INTERRUPT_NUM	1
// Data ready pin
// If using interrupts (NRF905_INTERRUPTS 1) then this must be
// an external interrupt pin that matches the interrupt register settings below.
#define DR			3





/***
 * Enable/Disable debug logging
 */
#define DEBUG

#endif
