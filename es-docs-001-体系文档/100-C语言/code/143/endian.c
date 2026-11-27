#include <stdio.h>
#include <stdint.h>

static int is_little_endian(void)
{
    uint16_t v = 0x0102;
    return *(uint8_t *)&v == 0x02;
}

static uint32_t bswap32(uint32_t x)
{
    return ((x & 0x000000FFu) << 24) | ((x & 0x0000FF00u) << 8) |
           ((x & 0x00FF0000u) >> 8)  | ((x & 0xFF000000u) >> 24);
}

int main(void)
{
    printf("little endian? %d\n", is_little_endian());

    uint32_t host = 0x12345678;
    printf("host   = 0x%08X\n", host);
    printf("bswap  = 0x%08X\n", bswap32(host));
    printf("bswap2 = 0x%08X\n", bswap32(bswap32(host)));

    uint8_t *b = (uint8_t *)&host;
    printf("bytes: %02X %02X %02X %02X\n", b[0], b[1], b[2], b[3]);
    return 0;
}
