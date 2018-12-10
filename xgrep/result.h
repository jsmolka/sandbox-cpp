#ifndef RESULT_H
#define RESULT_H

#include <wchar.h>

typedef struct
{
    const wchar_t *file;
    int line;
} Result;

Result *result_alloc(const wchar_t *file, int line);
void result_free(Result *this);

int result_compare(const Result *lhs, const Result *rhs);

#endif /* RESULT_H */
