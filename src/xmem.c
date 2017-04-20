#include <avr/io.h>
#include <stdio.h>
#include <common.h>
#include <util/delay.h>
#include <avr/wdt.h>

void xmem_init()
{
        PORTC=0xff;
        DDRC=0xff;
        XMCRB = 0;
        /* RTFM: m1280 datasheet, p. 33 */
        XMCRA = (1<<SRE) | (1<<SRW00) | (1<<SRW01) | (1<<SRW10) | (1<<SRW11) ;

}


void xmem_dump(int len)
{

        volatile unsigned char *xptr = 0x2200;
        int pos;
        for (pos = 0; pos < len; pos++) {
                if ((pos % 16) == 0)
                        printf("\n");
                printf(" %02x", xptr[pos]);
        }

}


void xmem_test_bits()
{
    unsigned char *xptr = 0x2200;
    int i;
    int total = 0;
    for (i=0; i<8; i++) {
        *xptr = 1 << i;
        _delay_ms(50);
        if (! (*xptr & (1 <<i))) {
            printf("bit %d is stuck in 0\n", i);
            total++;
        }
        *xptr = ~(1 << i);
        _delay_ms(50);
        if (! (~(*xptr) & (1 <<i))) {
            printf("bit %d is stuck in 1\n", i);
            total++;
        }
    }
    printf("Total %d data bus errors\n", total);
}

void xmem_test() {
        unsigned char *xptr = 0x2200;
        int i;
        for (i=0; i<256; i++)
                xptr[i] = i;
        _delay_ms(10);
        for (i=0; i<256; i++)
                printf("xptr[%d]==%x\n", i, xptr[i]);
}
