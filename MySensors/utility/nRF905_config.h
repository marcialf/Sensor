/*
 * Project: nRF905 AVR/Arduino Library/Driver
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/nrf905-avrarduino-librarydriver/
 */

#ifndef NRF905_CONFIG_H_
#define NRF905_CONFIG_H_

// Instructions
#define NRF905_CMD_NOP			0xFF
#define NRF905_CMD_W_CONFIG		0x00
#define NRF905_CMD_R_CONFIG		0x10
#define NRF905_CMD_W_TX_PAYLOAD	0x20
#define NRF905_CMD_R_TX_PAYLOAD	0x21
#define NRF905_CMD_W_TX_ADDRESS	0x22
#define NRF905_CMD_R_TX_ADDRESS	0x23
#define NRF905_CMD_R_RX_PAYLOAD	0x24
#define NRF905_CMD_CHAN_CONFIG	0x80

// Registers
#define NRF905_REG_CHANNEL		0x00
#define NRF905_REG_AUTO_RETRAN	0x01
#define NRF905_REG_LOW_RX		0x01
#define NRF905_REG_PWR			0x01
#define NRF905_REG_BAND			0x01
#define NRF905_REG_CRC			0x09
#define NRF905_REG_CLK			0x09
#define NRF905_REG_OUTCLK		0x09
#define NRF905_REG_OUTCLK_FREQ	0x09
#define NRF905_REG_RX_ADDRESS	0x05
#define NRF905_REG_RX_PAYLOAD_SIZE	0x03
#define NRF905_REG_TX_PAYLOAD_SIZE	0x04
#define NRF905_REG_ADDR_WIDTH	0x02

// Clock options
#define NRF905_CLK_4MHZ			0x00
#define NRF905_CLK_8MHZ			0x08
#define NRF905_CLK_12MHZ		0x10
#define NRF905_CLK_16MHZ		0x18
#define NRF905_CLK_20MHZ		0x20

// Register masks
#define NRF905_MASK_CHANNEL		0xFC
#define NRF905_MASK_AUTO_RETRAN	~(NRF905_AUTO_RETRAN_ENABLE | NRF905_AUTO_RETRAN_DISABLE) //0xDF
#define NRF905_MASK_LOW_RX		~(NRF905_LOW_RX_ENABLE | NRF905_LOW_RX_DISABLE) //0xEF
#define NRF905_MASK_PWR			~(NRF905_PWR_n10 | NRF905_PWR_n2 | NRF905_PWR_6 | NRF905_PWR_10) //0xF3
#define NRF905_MASK_BAND		~(NRF905_BAND_433 | NRF905_BAND_868 | NRF905_BAND_915) //0xFD
#define NRF905_MASK_CRC			(uint8_t)(~(NRF905_CRC_DISABLE | NRF905_CRC_8 | NRF905_CRC_16)) //0x3F // typecast to stop compiler moaning about large integer truncation
#define NRF905_MASK_CLK			~(NRF905_CLK_4MHZ | NRF905_CLK_8MHZ | NRF905_CLK_12MHZ | NRF905_CLK_16MHZ | NRF905_CLK_20MHZ) //0xC7
#define NRF905_MASK_OUTCLK		~(NRF905_OUTCLK_DISABLE | NRF905_OUTCLK_4MHZ | NRF905_OUTCLK_2MHZ | NRF905_OUTCLK_1MHZ | NRF905_OUTCLK_500KHZ) // 0xF8

// Bit positions
#define NRF905_STATUS_DR		5
#define NRF905_STATUS_AM		7

#include "nRF905_config.h"

#if (NRF905_DR_SW && NRF905_INTERRUPTS)
	#error "NRF905_INTERRUPTS and NRF905_DR_SW can not both be enabled"
#endif

// Workout channel from frequency & band
#define NRF905_CALC_CHANNEL(f, b)	((((f) / (1 + (b>>1))) - 422400000UL) / 100000UL)

#define CONCAT(a, b) a ## b
#define CONCAT2(a, b, c) a ## b ## c

#define PORT(port)			CONCAT(PORT, port)
#define PORTBIT(port, bit)	CONCAT2(PORT, port, bit)
#define DDR(port)			CONCAT(DDR, port)
#define PINPORT(port)		CONCAT(PIN, port)
#define PINBIT(port, bit)	CONCAT2(PIN, port, bit)
#define PCINT(pcint)		CONCAT(PCINT, pcint)

#define TRX_EN_DDR		DDR(CFG_TRX_EN_PORT)
#define TRX_EN_PORT		PORT(CFG_TRX_EN_PORT)
#define TRX_EN_BIT		PORTBIT(CFG_TRX_EN_PORT, CFG_TRX_EN_BIT)

#define PWR_MODE_DDR	DDR(CFG_PWR_MODE_PORT)
#define PWR_MODE_PORT	PORT(CFG_PWR_MODE_PORT)
#define PWR_MODE_BIT	PORTBIT(CFG_PWR_MODE_PORT, CFG_PWR_MODE_BIT)

#define TX_EN_DDR		DDR(CFG_TX_EN_PORT)
#define TX_EN_PORT		PORT(CFG_TX_EN_PORT)
#define TX_EN_BIT		PORTBIT(CFG_TX_EN_PORT, CFG_TX_EN_BIT)

#define CD_DDR			DDR(CFG_CD_PORT)
#define CD_PORT			PINPORT(CFG_CD_PORT)
#define CD_BIT			PINBIT(CFG_CD_PORT, CFG_CD_BIT)

#define AM_DDR			DDR(CFG_AM_PORT)
#define AM_PORT			PINPORT(CFG_AM_PORT)
#define AM_BIT			PINBIT(CFG_AM_PORT, CFG_AM_BIT)

#define DR_DDR			DDR(CFG_DR_PORT)
#define DR_PORT			PINPORT(CFG_DR_PORT)
#define DR_BIT			PINBIT(CFG_DR_PORT, CFG_DR_BIT)

#define CSN_DDR			DDR(CFG_CSN_PORT)
#define CSN_PORT		PORT(CFG_CSN_PORT)
#define CSN_BIT			PORTBIT(CFG_CSN_PORT, CFG_CSN_BIT)

#define INTCONCAT(num)		CONCAT(INT, num)
#define ISCCONCAT(num, bit)	CONCAT2(ISC, num, bit)
#define INTVECTCONCAT(num)	CONCAT2(INT, num, _vect)

#ifndef REG_EXTERNAL_INT
	#ifdef EIMSK
		#define REG_EXTERNAL_INT EIMSK
	#elif defined GICR
		#define REG_EXTERNAL_INT GICR
	#else
		#define REG_EXTERNAL_INT GIMSK
	#endif
#endif

#ifndef REG_EXTERNAL_INT_CTL
	#ifdef EICRA
		#if INTERRUPT_NUM < 4
			#define REG_EXTERNAL_INT_CTL EICRA
		#else
			#define REG_EXTERNAL_INT_CTL EICRB
		#endif
	#else
		#define REG_EXTERNAL_INT_CTL MCUCR
	#endif
#endif

#ifndef BIT_EXTERNAL_INT
	#define BIT_EXTERNAL_INT INTCONCAT(INTERRUPT_NUM)
#endif

#ifndef BIT_EXTERNAL_INT_CTL
	#define BIT_EXTERNAL_INT_CTL (_BV(ISCCONCAT(INTERRUPT_NUM, 1))|_BV(ISCCONCAT(INTERRUPT_NUM, 0)))
#endif

#ifndef INT_VECTOR
	#define INT_VECTOR INTVECTCONCAT(INTERRUPT_NUM)
#endif





// Crystal frequency (the one the radio IC/module is using)
// NRF905_CLK_4MHZ
// NRF905_CLK_8MHZ
// NRF905_CLK_12MHZ
// NRF905_CLK_16MHZ
// NRF905_CLK_20MHZ
#define NRF905_CLK_FREQ		NRF905_CLK_16MHZ

// Use pin interrupt for data ready
// NOTE: If you have other devices connected that use the SPI bus then you will need to call nRF905_interrupt_off() before using SPI comms and then RF905_interrupt_on() once you've finished.
#define NRF905_INTERRUPTS	1

// Buffer count
// Only used if interrupts are used (see NRF905_INTERRUPTS)
// NOT YET IMPLEMENTED
//#define BUFFER_COUNT_RX	1

// Buffer count
// NOT YET IMPLEMENTED
//#define BUFFER_COUNT_TX	1

//
// NOT YET IMPLEMENTED
//#define NRF905_MAX_PACKET_SIZE 64

// Use software to get address match state instead of reading pin for high/low state
// Not used in this library yet
#define NRF905_AM_SW		0

// Use software to get data ready state instead of reading pin for high/low state
// Interrupts and software DR can not be enabled together
#define NRF905_DR_SW		0

// Don't transmit if airway is busy (other transmissions are going on)
#define NRF905_COLLISION_AVOID	1

// ATmega48/88/168/328
// INT0 = D2 (Arduino UNO pin 2)
// INT1 = D3 (Arduino UNO pin 3)

// ATmega640/1280/1281/2560/2561
// INT0 = D0 (Arduino MEGA pin 21)
// INT1 = D1 (Arduino MEGA pin  20)
// INT2 = D2 (Arduino MEGA pin 19)
// INT3 = D3 (Arduino MEGA pin 18)
// INT4 = E4 (Arduino MEGA pin 2)
// INT5 = E5 (Arduino MEGA pin 3)
// INT6 = E6 (Arduino MEGA N/A)
// INT7 = E7 (Arduino MEGA N/A)

// Leave these commented out to let the library figure out what registers to use

// Which interrupt to use for data ready (DR)
//#define REG_EXTERNAL_INT	EIMSK
//#define BIT_EXTERNAL_INT	INT1
//#define INT_VECTOR			INT1_vect

// Set interrupt to trigger on rising edge
//#define REG_EXTERNAL_INT_CTL	EICRA
//#define BIT_EXTERNAL_INT_CTL	(_BV(ISC11)|_BV(ISC10))


///////////////////
// Default radio settings
///////////////////


// Save a few mA by reducing receive sensitivity
// NRF905_LOW_RX_DISABLE
// NRF905_LOW_RX_ENABLE
#define NRF905_LOW_RX		NRF905_LOW_RX_DISABLE

// Constantly retransmit payload while in transmit mode
// Can be useful in areas with lots of interference, but you'll need to make sure you can differentiate between re-transmitted packets and new packets (like an ID number).
// It will also block other transmissions if collision avoidance is enabled.
// NRF905_AUTO_RETRAN_DISABLE
// NRF905_AUTO_RETRAN_ENABLE
#define NRF905_AUTO_RETRAN	NRF905_AUTO_RETRAN_DISABLE

// Output a clock signal on pin 3 of IC
// NRF905_OUTCLK_DISABLE
// NRF905_OUTCLK_500KHZ
// NRF905_OUTCLK_1MHZ
// NRF905_OUTCLK_2MHZ
// NRF905_OUTCLK_4MHZ
#define NRF905_OUTCLK		NRF905_OUTCLK_DISABLE

// CRC checksum
// NRF905_CRC_DISABLE
// NRF905_CRC_8
// NRF905_CRC_16
#define NRF905_CRC			NRF905_CRC_16

// Address size
// Number of bytes for address
// NRF905_ADDR_SIZE_1
// NRF905_ADDR_SIZE_4
#define NRF905_ADDR_SIZE	NRF905_ADDR_SIZE_4

// Payload size (1 - 32)
#define NRF905_PAYLOAD_SIZE	32 //NRF905_MAX_PAYLOAD

#endif /* NRF905_CONFIG_H_ */