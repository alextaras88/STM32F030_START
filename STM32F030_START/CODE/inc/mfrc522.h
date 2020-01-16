#ifndef _MFRC522_H_
#define _MFRC522_H_

#include "stm32f0xx.h"

#include <stdbool.h>

#include "spi.h"
#include "delay.h"


#define		  CS_MFRC522_LOW 	    GPIOB->BSRR = GPIO_BSRR_BR_1;
#define 	  CS_MFRC522_HIGH 	  GPIOB->BSRR = GPIO_BSRR_BS_1;

// Status enumeration, Used with most functions
#define MI_OK					0
#define MI_NOTAGERR		1
#define MI_ERR				2

// MFRC522 Commands
#define PCD_IDLE								0x00   // NO action; Cancel the current command
#define PCD_AUTHENT							0x0E   // Authentication Key
#define PCD_RECEIVE							0x08   // Receive Data
#define PCD_TRANSMIT						0x04   // Transmit data
#define PCD_TRANSCEIVE					0x0C   // Transmit and receive data,
#define PCD_RESETPHASE					0x0F   // Reset
#define PCD_CALCCRC							0x03   // CRC Calculate

// Mifare_One card command word
#define PICC_REQIDL							0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL							0x52   // find all the cards antenna area
#define PICC_ANTICOLL						0x93   // anti-collision
#define PICC_SElECTTAG					0x93   // election card
#define PICC_AUTHENT1A					0x60   // authentication key A
#define PICC_AUTHENT1B					0x61   // authentication key B
#define PICC_READ								0x30   // Read Block
#define PICC_WRITE							0xA0   // write block
#define PICC_DECREMENT					0xC0   // debit
#define PICC_INCREMENT					0xC1   // recharge
#define PICC_RESTORE						0xC2   // transfer block data to the buffer
#define PICC_TRANSFER						0xB0   // save the data in the buffer
#define PICC_HALT								0x50   // Sleep

// MFRC522 Registers
// Page 0: Command and Status
#define MFRC522_REG_RESERVED00				0x00
#define MFRC522_REG_COMMAND						0x01 
#define MFRC522_REG_COMM_IE_N					0x02 
#define MFRC522_REG_DIV1_EN						0x03 
#define MFRC522_REG_COMM_IRQ					0x04 
#define MFRC522_REG_DIV_IRQ						0x05 
#define MFRC522_REG_ERROR							0x06 
#define MFRC522_REG_STATUS1						0x07 
#define MFRC522_REG_STATUS2						0x08 
#define MFRC522_REG_FIFO_DATA					0x09 
#define MFRC522_REG_FIFO_LEVEL				0x0A 
#define MFRC522_REG_WATER_LEVEL				0x0B 
#define MFRC522_REG_CONTROL						0x0C 
#define MFRC522_REG_BIT_FRAMING				0x0D 
#define MFRC522_REG_COLL							0x0E 
#define MFRC522_REG_RESERVED01				0x0F 
// Page 1: Command
#define MFRC522_REG_RESERVED10				0x10 
#define MFRC522_REG_MODE							0x11 
#define MFRC522_REG_TX_MODE						0x12 
#define MFRC522_REG_RX_MODE						0x13 
#define MFRC522_REG_TX_CONTROL				0x14 
#define MFRC522_REG_TX_AUTO						0x15 
#define MFRC522_REG_TX_SELL						0x16 
#define MFRC522_REG_RX_SELL						0x17 
#define MFRC522_REG_RX_THRESHOLD			0x18 
#define MFRC522_REG_DEMOD							0x19 
#define MFRC522_REG_RESERVED11				0x1A 
#define MFRC522_REG_RESERVED12				0x1B 
#define MFRC522_REG_MIFARE						0x1C 
#define MFRC522_REG_RESERVED13				0x1D 
#define MFRC522_REG_RESERVED14				0x1E 
#define MFRC522_REG_SERIALSPEED				0x1F 
// Page 2: CFG
#define MFRC522_REG_RESERVED20				0x20 
#define MFRC522_REG_CRC_RESULT_M			0x21 
#define MFRC522_REG_CRC_RESULT_L			0x22 
#define MFRC522_REG_RESERVED21				0x23 
#define MFRC522_REG_MOD_WIDTH					0x24 
#define MFRC522_REG_RESERVED22				0x25 
#define MFRC522_REG_RF_CFG						0x26 
#define MFRC522_REG_GS_N							0x27 
#define MFRC522_REG_CWGS_PREG					0x28 
#define MFRC522_REG__MODGS_PREG				0x29 
#define MFRC522_REG_T_MODE						0x2A 
#define MFRC522_REG_T_PRESCALER				0x2B 
#define MFRC522_REG_T_RELOAD_H				0x2C 
#define MFRC522_REG_T_RELOAD_L				0x2D 
#define MFRC522_REG_T_COUNTER_VALUE_H	0x2E 
#define MFRC522_REG_T_COUNTER_VALUE_L	0x2F 
// Page 3:TestRegister
#define MFRC522_REG_RESERVED30				0x30 
#define MFRC522_REG_TEST_SEL1					0x31 
#define MFRC522_REG_TEST_SEL2					0x32 
#define MFRC522_REG_TEST_PIN_EN				0x33 
#define MFRC522_REG_TEST_PIN_VALUE		0x34 
#define MFRC522_REG_TEST_BUS					0x35 
#define MFRC522_REG_AUTO_TEST					0x36 
#define MFRC522_REG_VERSION						0x37 
#define MFRC522_REG_ANALOG_TEST				0x38 
#define MFRC522_REG_TEST_ADC1					0x39 
#define MFRC522_REG_TEST_ADC2					0x3A 
#define MFRC522_REG_TEST_ADC0					0x3B 
#define MFRC522_REG_RESERVED31				0x3C 
#define MFRC522_REG_RESERVED32				0x3D 
#define MFRC522_REG_RESERVED33				0x3E 
#define MFRC522_REG_RESERVED34				0x3F 

#define		STATUS_OK				 			1					// Success
#define		STATUS_ERROR			 		2					// Error in communication
#define		STATUS_COLLISION		 	3					// Collission detected
#define		STATUS_TIMEOUT			 	4					// Timeout in communication.
#define		STATUS_NO_ROOM			 	5					// A buffer is not big enough.
#define		STATUS_INTERNAL_ERROR	6					// Internal error in the code. Should not happen ;-)
#define		STATUS_INVALID			 	7					// Invalid argument.
#define		STATUS_CRC_WRONG		 	8					// The CRC_A does not match
#define		STATUS_MIFARE_NACK		9					// A MIFARE PICC responded with NAK.

#define 	MFRC522_DUMMY					0x00			// Dummy byte
#define 	MFRC522_MAX_LEN			  16				// Buf len byte


typedef struct {
		uint8_t	 size;					// Number of bytes in the UID. 4, 7 or 10.
		uint8_t		uidByte[10];
		uint8_t		sak;					// The SAK (Select acknowledge) byte returned from the PICC after successful selection.
	} Uid;


void mfrc522_spi_Init(void);

void mfrc522_WriteREG(uint8_t addr, uint8_t data);
uint8_t mfrc522_ReadREG(uint8_t addr);

void mfrc522_SetBitMask(uint8_t reg, uint8_t mask);
void mfrc522_ClearBitMask(uint8_t reg, uint8_t mask);

void mfrc522_AntennaOn(void);
void mfrc522_AntennaOff(void);
void mfrc522_Reset(void);
uint8_t mfrc522_Request(uint8_t reqMode, uint8_t * TagType);
uint8_t mfrc522_ToCard(uint8_t command, uint8_t * sendData, uint8_t sendLen, uint8_t * backData, uint16_t * backLen);
uint8_t mfrc522_Anticoll(uint8_t cascade, uint8_t * serNum);
void mfrc522_CalculateCRC(uint8_t *  pIndata, uint8_t len, uint8_t * pOutData);
uint8_t mfrc522_SelectTag(uint8_t * serNum);
uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t * Sectorkey, uint8_t * serNum);

uint8_t mfrc522_Read(uint8_t blockAddr, uint8_t * recvData);
uint8_t mfrc522_Write(uint8_t blockAddr, uint8_t * writeData);
void mfrc522_Halt(void);

uint8_t mfrc522_Check(uint8_t * id);
uint8_t mfrc522_Compare(uint8_t * CardID, uint8_t * CompareID);
void mfrc522_Init(void);

/******************************************************************************/












#endif /* _MFRC522_H_ */

