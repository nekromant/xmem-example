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
        xmem_test_bits();
        xmem_test();
        xmem_dump(0x128);

#if 0
	xmem_bb_init();
	printf("xmem_bb: Testing ALE latch\n");
	uint8_t i = 0;
	while (1) {
		xmem_bb_latch(i++);
		_delay_ms(10);
	}
#endif
}
