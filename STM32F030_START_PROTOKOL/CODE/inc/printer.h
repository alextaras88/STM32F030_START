#ifndef _PRINTER_H_
#define _PRINTER_H_

#include "stm32f0xx.h"
#include "usart.h"
#include "delay.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>



typedef enum
{
  ALIGN_LEFT = 0,
  ALIGN_MID = 1,
  ALIGN_RIGHT = 2
} eAlignType;

typedef enum
{
  America = 0,
  France = 1,
  Germany = 2,
  England = 3,
  Denmark = 4,
  Sweden = 5,
  Italy = 6,
  Spain = 7,
  Japan = 8,
  Norway = 9,
  Denmark2 = 10,
  Spain2 = 11,
  LatinAmerica = 12,
  Korea = 13,
  Slovenia = 14,
  China = 15
} eCharSet;

typedef enum
{
  CP437 = 0,
  KataKana = 1,
  CP850 = 2,
  CP860 = 3, 
  CP863 = 4,
  CP865 = 5,
  WCP1251 = 6,  
  CP866 = 7,    
  MIK = 8, 
  CP755 = 9,
  China2 = 10,
  China3 = 11,
  China4 = 12,
  China5 = 13,
  China6 = 14,
  CP862 = 15,
  WCP1252 = 16, 
  WCP1253 = 17,
  CP852 = 18, 
  CP858 = 19,
  China7 = 20,
  Latvia = 21,
  CP864 = 22,
  ISO_8859_1 = 23,
  CP737 = 24,
  WCP1257 = 25,
  China1 = 26,
  CP720 = 27,
  CP855 = 28,
  CP857 = 29,
  WCP1250 = 30,
  CP775 = 31,
  WCP1254 = 32,
  WCP1255 = 33,
  WCP1256 = 34,
  WCP1258 = 35,
  ISO_8859_2 = 36,
  ISO_8859_3 = 37,
  ISO_8859_4 = 38,
  ISO_8859_5 = 39,
  ISO_8859_6 = 40,
  ISO_8859_7 = 41,
  ISO_8859_8 = 42,
  ISO_8859_9 = 43,
  ISO_8859_15 = 44,
  Taybun = 45,
  CP856 = 46,
  CP874 = 47,
  GBK2312 = 255
} eCodePage;

typedef enum
{
  UPC_A = 0,           
  UPC_E = 1,           
  JAN13 = 2,            
  JAN8 = 3,             
  CODE39 = 4,          
  ITF = 5,              
  CODABAR = 6,        
  CODE93 = 72,         
  UCC_EAN1 = 74,        
} eBarCodeType;  

typedef enum
{
  CorrectionLevel_7 = 48,       // L
  CorrectionLevel_15 = 49,      // M
  CorrectionLevel_25 = 50,      // Q
  CorrectionLevel_30 = 51,      // H
} eQRcodeCorrectionLevel;

typedef enum
{
  Normal = 0,           
  DoubleX = 1,         
  DoubleY = 2,          
  DoubleXY = 3          
} eBitmapPrintMode;

#define SO      0x0E
#define DC4     0x14
#define ESC     0x1B
#define FS      0x1C
#define GS      0x1D

#define PRINTMODE_FONT_A_12x24            0x00
#define PRINTMODE_FONT_B_9x17             0x01
#define PRINTMODE_ANTI_WHITE_OFF          0x00
#define PRINTMODE_ANTI_WHITE_ON           0x02
#define PRINTMODE_UPSIDE_DOWN_OFF         0x00
#define PRINTMODE_UPSIDE_DOWN_ON          0x04  
#define PRINTMODE_BOLD_MODE_OFF           0x00
#define PRINTMODE_BOLD_MODE_ON            0x08
#define PRINTMODE_DOUBLE_HEIGHT_OFF       0x00
#define PRINTMODE_DOUBLE_HEIGHT_ON        0x10
#define PRINTMODE_DOUBLE_WIDTH_OFF        0x00
#define PRINTMODE_DOUBLE_WIDTH_ON         0x20
#define PRINTMODE_DELETE_LINE_MODE_OFF    0x00
#define PRINTMODE_DELETE_LINE_MODE_ON     0x40


void thermo_print(char *Str);
void thermo_printf(const char *args, ...);
void thermal_printer_init(void);

void thermo_printer_initCmd(void);
void thermo_china_mode(uint8_t state);
void thermo_set_codepage(eCodePage codepage);

void thermo_set_print_concentration(uint8_t heatPoints, uint8_t heatTime, uint8_t heatInterval);
void thermo_skip_lines(uint8_t x);
void thermo_set_rotation_90_mode(uint8_t mode);
void thermo_select_character_size(uint8_t height_size, uint8_t width_size);


void thermo_print_barcode(eBarCodeType barCodeType, uint16_t dataLen, uint8_t *pData);
void thermo_set_barcode_height(uint8_t value);
void thermo_set_barcode_width(uint8_t value);


#endif /* _PRINTER_H_ */

