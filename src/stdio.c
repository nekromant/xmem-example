#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#define BAUD 57600
#define MYUBRR F_CPU/16/BAUD-1 //скорость передачи

static FILE mystdin = FDEV_SETUP_STREAM(NULL, fgetc, _FDEV_SETUP_READ);
static FILE mystdout = FDEV_SETUP_STREAM(fputc, NULL, _FDEV_SETUP_WRITE);

void stdio_init(unsigned int baud)
{
	#define BAUD 57600
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;	//Enable receiver and transmitter

	UCSR0B = (1 << RXEN0) | (1 << TXEN0);   //разрешить приём и передачу данных
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);  //установка формата посылки: 8 бит данных, 2 стоп бита

	stdin = &mystdin;
	stdout = &mystdout;
}

int fputc(int c, FILE *_stream)
{
	if (c == '\n')
		fputc('\r', _stream);
	while (!(UCSR0A & (1 << UDRE0)));  //UDREO - флаг опустошения регистра UDR0 (пока в регистре данных нет значений, записываем в UDR0 бит
	UDR0 = c;
	return 0;
};

int fgetc(FILE *_stream)
{
	while (!(UCSR0A & (1 << RXC0))) ; //ожидание окончания приёма данных, RXC - флаг завершения приёма (пока есть данные в регистре UDR0, принимаем их)
	return UDR0;
}
