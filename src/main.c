#include <avr/io.h>
#include <stdio.h>
#include <common.h>
#include <util/delay.h>
#include <avr/wdt.h>
#include <string.h> 

void writeByte( uint16_t add, uint8_t data) {
  DDRG  = 0xFF; //set to input
  PORTG |= (1<<PG2)|(1<<PG0);
  DDRA = 0xFF;
  PORTA = (add&0xFF);
  DDRC = 0xFF;
  PORTC = (add >> 8);
  PORTG &= ~(1<<PG2);
  _delay_ms(50);
  PORTA = data;
  PORTG &= ~(1<<PG0);
  _delay_ms(50);
  PORTG |= (1<<PG2)|(1<<PG0);
}

uint8_t readByte( uint16_t add) {
  uint8_t data;
  DDRG  = 0xFF;
  PORTG |= (1<<PG2)|(1<<PG1);
  DDRA = 0xFF;
  PORTA = add&0xFF;
  DDRC = 0xFF;
  PORTC = (add >> 8);
  PORTG &= ~(1<<PG2);
  DDRA = 0x00; //set to output
  _delay_ms(50);
  data = PINA;
  _delay_ms(50);
  PORTG &= ~(1<<PG1);
  return data;
}


int main()
{
	wdt_disable();
	stdio_init();
   //     xmem_init();
    memset(0x2200,0x0, 128);
	
	writeByte(0x2200, 0x55);
	printf("%x\n", readByte(0x2200));
	writeByte(0x2200, 0x11);
	printf("%x\n", readByte(0x2200));
	writeByte(0x2200, 0x10);
	printf("%x\n", readByte(0x2200));
	writeByte(0x2200, 0xFF);
	printf("%x\n", readByte(0x2200));
	
	
       // xmem_test_bits();
       // xmem_test();
        //xmem_dump(0x128);

}
