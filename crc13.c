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

void print_usage(char *prg)
{
	fprintf(stderr, "%s - Returns CRC13 of input stream.\n\n", prg);
	fprintf(stderr, "   Usage: %s <input stream>\n\n", prg);
	exit(EXIT_FAILURE);
}

int calc_crc13(uint8_t inputs[], uint16_t *crc)
{
    uint16_t crc_tmp = 0;
    uint8_t in, pos;
    int i = 0; /* MAX_ARG_STRLEN = PAGE_SIZE(4096) * 32 */

    if (inputs == NULL || crc == NULL) {
        return -EINVAL;
    }

    while (inputs[i] != '\0') {
        in = inputs[i];
        pos = (uint8_t)((crc_tmp ^ ((uint16_t)in << (13u - 8u))) >> (13u - 8u));
        crc_tmp = (uint16_t)(((uint32_t)crc_tmp << 8) ^ (uint32_t)crc_tab[pos]);
        i++;
    }

    *crc = crc_tmp;

    return 0;
}

int main(int argc, char *argv[])
{
    uint16_t crc;

    if (argc != 2) {
        print_usage(argv[0]);
    }

    if (calc_crc13((uint8_t*)argv[1], &crc) != 0) {
        perror("Error: calc_crc13: Invalid argument(s)");
        exit(EXIT_FAILURE);
    }

    printf("0x%04x\n", crc);

    return 0;
}
