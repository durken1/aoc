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
    int toggle = 0;
    uint32_t n_houses = 0;
    uint32_t direction = 0;
    while (1)
    {
        c = PRINT_GETC();
        de10_lite_7seg_enable_loading();
        if (c != 0x0A)
        {
            switch (c)
            {
            case 0x3E:
                direction = 0x00000000;
                break;

            case 0x3C:
                direction = 0x00000001;
                break;

            case 0x5E:
                direction = 0x00000002;
                break;

            case 0x76:
                direction = 0x00000003;
                break;
            }
            toggle = ~toggle;
            neorv32_cpu_store_unsigned_word(0x90000008, ((toggle & (1 << 2)) | direction));
        }
        else
        {
            n_houses = neorv32_cpu_load_unsigned_word(0x90000000);
            while (1)
            {
                if (neorv32_gpio_pin_get(2) != 0)
                {
                    de10_lite_7seg_write_signed_dec(n_houses);
                }
                else
                {
                    de10_lite_7seg_write_signed_dec(0);
                }
            }
        }
    }
}
