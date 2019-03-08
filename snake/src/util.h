#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static inline int randint(int low, int high)
{
    return rand() % (high + 1 - low) + low;
}

#endif /* UTIL_H */
