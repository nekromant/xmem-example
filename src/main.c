#include <avr/io.h>
#include <stdio.h>
#include <common.h>
#include <util/delay.h>


int main()
{
    stdio_init(115200);
    while (1) {
        printf("X\n");
        _delay_ms(1000);
    }
    while (1);
}
