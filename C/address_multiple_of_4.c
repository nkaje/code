#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#define BUFSIZE 32
#define WIDTH   4

#define MIN(A, B) ((A) < (B) ? (A) : (B))

typedef enum {
    NODEBUG = 0,
    DEBUG = 1,
} DebugLevel;

int gloglevel = NODEBUG;

static inline void _dprintf(const char *format, ...)
{
    if (gloglevel) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

uint8_t gBase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int read_call(uint32_t *base, uint32_t offset, uint32_t length, uint8_t *ptr)
{
    uint8_t *begin = NULL;
    uint8_t tmp[BUFSIZE] = {0};
    uint8_t *ptrb = ptr;

    uint32_t mod = offset % WIDTH;

    begin = (uint8_t *)base + offset - mod;

    _dprintf("begin %p, offset %d, mod %d, length %d\n", begin, offset, mod, length);

    memcpy(tmp, begin, sizeof(uint32_t));
    begin += WIDTH;

    _dprintf("tmp %s, len %zu\n", tmp, strlen((char *)tmp));

    memcpy(ptr, &tmp[mod], MIN(length, WIDTH));
    _dprintf("%s %p %d\n", ptr, ptr, MIN(length, WIDTH));
    ptr += (WIDTH - mod);
    length -= MIN(length, WIDTH);

    _dprintf("length %d\n", length);

    while (length > 0)
    {
        memcpy(ptr, begin, MIN(length, WIDTH));
        _dprintf("begin %s, ptr %s %p, len %zu, length %d\n",
                begin, ptr, ptr, strlen((char *)ptr), MIN(length, WIDTH));
        ptr += MIN(length, WIDTH);
        begin += MIN(length, WIDTH);
        length -= MIN(length, WIDTH);
    }

    _dprintf("end %s\n", ptrb);
    return 0;
}

void read_and_dump(uint32_t *base, uint32_t offset, uint32_t length, uint8_t *buffer)
{
    memset(buffer, 0, BUFSIZE);
    read_call(base, offset, length, buffer);
    printf("%s\n", buffer);
}

int main()
{
    uint32_t *base = (uint32_t *)&gBase;
    uint32_t offset = 0x1;
    uint8_t buffer[BUFSIZE];

    for (uint32_t i = 4; i < 16; i++)
        read_and_dump(base, offset, i, &buffer[0]);
    return 0;
}
