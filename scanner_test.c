
#include <avr/io.h>
#include <stdint.h>
#include "libLCD/HD44780.h"
//#include "lib/fingerprint_sensor.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define u_delay  1
#define F_CPU 16000000 
#define BAUD 57600
#define MYUBRR ((F_CPU/16/BAUD)-1)
#define TX_BUFFER_SIZE = 128
#define RX_BUFFER_SIZE = 256

#define HEADER              0xEF     //Fixed value, High byte transmitted first.
#define LEADER				0x01
#define ADR                 0xFFFFFFFF
#define CMD_PKT             0x01
#define DATA_PKT            0x02
#define ACK_PKT             0x07
#define END_PKT             0x08
#define HANDSHAKE_CHECKSUM  0x001C
#define HANDSHAKE           0x17 
#define HS_LENGTH           0x04


/*Prototypes*/

void my_delay_ms(uint32_t delay);
void USART_Init(unsigned int ubrr);
void USART_Transmit(uint32_t data);

/*globals*/
volatile uint32_t  transmit_buffer[] = {HEADER , LEADER,  0xFF, 0xFF, 0xFF, 0xFF , CMD_PKT ,0x00 ,  HS_LENGTH , HANDSHAKE , 0x00 , 0x00, 0x1C}; 
volatile uint8_t recieve_buffer ; 


int main(void)
{
	
	uint32_t i ;
	LCD_Setup();
	LCD_Clear();
	LCD_GotoXY(0,0);
	LCD_PrintString("PLACE Finger");
	my_delay_ms(3000);
	
	USART_Init(MYUBRR);
	
	for (i=0; i<13; ++i)
	{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = transmit_buffer[i];
		
		LCD_Clear();
		LCD_PrintInteger(UDR0);
		my_delay_ms(1000);
		
		
	}
	
	if (UDRE0 != 1)
	{
	LCD_Clear();
	LCD_PrintString("Error");
	}
	
}		

void USART_Init(unsigned int ubrr)
{
	
	//Set baud rate 
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L =  (unsigned char) ubrr;
	
	//Enable receiver and transmitter /
	UCSR0B = /*(1 << RXEN0)|*/ (1 << TXEN0);

	// Set frame format: 8data, 1 stop bit 
	UCSR0C = (1 << UCSZ00) | (1<< UCSZ01);
	
	sei();

}


void USART_Transmit(uint32_t data)
{
	while (!(UCSR0A & (1<<UDRE0)))
	{
	UDR0 = data;
	}
	
}





//handles delays, only used in check_button_press_and_release function
void my_delay_ms(uint32_t delay) 
{
	uint32_t i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	if (delay % 10) {
		_delay_ms(delay % 10);
	}
}