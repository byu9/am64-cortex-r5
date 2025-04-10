/*
 * c_runtime.c
 *
 *  Created on: Apr 9, 2025
 *      Author: JohnYu
 */
#include <string.h>
#include <stdint.h>

/*
 * The GCC compiler will sometimes emit calls to memset, memcpy, memmove, etc, which are defined
 * in the C standard library. Since we specifically asked the compiler to not link in the standard
 * library (which usually just contains a bunch of empty function stubs on embedded platforms),
 * we need to provide an implementation for these memory functions in case the compiler emit
 * calls to them.
 */
void* memset(void *dest, int val, size_t len)
{
    uint8_t *ptr = (uint8_t*) dest;
    uint8_t byte = (uint8_t) val;

    while (len--)
    {
        *ptr++ = byte;
    }
    return dest;
}

void* memcpy(void *__restrict dest, const void *__restrict src, size_t len)
{
    uint8_t *d = (uint8_t*) dest;
    const uint8_t *s = (const uint8_t*) src;

    while (len--)
    {
        *d++ = *s++;
    }
    return dest;
}

void* memmove(void *dest, const void *src, size_t len)
{
    uint8_t *d = (uint8_t*) dest;
    const uint8_t *s = (const uint8_t*) src;

    if (d == s || len == 0)
    {
        return dest; // Nothing to do
    }

    if (d < s)
    {
        // Copy forwards
        while (len--)
        {
            *d++ = *s++;
        }
    }
    else
    {
        // Copy backwards
        d += len;
        s += len;
        while (len--)
        {
            *--d = *--s;
        }
    }

    return dest;
}

