#include <stdio.h>
#include <string.h>

int convert_decimal_to_binary(const int dec, char *out, const int lead_bit = 0)
{
    int d = dec, len = lead_bit;

    if(len == 0)
        do len++; while ((d /= 2) != 0);

    for(int i = len - 1; i >= 0; i--)
        sprintf(out, "%s%d", out, (dec >> i) & 1);

    return len;
}

int main(void)
{
    /* 0(bin) have length 1, so r[0] should be 1 */
    int bin_max[18] = { 1, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };
    int bin_len[18] = { 0, };

    for(int i = 0; i < 131072; i++)
    {
        char bin[18] = {0, };
        int len = convert_decimal_to_binary(i, bin);

        if(strstr(bin, "00") != NULL) bin_len[len]++;
    }

    for(int i = 0; i < 18; i++)
        printf("%d: %d\n", i, bin_max[i] - bin_len[i]);

    return 0;
}
