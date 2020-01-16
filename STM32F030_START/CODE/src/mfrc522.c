#include "mfrc522.h"

/******************************************************************************/
void mfrc522_spi_Init(void){
	
	// GPIO INIT
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;											// Clock GPIOB
	GPIOA->AFR[0] |= (0<<20)|(0<<24)|(0<<28);								// PA5, PA6, PA7 - GPIO AF0

	// PA5 SCK
	GPIOA->MODER |= GPIO_MODER_MODER5_1;										// AF
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;											// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;       				// Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;											// No pull-up, pull-down

	// PA6 MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
  GPIOA->MODER |= GPIO_MODER_MODER6_1;										// INPUT Floating
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6;

	// PA7 MOSI
	GPIOA->MODER |= GPIO_MODER_MODER7_1;										// AF
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_7;											// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;       				// Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7;											// No pull-up, pull-down
	
	// PB1 CS
	GPIOB->MODER |= GPIO_MODER_MODER0_1;   			 			 			// OUT PB_1
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;  							 			// Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;	     	 			// High speed
	
	CS_MFRC522_HIGH;
	
	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;											// Clock SPI1

	SPI1->CR1 |=  SPI_CR1_BR_2;       											// Spi Clock div 48MHz/32 (1.5MHz)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= SPI_CR2_DS_0 |SPI_CR2_DS_1 | SPI_CR2_DS_2; // 8 bit data;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;													// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;									// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;															// SPI Master Mode

	SPI1->CR1 |= SPI_CR1_SPE;																// SPI Enable
	
	GPIOA->MODER |= GPIO_MODER_MODER4_1;   			 			 			// OUT PB_1
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;  							 			// Push pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;	     	 			// High speed
	
}
/******************************************************************************/
void mfrc522_WriteREG(uint8_t addr, uint8_t data){
	
	CS_MFRC522_LOW;
	Spi_Transfer(SPI1, (addr<<1) & 0x7E);
	Spi_Transfer(SPI1, data);
	CS_MFRC522_HIGH;
	
}
/******************************************************************************/
uint8_t mfrc522_ReadREG(uint8_t addr){
	
	uint8_t data;
	
	CS_MFRC522_LOW;
  Spi_Transfer(SPI1, ((addr<<1) & 0x7E|0x80));
  data =  Spi_Transfer(SPI1, 0x00 );
	CS_MFRC522_HIGH;
	
	return data;
	
}
/******************************************************************************/
void mfrc522_SetBitMask(uint8_t reg, uint8_t mask){
	
	mfrc522_WriteREG(reg, mfrc522_ReadREG(reg) | mask);
	
}
/******************************************************************************/
void mfrc522_ClearBitMask(uint8_t reg, uint8_t mask){
	
	mfrc522_WriteREG(reg, mfrc522_ReadREG(reg) & (~mask));
	
}	
/******************************************************************************/
void mfrc522_AntennaOn(void){
	
	uint8_t temp;

	temp = mfrc522_ReadREG(MFRC522_REG_TX_CONTROL);
	if (!(temp & 0x03)) mfrc522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
	
}
/******************************************************************************/
void mfrc522_AntennaOff(void){
	
	mfrc522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
	
}
/******************************************************************************/
void mfrc522_Reset(void){
	
	mfrc522_WriteREG(MFRC522_REG_COMMAND, PCD_RESETPHASE);
	
}
/******************************************************************************/
uint8_t mfrc522_Request(uint8_t reqMode, uint8_t * TagType){
	
	uint8_t status;  
	uint16_t backBits;																				// The received data bits

	mfrc522_WriteREG(MFRC522_REG_BIT_FRAMING, 0x07);					// TxLastBists = BitFramingReg[2..0]
	TagType[0] = reqMode;
	status = mfrc522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
	if ((status != MI_OK) || (backBits != 0x10)) status = MI_ERR;
	
	return status;
	
}
/******************************************************************************/
uint8_t mfrc522_ToCard(uint8_t command, uint8_t * sendData, uint8_t sendLen, uint8_t * backData, uint16_t * backLen){
	
	uint8_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command) {
		case PCD_AUTHENT: {
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE: {
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
		break;
	}

	mfrc522_WriteREG(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
	mfrc522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
	mfrc522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
	mfrc522_WriteREG(MFRC522_REG_COMMAND, PCD_IDLE);

	// Writing data to the FIFO
	for (i = 0; i < sendLen; i++) mfrc522_WriteREG(MFRC522_REG_FIFO_DATA, sendData[i]);

	// Execute the command
	mfrc522_WriteREG(MFRC522_REG_COMMAND, command);
	if (command == PCD_TRANSCEIVE) mfrc522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);			// StartSend=1,transmission of data starts 

	// Waiting to receive data to complete
	i = 2000;	// i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms
	do {
		// CommIrqReg[7..0]
		// Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = mfrc522_ReadREG(MFRC522_REG_COMM_IRQ);
		i--;
	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	mfrc522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);																	// StartSend=0

	if (i != 0)  {
		if (!(mfrc522_ReadREG(MFRC522_REG_ERROR) & 0x1B)) {
			status = MI_OK;
			if (n & irqEn & 0x01) status = MI_NOTAGERR;
			if (command == PCD_TRANSCEIVE) {
				n = mfrc522_ReadREG(MFRC522_REG_FIFO_LEVEL);
				lastBits = mfrc522_ReadREG(MFRC522_REG_CONTROL) & 0x07;
				if (lastBits) *backLen = (n - 1) * 8 + lastBits; else *backLen = n * 8;
				if (n == 0) n = 1;
				if (n > MFRC522_MAX_LEN) n = MFRC522_MAX_LEN;
				for (i = 0; i < n; i++) backData[i] = mfrc522_ReadREG(MFRC522_REG_FIFO_DATA);		// Reading the received data in FIFO
			}
		} else status = MI_ERR;
	}
	return status;
}
/******************************************************************************/
uint8_t mfrc522_Anticoll(uint8_t cascade, uint8_t * serNum){
	
	uint8_t status;
	uint8_t i;
	uint8_t serNumCheck = 0;
	uint16_t unLen;

	mfrc522_WriteREG(MFRC522_REG_BIT_FRAMING, 0x00);												// TxLastBists = BitFramingReg[2..0]
	serNum[0] = 0x93;
	serNum[1] = 0x20;
	status = mfrc522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
	if (status == MI_OK) {
		// Check card serial number
		
		for (i = 0; i < 4; i++) serNumCheck ^= serNum[i];
		
		if (serNumCheck != serNum[i]) status = MI_ERR;
	}

	return status;
	
} 
/******************************************************************************/
void mfrc522_CalculateCRC(uint8_t *  pIndata, uint8_t len, uint8_t * pOutData){
	
	uint8_t i, n;

	mfrc522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);													// CRCIrq = 0
	mfrc522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);													// Clear the FIFO pointer
	// Write_MFRC522(CommandReg, PCD_IDLE);

	// Writing data to the FIFO	
	for (i = 0; i < len; i++) mfrc522_WriteREG(MFRC522_REG_FIFO_DATA, *(pIndata+i));
	mfrc522_WriteREG(MFRC522_REG_COMMAND, PCD_CALCCRC);

	// Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = mfrc522_ReadREG(MFRC522_REG_DIV_IRQ);
		i--;
	} while ((i!=0) && !(n&0x04));																		// CRCIrq = 1

	// Read CRC calculation result
	pOutData[0] = mfrc522_ReadREG(MFRC522_REG_CRC_RESULT_L);
	pOutData[1] = mfrc522_ReadREG(MFRC522_REG_CRC_RESULT_M);
	
}
/******************************************************************************/
uint8_t mfrc522_SelectTag(uint8_t * serNum){
	
	uint8_t i;
	uint8_t status;
	uint8_t size;
	uint16_t recvBits;
	uint8_t buffer[9]; 

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i = 0; i < 5; i++) buffer[i+2] = *(serNum+i);
	mfrc522_CalculateCRC(buffer, 7, &buffer[7]);		//??
	status = mfrc522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
	if ((status == MI_OK) && (recvBits == 0x18)) size = buffer[0]; else size = 0;
	
	return size;
	
}
/******************************************************************************/
uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t * Sectorkey, uint8_t * serNum){
	
	uint8_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[12]; 

	// Verify the command block address + sector + password + card serial number
	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i = 0; i < 6; i++) buff[i+2] = *(Sectorkey+i);
	for (i=0; i<4; i++) buff[i+8] = *(serNum+i);
	status = mfrc522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);
	if ((status != MI_OK) || (!(mfrc522_ReadREG(MFRC522_REG_STATUS2) & 0x08))) status = MI_ERR;
	
	return status;
	
}
/******************************************************************************/
uint8_t mfrc522_Read(uint8_t blockAddr, uint8_t * recvData){
	
	uint8_t status;
	uint16_t unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	mfrc522_CalculateCRC(recvData,2, &recvData[2]);
	status = mfrc522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);
	if ((status != MI_OK) || (unLen != 0x90)) status = MI_ERR;
	
	return status;
	
}
/******************************************************************************/
uint8_t mfrc522_Write(uint8_t blockAddr, uint8_t * writeData){
	
	uint8_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[18]; 

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	mfrc522_CalculateCRC(buff, 2, &buff[2]);
	status = mfrc522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);
	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) status = MI_ERR;
	if (status == MI_OK) {
		// Data to the FIFO write 16Byte
		for (i = 0; i < 16; i++) buff[i] = *(writeData+i);
		mfrc522_CalculateCRC(buff, 16, &buff[16]);
		status = mfrc522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) status = MI_ERR;
	}
	
	return status;
	
}
/******************************************************************************/
void mfrc522_Halt(void){
	
	uint16_t unLen;
	uint8_t buff[4]; 

	buff[0] = PICC_HALT;
	buff[1] = 0;
	mfrc522_CalculateCRC(buff, 2, &buff[2]);
	mfrc522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
	
}
/******************************************************************************/
uint8_t mfrc522_Check(uint8_t * id){
	
	uint8_t status;
	status = mfrc522_Request(PICC_REQIDL, id);							// Find cards, return card type
	if (status == MI_OK) status = mfrc522_Anticoll(0x93, id);			// Card detected. Anti-collision, return card serial number 4 bytes
	mfrc522_Halt();																					// Command card into hibernation 
	
	return status;
	
}
/******************************************************************************/
uint8_t mfrc522_Compare(uint8_t * CardID, uint8_t * CompareID){
	
	uint8_t i;
	
	for (i = 0; i < 5; i++) {
		if (CardID[i] != CompareID[i]) return MI_ERR;
	}
	
	return MI_OK;
	
}
/******************************************************************************/
void mfrc522_Init(void){
	
	mfrc522_spi_Init();
	
	mfrc522_Reset();
	Delay_ms(200);
	mfrc522_WriteREG(MFRC522_REG_T_MODE, 0x80);
	mfrc522_WriteREG(MFRC522_REG_T_PRESCALER, 0xA9);
	mfrc522_WriteREG(MFRC522_REG_T_RELOAD_L, 0xE8);           
	mfrc522_WriteREG(MFRC522_REG_T_RELOAD_H, 0x03);
	mfrc522_WriteREG(MFRC522_REG_RF_CFG, 0x70);			// 48dB gain	
	mfrc522_WriteREG(MFRC522_REG_TX_AUTO, 0x40);
	mfrc522_WriteREG(MFRC522_REG_MODE, 0x3D);
	mfrc522_AntennaOn();														// Open the antenna
	
	Delay_ms(100);
}
/******************************************************************************/
