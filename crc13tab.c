 /* crc13_tab.c - Generates CRC13 lookup table
  *
  * Jonathan Liang <jonathan.yh.liang@gmail.com>
  * 
  */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define POLYNOMIAL  (0x1909)

int gen_crc_tab(FILE *fp, const uint16_t poly)
{
    if (fp == NULL) {
        return -ENOENT;
    }

    fprintf(fp, "const uint16_t crc_tab[] = {\n");

    for (int dividend = 0; dividend < 256; dividend++) {
        uint16_t padded_dividend = (uint16_t)((uint16_t)dividend << (13u - 8u));
        for (int bit = 0; bit < 8; bit++) {
            if ((padded_dividend & 0x1000) != 0) {
                padded_dividend <<= 1;
                padded_dividend ^= poly;
            } else {
                padded_dividend <<= 1;
            }
        }

        /* Fetch CRC13 value */
        padded_dividend &= 0x1FFF;

        if (dividend == 255) { 
            fprintf(fp, "    0x%04x\n", padded_dividend);
            fprintf(fp, "};\n");
        } else {
            fprintf(fp, "    0x%04x,\n", padded_dividend);
        }
    }

    return 0;
}

int main(void)
{
    FILE *fp = NULL;

    fp = fopen("crc13_tab.h", "w");
    if (fp == NULL) {
        perror("Error: No such file or directory");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "#ifndef _CRC13TAB_H_\n");
    fprintf(fp, "#define _CRC13TAB_H_\n\n");
    fprintf(fp, "#include <stdint.h>\n\n");

    /* Generate CRC13 lookup table here */
    if (gen_crc_tab(fp, POLYNOMIAL) != 0) {
        perror("Error: gen_crc_tab: No such file or directory");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\n#endif\n");
    fclose(fp);

    return 0;
}
