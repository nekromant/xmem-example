#include <avr/io.h>
#include <stdio.h>
#include <common.h>
#include <util/delay.h>
#include <avr/wdt.h>



int main()
{
	wdt_disable();
	stdio_init();
        xmem_init();
        memset(0x2200, 0x0, 128);
        xmem_test();
        xmem_dump(0x128);
        
}
