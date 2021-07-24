#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define STRING_SIZE	13							///< Size of the string to be received.

void USART_INIT(void);
unsigned char USART_RECEIVE(void);
unsigned char * USART_RECEIVE_STRING(void);

uint8_t UBRR = 51;								///< Value to be changed to specify the baudrate for the particular operating clock frequency.

int main(void){
	USART_INIT();
	
	unsigned char *message;
	
	message = USART_RECEIVE_STRING();
}

/*!
 *	@brief Initialize USART.
 */

void USART_INIT(void){
	UCSRB |= (1<<RXEN);							///< Enable receiving over USART.
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);				///< Select register UCSRC and set transmission character size to 8 bits.
	UBRRL = UBRR;								///< Set UBRR value for specified baudrate at specified frequency.
}

/*!
 *	@brief Receive a character over USART.
 *	@return Character received (unsigned char).
 */

unsigned char USART_RECEIVE(void){
	while(!(UCSRA & (1<<RXC)));						///< Wait until data receiving is complete.
	return UDR;								///< Return contents of UDR register.
}

/*!
 *	@brief Receive a string of characters over USART.
 *	@return Received string (unsigned char).
 */

unsigned char * USART_RECEIVE_STRING(void){
	uint8_t i = 0;
	static unsigned char message[STRING_SIZE];
	do{
		message[i] = USART_RECEIVE();
		i++;
	}
	while(message[i-1]!=0);
	return message;
}
