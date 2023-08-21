 /* crc13.c - Returns CRC13 of input stream
  *
  * Jonathan Liang <jonathan.yh.liang@gmail.com>
  * 
  */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "crc13_tab.h"

int calc_crc13(uint8_t ch, uint16_t *crc)
{
    uint16_t crc_tmp = *crc;
    uint8_t pos;

    if (crc == NULL) {
        return -EINVAL;
    }

    pos = (uint8_t)((crc_tmp ^ ((uint16_t)ch << (13u - 8u))) >> (13u - 8u));
    crc_tmp = (uint16_t)(((uint32_t)crc_tmp << 8) ^ (uint32_t)crc_tab[pos]);
    crc_tmp &= 0x1FFF;
    *crc = crc_tmp;

    return 0;
}

int main()
{
    uint16_t crc = 0;

    errno = 0;

    while(1) {
        int ch = getchar();
        if (ch != EOF) {
            /* Skip control characters */
            if (ch > 31 && ch != 127) {
                if (calc_crc13((uint8_t)ch, &crc) != 0) {
                    perror("Error: calc_crc13: Invalid argument(s)");
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            if (errno) {
                perror("Error: stdin (%d)");
                exit(EXIT_FAILURE);
            }

            printf("0x%04x\n", crc);
            break;
        }
    }

    return 0;
}
