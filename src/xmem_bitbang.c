#include <avr/io.h>
#include <stdio.h>
#include <common.h>
#include <util/delay.h>
#include <avr/wdt.h>


void xmem_bb_init()
{
    DDRA = 0xff; /* AD[0:7] */
    DDRG |= (1<<2) | (1<<0) | (1<<1); /* ALE */
    DDRC = 0xff;
    DDRB |= 1<<0;
    DDRF |=
}


static void cs

static void rd(uint8_t state)
{
    if (state)
        DDRG |= (1<<1);
    else
        DDRG &= ~(1<<1);
}


static void wr(uint8_t state)
{
    if (state)
        DDRG |= (1<<0);
    else
        DDRG &= ~(1<<0);
}

static void data(uint8_t byte)
{
    PORTA=byte;
}

static void addr(uint16_t addr)
{
    xmem_bb_latch(addr & 0xff);
    PORTC |= (addr >> 8);
}

void xmem_bb_latch(uint8_t value)
{
    data(value);
    /* Do the ALE magic */
    PORTG &= ~(1<<2);
    PORTG |= 1<<2;
}

uint8_t xmem_read(uint16_t addr)
{
    addr(addr);

}
