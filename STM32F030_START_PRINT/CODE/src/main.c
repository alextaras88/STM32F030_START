#include "main.h"

char str[20];
uint16_t i = 0;

char barCode1[] = "01234567890";
char barCode2[] = "0123456789012";
char barCode3[] = "0123456789";

void test_heat_modes(void);

	
int main(void){
	
	Clock_Init();
	Delay_Init();
	GPIO_Init();
	thermal_printer_init();
	
	I2c_Init();
	ssd1306_Init();
	
	ssd1306_SetCursor(20, 0);
	ssd1306_WriteString("PRINTER", Font_11x18, White);
	ssd1306_UpdateScreen();
	
//  thermo_select_character_size(1, 1);
//	thermo_printf("ABCDEFGHJKLMNOPQASTUVWXWZ\r\n");
//	thermo_printf("*****\r\n");
//	thermo_printf("****\r\n");
//	thermo_printf("***\r\n");
//	thermo_printf("*\r\n");
//	thermo_printf("***\r\n");
//	thermo_printf("*****\r\n");
//	thermo_printf("-----------HELLO-----------\r\n");
//	thermo_printf("-----------ÏÐÈÂÅÒ-----------\r\n");
//	thermo_skip_lines(20);

	
	while(1){
		
		
		
		
	
		
		if ((GPIOA->IDR & GPIO_IDR_4) == 0){

			Delay_ms(200);

			if ((GPIOA->IDR & GPIO_IDR_4) == 0){
				
				
  
				
				
		   // thermo_select_character_size(2, 2);
				thermo_printf("ABCDEFGHJKLMNOPQASTUVWXWZ\r\n");
				thermo_printf("àáâãäåæýèêëìíýþÿ\r\n");
				thermo_printf("*****\r\n");
				thermo_printf("****\r\n");
				thermo_printf("***\r\n");
				thermo_printf("*\r\n");
				thermo_printf("***\r\n");
				thermo_printf("****\r\n");
				thermo_printf("*****\r\n");
				thermo_printf("-----------HELLO-----------\r\n");
				thermo_skip_lines(10);
				
				
				
				
			}
		}
	}
}

void test_heat_modes(void)
{
  // ??? ????????? HeatPoints ??????? ?? ?????
  thermo_set_print_concentration(9, 80, 2);
  thermo_printf("HeatPoints=9\r\n");

  thermo_set_print_concentration(15, 80, 2);
  thermo_printf("HeatPoints=15\r\n");
  
  thermo_set_print_concentration(25, 80, 2);
  thermo_printf("HeatPoints=25\r\n");

  thermo_set_print_concentration(40, 80, 2);
  thermo_printf("HeatPoints=40\r\n");

  thermo_set_print_concentration(80, 80, 2);
  thermo_printf("HeatPoints=80\r\n");

  thermo_set_print_concentration(160, 80, 2);
  thermo_printf("HeatPoints=160\r\n");

  // ??? ????????? HeatTime ??????????? ?????????? ???????????, ?? ??? ????????? ???? 150 ???????? ???????????
  thermo_set_print_concentration(9, 1, 2);
  thermo_printf("HeatTime=1\r\n");

  thermo_set_print_concentration(9, 5, 2);
  thermo_printf("HeatTime=5\r\n");

  thermo_set_print_concentration(9, 10, 2);
  thermo_printf("HeatTime=10\r\n");

  thermo_set_print_concentration(9, 20, 2);
  thermo_printf("HeatTime=20\r\n");

  thermo_set_print_concentration(9, 30, 2);
  thermo_printf("HeatTime=30\r\n");

  thermo_set_print_concentration(9, 40, 2);
  thermo_printf("HeatTime=40\r\n");

  thermo_set_print_concentration(9, 50, 2);
  thermo_printf("HeatTime=50\r\n");

  thermo_set_print_concentration(9, 60, 2);
  thermo_printf("HeatTime=60\r\n");

  thermo_set_print_concentration(9, 70, 2);
  thermo_printf("HeatTime=70\r\n");

  thermo_set_print_concentration(9, 80, 2);
  thermo_printf("HeatTime=80\r\n");

  thermo_set_print_concentration(9, 130, 2);
  thermo_printf("HeatTime=130\r\n");

  thermo_set_print_concentration(9, 180, 2);
  thermo_printf("HeatTime=180\r\n");

  thermo_set_print_concentration(9, 240, 2);
  thermo_printf("HeatTime=240\r\n");

  thermo_set_print_concentration(9, 255, 2);
  thermo_printf("HeatTime=255\r\n");
  thermo_set_print_concentration(9, 80, 2);

  // ??? ?????????? HeatInterval ??????????? ?????????? ???????
  thermo_set_print_concentration(9, 80, 1);
  thermo_printf("HeatInterval=1\r\n");
  
  thermo_set_print_concentration(9, 80, 10);
  thermo_printf("HeatInterval=10\r\n");
  
  thermo_set_print_concentration(9, 80, 25);
  thermo_printf("HeatInterval=25\r\n");
  
  thermo_set_print_concentration(9, 80, 50);
  thermo_printf("HeatInterval=50\r\n");
  
  thermo_set_print_concentration(9, 80, 75);
  thermo_printf("HeatInterval=75\r\n");
  
  thermo_set_print_concentration(9, 80, 100);
  thermo_printf("HeatInterval=100\r\n");
  
  thermo_set_print_concentration(9, 80, 125);
  thermo_printf("HeatInterval=125\r\n");
  
  thermo_set_print_concentration(9, 80, 150);
  thermo_printf("HeatInterval=150\r\n");
  
  thermo_set_print_concentration(9, 80, 175);
  thermo_printf("HeatInterval=175\r\n");
  
  thermo_set_print_concentration(9, 80, 200);
  thermo_printf("HeatInterval=200\r\n");
  
  thermo_set_print_concentration(9, 80, 225);
  thermo_printf("HeatInterval=225\r\n");
  
  thermo_set_print_concentration(9, 80, 255);
  thermo_printf("HeatInterval=255\r\n");
  
  thermo_set_print_concentration(9, 80, 2);
	
}
