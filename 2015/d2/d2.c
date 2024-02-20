/************************************************************************
 * @file 2015/d1/d2.c
 * @author durken
 * @brief aoc 2015
 **************************************************************************/
#include <stdint.h>
#include <string.h>
#include <neorv32.h>
#include <de10_lite.h>

/* -------- UART interface -------- */

#define PRINT_TEXT(...) neorv32_uart0_puts(__VA_ARGS__)
#define PRINT_GETC(a) neorv32_uart0_getc()
#define PRINT_PUTC(a) neorv32_uart0_putc(a)

/* -------------------------------- */

void d2(void)
{
    char c = 1;
    int i = 0;
    int dim[3] = {0};
    int tmp = 0;
    uint32_t sum = 0;
    int line = 0;
    int bow = 0;
    de10_lite_7seg_enable_loading();

    while (1)
    {
        while (line < 1000) // EOF check
        {
            c = PRINT_GETC();
            switch (c)
            {
            case 0x0A: // LF
                ++line;
                i = 0;               // reset intex
                if (dim[0] > dim[2]) // sort array
                {
                    tmp = dim[0];
                    dim[0] = dim[2];
                    dim[2] = tmp;
                }
                if (dim[1] > dim[2])
                {
                    tmp = dim[1];
                    dim[1] = dim[2];
                    dim[2] = tmp;
                }

                sum += 3 * dim[0] * dim[1] + 2 * (dim[0] * dim[2] + dim[1] * dim[2]); // Smallest area will be dim[0]*dim[1]
                bow += 2 * (dim[0] + dim[1]) + dim[0] * dim[1] * dim[2];
                memset(dim, 0, sizeof dim); // clear array data
                break;

            case 'x':
                i++;
                break;

            default:
                dim[i] = 10 * dim[i] + c - '0';
            }
        }

        while (1)
        {
            if (neorv32_gpio_pin_get(2) == 0)
            {
                de10_lite_7seg_write_unsigned_hex(bow);
            }
            else
            {
                de10_lite_7seg_write_unsigned_hex(sum);
            }
        }
    }
}