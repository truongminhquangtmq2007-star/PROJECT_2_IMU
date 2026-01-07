#include "button.h"
#include "main.h"
	

uint8_t btn_current=1;
uint8_t btn_last=1;
uint8_t btn_filter=1;
uint8_t is_debouncing;
uint32_t time_debounce;
uint32_t time_start_press;
uint8_t is_press_time_out=1;


void btn_pressing_callback()
{
}
void btn_release_callback()
{
}
//----------NHAN KHONG QUA 3s DOI CHE DO------
void btn_short_press_callback() 
{
    Set_Zero_Now(); 
}
//-------------NHAN GIU QUA 3s----------------
void btn_press_time_out_callback()
{
			
}
	
void button_handle()
	//-------------------LOC NHIEU--------------
	{
		uint8_t sta = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		if( sta != btn_filter)
		{
			btn_filter=sta;
			is_debouncing=1;
			time_debounce = HAL_GetTick();
		}	
		//------------- Tin hieu da xac lap-------------
		if (is_debouncing && (HAL_GetTick()-time_debounce>=15))
		{
			btn_current=btn_filter;
			is_debouncing=0;
		}
	//-----------------Xu li---------------
		if(btn_current != btn_last)
		{
			if(btn_current==0)// nhan xuong
			{
				btn_pressing_callback();
				time_start_press=HAL_GetTick();
				is_press_time_out = 1;
			}
			else //nha nut
			{
				if (is_press_time_out==1 && (HAL_GetTick() - time_start_press <= 1000))
				{	
				btn_short_press_callback();
					
				}is_press_time_out = 0;
			btn_release_callback();
			}
			btn_last=btn_current;	
		}	
		//--------------NHAN GIU--------------		
		if (is_press_time_out&& (HAL_GetTick() - time_start_press >= 3000))
		{
			btn_press_time_out_callback();
			is_press_time_out=0;
		}
}		
