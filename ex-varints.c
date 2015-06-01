#include "common.h"
#include "varint.h"

typedef struct {
    uint16_t fixed1;
    uint64_t var2;
    uint32_t fixed3;
    uint8_t fixed4;
} foo_t;

int main() {
    uint8_t bytes[] = {
        0x13, 0x9c, 0xfd, 0x7d,
        0x80, 0x44, 0x6b, 0xa2,
        0x20, 0xcc
    };

    foo_t decoded;
    size_t varlen;

    decoded.fixed1 = bbp_eint16(BBP_LITTLE, *(uint16_t *)bytes);
    decoded.var2 = bbp_varint_get(bytes + 2, &varlen);
    decoded.fixed3 = bbp_eint32(BBP_LITTLE, *(uint32_t *)(bytes + 2 + varlen));
    decoded.fixed4 = *(bytes + 2 + varlen + 4);

    /* 9c13, 807d, 20a26b44, cc */
    printf("fixed1 = %x\n", decoded.fixed1);
    printf("var2 = %llx\n", decoded.var2);
    printf("fixed3 = %x\n", decoded.fixed3);
    printf("fixed4 = %x\n", decoded.fixed4);

    return 0;
}