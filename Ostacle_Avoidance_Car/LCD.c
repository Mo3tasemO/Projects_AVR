/*
 * LCD.c
 *
 *  Created on: Oct 3, 2023
 *  Author: Yousef Mostafa
 *
 */


#include "LCD.h"
#include "gpio.h"
#include "common_macros.h"
#include <util/delay.h>



/*******************************************************************************
 *                             Static Functions Prototypes                     *
 *******************************************************************************/






void LCD_sendCommmand(uint8 command)
{
	/* RS = 0 for command  */
	GPIO_writePin(PORT_RS , PIN_RS , LOGIC_LOW);
	/*delay for tas*/

	_delay_ms(TAS_TIME);

	/*enable PIN0_ID*/
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_HIGH);

	/*delay for tpw*/
	_delay_ms(TPW_TIME);

#if(LCD_DATA_BITS_MODE == 8)
	GPIO_writePort(PORT_LCD,command);
#elif(LCD_DATA_BITS_MODE==4)
	GPIO_writePin(PORT_LCD , LCD_PIN1_ID , GET_BIT(command , 4));
	GPIO_writePin(PORT_LCD , LCD_PIN2_ID , GET_BIT(command , 5));
	GPIO_writePin(PORT_LCD , LCD_PIN3_ID , GET_BIT(command , 6));
	GPIO_writePin(PORT_LCD , LCD_PIN4_ID , GET_BIT(command , 7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_HIGH);
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	GPIO_writePin(PORT_LCD , LCD_PIN1_ID , GET_BIT(command , 0));
	GPIO_writePin(PORT_LCD , LCD_PIN2_ID , GET_BIT(command , 1));
	GPIO_writePin(PORT_LCD , LCD_PIN3_ID , GET_BIT(command , 2));
	GPIO_writePin(PORT_LCD , LCD_PIN4_ID , GET_BIT(command , 3));


#endif
	_delay_ms(1);

	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_LOW);

	/*delay for th*/
	_delay_ms(TH_TIME);



}

void LCD_displayCharcter(uint8 Data)
{
	/* RS = 1 for data transimetion  */
	GPIO_writePin(PORT_RS , PIN_RS , LOGIC_HIGH);
	/*delay for tas*/
	_delay_ms(TAS_TIME);
	/*enable E*/
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_HIGH);
	/*delay for tpw*/
	_delay_ms(TPW_TIME);
#if (LCD_DATA_BITS_MODE == 8 )
	GPIO_writePort(PORT_LCD , Data);

#elif (LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(PORT_LCD , LCD_PIN1_ID , GET_BIT(Data , 4));
	GPIO_writePin(PORT_LCD , LCD_PIN2_ID , GET_BIT(Data , 5));
	GPIO_writePin(PORT_LCD , LCD_PIN3_ID , GET_BIT(Data , 6));
	GPIO_writePin(PORT_LCD , LCD_PIN4_ID , GET_BIT(Data , 7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_HIGH);
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	GPIO_writePin(PORT_LCD , LCD_PIN1_ID , GET_BIT(Data , 0));
	GPIO_writePin(PORT_LCD , LCD_PIN2_ID , GET_BIT(Data , 1));
	GPIO_writePin(PORT_LCD , LCD_PIN3_ID , GET_BIT(Data , 2));
	GPIO_writePin(PORT_LCD , LCD_PIN4_ID , GET_BIT(Data , 3));


#endif

	GPIO_writePin(PORT_E_enabel , PIN_E_enabel , LOGIC_LOW);

	/*delay for th*/

	_delay_ms(TH_TIME);

}

void LCD_init (void)
{


	/* RS*/
	GPIO_setupPinDirection(PORT_RS , PIN_RS , PIN_OUTPUT);


	/*enable PIN0_ID*/
	GPIO_setupPinDirection(PORT_E_enabel , PIN_E_enabel , PIN_OUTPUT);

#if (LCD_DATA_BITS_MODE ==8)
	/*setup direction for port data*/
	GPIO_setupPortDirection(PORT_LCD , PORT_OUTPUT);

#elif(LCD_DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(PORT_LCD , LCD_PIN1_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_LCD , LCD_PIN2_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_LCD , LCD_PIN3_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(PORT_LCD , LCD_PIN4_ID , PIN_OUTPUT);


#endif
	_delay_ms(20);


	LCD_sendCommmand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	LCD_sendCommmand(LCD_CURSOR_OFF);
	LCD_sendCommmand(LCD_CLEAR_COMMAND);



}
void LCD_displayString(const uint8 *a_str)
{
	uint8 l_size;
	l_size = 0 ;
	for( 	l_size = 0 ;a_str[l_size] != '\0';	l_size++ )
	{
		LCD_displayCharcter(a_str[l_size]);
	}

}

void LCD_moveCursor(uint8 row , uint8 colum )

{
	uint8 l_adressCursor;
#if (LCD_TYPE ==4)
	switch(row)
	{
		case 0:
			l_adressCursor=colum;
				break;
		case 1:
			l_adressCursor=colum+0x40;
				break;
		case 2:
			l_adressCursor=colum+0x10;
				break;
		case 3:
			l_adressCursor=colum+0x50;
				break;
	}
#elif (LCD_TYPE == 2)
	switch(row)
	{
		case 0:
			l_adressCursor=colum;
				break;
		case 1:
			l_adressCursor=colum+0x40;
				break;
	}
#endif
	LCD_sendCommmand((LCD_SET_CURSOR_LOCATION | l_adressCursor));

}
void LCD_displayStringRowCoulmn(uint8 row , uint8 column ,const uint8  * str )
{
	LCD_moveCursor(row ,column);
	LCD_displayString(str);
}


void LCD_clearScreen()
{
	LCD_sendCommmand(LCD_CLEAR_COMMAND);
}

void LCD_intgerToString(uint32 num)
{
	uint8 i=0;
	uint8 size = 0;
	uint8 intTostr[16];
	uint8 temp ;


	for (i = 0 ; num != 0 ; i++)
	{
		intTostr[i] = (num%10)+ 48;
		num/=10;
	}
	size = i;

	for(i = 0 ; i < (size /2) ; i ++)
	{
		temp = intTostr[i];
		intTostr[i] = intTostr[(size-i-1)];
		intTostr[(size-i-1)] = temp;
	}

	intTostr[size] = '\0';
	LCD_displayString(intTostr);

/*

	  Tark code
	  char buff[16];
	   itoa(num,buff,10);
	   LCD_displayString(buff);

*/
}
