/************************************************************************
 * @file 2015/d1/d2.c
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

void d1(void)
{
    char c = 0;
    int32_t sum = 0;
    uint32_t pos = 0;
    bool unlocked = true;
    uint32_t res = 0;
    while (1)
    {
        while (c != 10)
        {
            if (c == '(')
            {
                sum += 1;
            }
            else if (c == ')')
            {
                sum -= 1;
            }
            if (unlocked)
            {
                pos += 1;
                if (sum < 0)
                {
                    unlocked = false;
                }
            }
            c = PRINT_GETC();
        }

        res = neorv32_gpio_pin_get(0);
        if (res == 0)
        {
            de10_lite_7seg_write_signed_dec(pos);
        }
        else
        {
            de10_lite_7seg_write_signed_dec(sum);
        }
    }
}