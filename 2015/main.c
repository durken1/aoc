/************************************************************************
 * @file 2015/main.c
 * @author durken
 * @brief aoc 2015
 **************************************************************************/
#include <stdint.h>
#include <neorv32.h>
#include <de10_lite.h>
#include <aoc2015.h>

/* -------- UART interface -------- */

/** Set to 0 to disable UART interface */
#ifndef UART_EN
#define UART_EN 1
#endif

/** UART BAUD rate for serial interface */
#ifndef UART_BAUD
#define UART_BAUD 19200
#endif

/** Set to 1 to enable UART HW handshaking */
#ifndef UART_HW_HANDSHAKE_EN
#define UART_HW_HANDSHAKE_EN 0
#endif

#define PRINT_TEXT(...) neorv32_uart0_puts(__VA_ARGS__)
#define PRINT_GETC(a) neorv32_uart0_getc()
#define PRINT_PUTC(a) neorv32_uart0_putc(a)

/* -------------------------------- */

/************************************************************************
 * Main function; Choose day
 *
 * @note This program requires the GPIO controller to be synthesized.
 *
 * @return Will never return.
 **************************************************************************/
int main()
{
  neorv32_rte_setup();

  void (*fp[3]) (void);
  fp[0] = d1;
  fp[1] = d2;
  fp[2] = d3;

  while (1)
  {

    PRINT_TEXT("Choose day [1-25]\nCMD:> ");
    char day = PRINT_GETC();
    PRINT_PUTC(day); // echo
    PRINT_TEXT("\n");

    if (day > '3' || day < '1')
    {
      PRINT_TEXT("Invalid input\n");
    }
    else
    {
      PRINT_TEXT("Upload input\n");
      (*fp[day-'1'])();
    }

  } // while(1)
}
