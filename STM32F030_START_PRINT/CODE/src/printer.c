#include "printer.h"

/******************************************************************************/
void thermo_print(char *Str){
	
  USART1_Send_Buffer((uint8_t *)Str, strlen((char *)Str));
	
}
/******************************************************************************/
void thermo_printf(const char *args, ...)
{
  char StrBuff[256];
  
  va_list ap;
  va_start(ap, args);
  char len = vsnprintf(StrBuff, sizeof(StrBuff), args, ap);
  va_end(ap);
  
  thermo_print(StrBuff);
}
/******************************************************************************/
void thermal_printer_init(void){
	
	USART1_Init();
	Delay_ms(200);
	thermo_printer_initCmd();
	Delay_ms(200);
  thermo_china_mode(0);
	Delay_ms(200);
  thermo_set_codepage(WCP1252);
	Delay_ms(200);
}
/******************************************************************************/
void thermo_printer_initCmd(void){
	
  uint8_t buff[] = {ESC, '@'};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_china_mode(uint8_t state){
	
  uint8_t buff[] = {FS, state ? '&' : '.'};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_set_codepage(eCodePage codepage){
	
  uint8_t buff[] = {ESC, 't', codepage};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_set_print_concentration(uint8_t heatPoints, uint8_t heatTime, uint8_t heatInterval){
	
  uint8_t buff[] = {ESC, '7', heatPoints, heatTime, heatInterval};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_skip_lines(uint8_t x){
	
  uint8_t buff[] = {ESC, 'd', x};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_set_rotation_90_mode(uint8_t mode){
	
  uint8_t buff[] = {ESC, 'V', mode ? 1 : 0};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_select_character_size(uint8_t height_size, uint8_t width_size){
	
  if (height_size > 7)
    height_size = 7;
  if (width_size > 7)
    width_size = 7;
  
  uint8_t buff[] = {GS, '!', height_size | (width_size << 4)};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_print_barcode(eBarCodeType barCodeType, uint16_t dataLen, uint8_t *pData){
	
  uint8_t typeB = barCodeType > 10 ? 1 : 0;
  
  uint16_t idx = 0;
  uint8_t buff[270];
  buff[idx++] = GS;
  buff[idx++] = 'k';
  buff[idx++] = barCodeType;

  if (typeB)
    buff[idx++] = dataLen;

  for (uint16_t dataIdx = 0; dataIdx < dataLen; dataIdx++)
    buff[idx++] = *(pData++);

  if (!typeB)
    buff[idx++] = 0x00;
  
   USART1_Send_Buffer(buff, idx);
	
}
/******************************************************************************/
void thermo_set_barcode_height(uint8_t value){
	
  uint8_t buff[] = {GS, 'h', value};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
void thermo_set_barcode_width(uint8_t value){
	
  if ((value < 2) || (value > 6))
    return;
  
  uint8_t buff[] = {GS, 'w', value};
  USART1_Send_Buffer(buff, sizeof(buff));
	
}
/******************************************************************************/
