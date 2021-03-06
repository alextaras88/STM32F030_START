/***************************/
/* MY_SSD1306             */

#include "ssd1306.h"

void ssd1306_Reset(void) {
	/* for I2C - do nothing */
}

// Send a byte to the command register
void ssd1306_WriteCommand(uint8_t byte){
	
	i2c_Start_addr(I2C1, SSD1306_I2C_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, 0x00);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, byte);
	i2c_BUSY(I2C1);
	
}

// Send data
void ssd1306_WriteData(uint8_t* buffer, uint16_t buff_size) {
	
	unsigned int i;
	
	i2c_Start_addr(I2C1, SSD1306_I2C_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, 0x40);
		for(i = 0; i < buff_size; i++){
		
		i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, buffer[i]);
		
	}
		
	 I2C1->CR2 &= ~I2C_CR2_RELOAD;   
   while (!(I2C1->ISR & I2C_ISR_STOPF)){}
	
}
	
	
//	Start_i2c();
//	Write_addr_i2c(SSD1306_I2C_ADDR, 0);
//	Write_one_data_i2c(0x40);
//	
//	for(i = 0; i < buff_size; i++){
//		
//		Write_data_i2c(buffer[i]);
//		
//	}
//	I2C1->CR1 &= ~I2C_CR1_ACK;
//	Stop_i2c();
//		
//}


// Screenbuffer
static uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

// Screen object
static SSD1306_t SSD1306;

// Initialize the oled screen
void ssd1306_Init(void){
	// Reset OLED
		ssd1306_Reset();

    // Wait for the screen to boot
    Delay_ms(100);
    
// Init OLED 128x64
    ssd1306_WriteCommand(0xAE); //display off

    ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode
    ssd1306_WriteCommand(0x10); // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode;
                                // 10,Page Addressing Mode (RESET); 11,Invalid

    ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
    ssd1306_WriteCommand(0xC0); // Mirror vertically
#else
    ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction
#endif

    ssd1306_WriteCommand(0x00); //---set low column address
    ssd1306_WriteCommand(0x10); //---set high column address

    ssd1306_WriteCommand(0x40); //--set start line address - CHECK

    ssd1306_WriteCommand(0x81); //--set contrast control register - CHECK
    ssd1306_WriteCommand(0xFF);

#ifdef SSD1306_MIRROR_HORIZ
    ssd1306_WriteCommand(0xA0); // Mirror horizontally
#else
    ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
    ssd1306_WriteCommand(0xA7); //--set inverse color
#else
    ssd1306_WriteCommand(0xA6); //--set normal color
#endif

    ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64) - CHECK
    ssd1306_WriteCommand(0x3F); //

    ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    ssd1306_WriteCommand(0xD3); //-set display offset - CHECK
    ssd1306_WriteCommand(0x00); //-not offset

    ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306_WriteCommand(0xF0); //--set divide ratio

    ssd1306_WriteCommand(0xD9); //--set pre-charge period
    ssd1306_WriteCommand(0x22); //

    ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration - CHECK
    ssd1306_WriteCommand(0x12);

    ssd1306_WriteCommand(0xDB); //--set vcomh
    ssd1306_WriteCommand(0x20); //0x20,0.77xVcc

    ssd1306_WriteCommand(0x8D); //--set DC-DC enable
    ssd1306_WriteCommand(0x14); //
    ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel
/*************************************************/
/* INIT SSD1306 128X32  												 */
/*************************************************/
//ssd1306_WriteCommand(0xAE);
//ssd1306_WriteCommand(0xD5);
//ssd1306_WriteCommand(0x80);

//ssd1306_WriteCommand(0xA8);
//ssd1306_WriteCommand(32-1);

//ssd1306_WriteCommand(0xD3);
//ssd1306_WriteCommand(0x40|0x0);
//ssd1306_WriteCommand(0x8D);
//ssd1306_WriteCommand(0x14);//

//ssd1306_WriteCommand(0x20);
//ssd1306_WriteCommand(0x00);
//ssd1306_WriteCommand(0xA0|0x1);
//ssd1306_WriteCommand(0xC8);

//ssd1306_WriteCommand(0xDA);
//ssd1306_WriteCommand(0x02);
//ssd1306_WriteCommand(0x81);
//ssd1306_WriteCommand(0x8F);
//ssd1306_WriteCommand(0xCF);//

//ssd1306_WriteCommand(0xD9);
//ssd1306_WriteCommand(0xF1);//
//ssd1306_WriteCommand(0xD8);
//ssd1306_WriteCommand(0x40);
//ssd1306_WriteCommand(0xA4);
//ssd1306_WriteCommand(0xA6);
//ssd1306_WriteCommand(0x2E);

//ssd1306_WriteCommand(0xAF);

    // Clear screen
    ssd1306_Fill(Black);
    
    // Flush buffer to screen
    ssd1306_UpdateScreen();
    
    // Set default values for screen object
    SSD1306.CurrentX = 0;
    SSD1306.CurrentY = 0;
    
    SSD1306.Initialized = 1;
}

// Fill the whole screen with the given color
void ssd1306_Fill(SSD1306_COLOR color) {
    /* Set memory */
    uint32_t i;

    for(i = 0; i < sizeof(SSD1306_Buffer); i++) {
        SSD1306_Buffer[i] = (color == Black) ? 0x00 : 0xFF;
    }
}

// Write the screenbuffer with changed to the screen
void ssd1306_UpdateScreen(void) {
    uint8_t i;
    for(i = 0; i < 8; i++) {
        ssd1306_WriteCommand(0xB0 + i);
        ssd1306_WriteCommand(0x00);
        ssd1306_WriteCommand(0x10);
        ssd1306_WriteData(&SSD1306_Buffer[SSD1306_WIDTH*i],SSD1306_WIDTH);
    }
}

//    Draw one pixel in the screenbuffer
//    X => X Coordinate
//    Y => Y Coordinate
//    color => Pixel color
void ssd1306_DrawPixel(uint8_t x, uint8_t y, SSD1306_COLOR color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }
    
    // Check if pixel should be inverted
    if(SSD1306.Inverted) {
        color = (SSD1306_COLOR)!color;
    }
    
    // Draw in the right color
    if(color == White) {
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else { 
        SSD1306_Buffer[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

// Draw 1 char to the screen buffer
// ch         => char om weg te schrijven
// Font     => Font waarmee we gaan schrijven
// color     => Black or White
char ssd1306_WriteChar(char ch, FontDef Font, SSD1306_COLOR color) {
    uint32_t i, b, j;
    
    // Check remaining space on current line
    if (SSD1306_WIDTH <= (SSD1306.CurrentX + Font.FontWidth) ||
        SSD1306_HEIGHT <= (SSD1306.CurrentY + Font.FontHeight))
    {
        // Not enough space on current line
        return 0;
    }
    
    // Use the font to write
    for(i = 0; i < Font.FontHeight; i++) {
        b = Font.data[(ch - 32) * Font.FontHeight + i];
        for(j = 0; j < Font.FontWidth; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR) color);
            } else {
                ssd1306_DrawPixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR)!color);
            }
        }
    }
    
    // The current space is now taken
    SSD1306.CurrentX += Font.FontWidth;
    
    // Return written char for validation
    return ch;
}

// Write full string to screenbuffer
char ssd1306_WriteString(char* str, FontDef Font, SSD1306_COLOR color) {
    // Write until null-byte
    while (*str) {
        if (ssd1306_WriteChar(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }
        
        // Next char
        str++;
    }
    
    // Everything ok
    return *str;
}

// Position the cursor
void ssd1306_SetCursor(uint8_t x, uint8_t y) {
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}
