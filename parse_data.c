/*
 * parse_data.c
 *
 *  Created on: Mar 6, 2022
 *      Author: root
 */
#include "main.h"
#include "buffer_ring.h"
#include "parse_data.h"
#include "utils.h"
#include "string.h"

void  Parse_SaveLine(BufferRing_t *Buf, uint8_t *LineData)
{
	uint8_t Tmp;
	uint8_t i = 0  ;
 	 	 do
		  {
			  	  BR_Read(Buf, &Tmp);
			  	  LineData[i] = Tmp;

			  	  i++;
		  }while(Tmp != ENDLINE);
}
void Parse_Data(uint8_t *Data){
	 //LED_ON0
			  //LED_OFF0
			  if (strcmp("LED_ON0",(char*)Data)== 0 )
			  {
				  	  HAL_GPIO_WritePin(GPIOA, LD_out_Pin, 1 );
				  	Uart_Message("LED_ON");

			  }
			  else if (strcmp("LED_OFF0",(char*)Data)== 0 )
			  {
				  HAL_GPIO_WritePin(GPIOA, LD_out_Pin, 0 );
				  Uart_Message("LED_OFF");
			  }

}

