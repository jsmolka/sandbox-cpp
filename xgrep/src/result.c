#include "result.h"

#include <stdlib.h>

#include "util.h"

Result *result_alloc(const wchar_t *file, int line)
{
    Result *this = (Result *)malloc(sizeof(Result));
    this->file = file;
    this->line = line;

    return this;
}

void result_free(Result *this)
{
    free(this);
}

int result_compare(const Result *lhs, const Result *rhs)
{
    const int cmp = wcscmpc(rhs->file, lhs->file);
    return cmp != 0 ? cmp : rhs->line - lhs->line;
}
