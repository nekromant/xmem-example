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


void xmem_test() {
        unsigned char *xptr = 0x2200;
        int i;
        for (i=0; i<256; i++)
                xptr[i] = ~i;
        for (i=0; i<256; i++)
                printf("xptr[%d]==%x\n", i, xptr[i]);
}