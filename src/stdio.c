#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>


int uart_putc(char c, FILE *_stream)
{
	if (c == '\n')
		fputc('\r', _stream);
	while (!(UCSR0A & (1 << UDRE0)));  //UDREO - флаг опустошения регистра UDR0 (пока в регистре данных нет значений, записываем в UDR0 бит
	UDR0 = c;
	return 0;
};

int uart_getc(FILE *_stream)
{
	while (!(UCSR0A & (1 << RXC0))) ; //ожидание окончания приёма данных, RXC - флаг завершения приёма (пока есть данные в регистре UDR0, принимаем их)
	return UDR0;
}



FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getc, _FDEV_SETUP_READ);
FILE uart_output = FDEV_SETUP_STREAM(uart_putc, NULL, _FDEV_SETUP_WRITE);

void stdio_init(unsigned int baud)
{
	#define BAUD 57600
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;	//Enable receiver and transmitter

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);   //разрешить приём и передачу данных
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);  //установка формата посылки: 8 бит данных, 2 стоп бита
	
	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif
	
        stdin = &uart_input;
	stdout = &uart_output;
        printf("stdio: subsystem initialized @ 57600 bps\n");
}

