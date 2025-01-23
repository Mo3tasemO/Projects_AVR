/*
 * LCD.h
 *
 *  Created on: Oct 3, 2023
 *      Author: Yousef Mostafa
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif


#if (LCD_DATA_BITS_MODE == 4)

#define LCD_PIN1_ID                 PIN3_ID
#define LCD_PIN2_ID                 PIN4_ID
#define LCD_PIN3_ID                 PIN5_ID
#define LCD_PIN4_ID                 PIN6_ID

#endif

/* Definitions for PORT used for LCD */

#define PORT_LCD            PORTA_ID

#define PORT_RS             PORTB_ID
#define PIN_RS              PIN0_ID

#define PORT_E_enabel       PORTB_ID
#define PIN_E_enabel        PIN1_ID


/***********************************/


/*     Definitions of Time delay  */

#define TAS_TIME      1
#define TPW_TIME      1
#define TH_TIME       1

/*********************************/



/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80


/*      static configuration       */
#define LCD_TYPE 2


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void LCD_sendCommmand(uint8);
void LCD_displayCharcter(uint8);


void LCD_init(void);
void LCD_displayString(const uint8 *a_str);


void LCD_moveCursor(uint8 , uint8 );
void LCD_displayStringRowCoulmn(uint8 , uint8  , const uint8 *);

void LCD_intgerToString(uint32);
void LCD_clearScreen();


#endif /* LCD_H_ */
