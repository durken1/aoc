/************************************************************************
 * @file 2015/d3/d3.c
 * @author durken
 * @brief aoc 2015
 **************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <neorv32.h>
#include <de10_lite.h>

/* -------- UART interface -------- */

#define PRINT_TEXT(...) neorv32_uart0_puts(__VA_ARGS__)
#define PRINT_GETC(a) neorv32_uart0_getc()
#define PRINT_PUTC(a) neorv32_uart0_putc(a)

/* -------------------------------- */

void d3(void)
{
    char c = 0;
    int matrix[14][14] = {0};
    int xy[2] = {98, 98};
    while (1)
    {
        c = PRINT_GETC();
        switch (c)
        {
        case '<':

            break;

        case '>':

            break;

        case 'v':

            break;

        case '^':

            break;
        
        default:
            while(1)
            {
                if(neorv32_gpio_pin_get(2) != 0)
                {
                    de10_lite_7seg_write_signed_dec(0);
                }
                else
                {
                    de10_lite_7seg_write_signed_dec(0);
                }
            }
        }
    }
}
