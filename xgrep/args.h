#ifndef ARGS_H
#define ARGS_H

#include <stdbool.h>
#include <wchar.h>

typedef struct
{
    wchar_t *dir;
    wchar_t *file;
    wchar_t *ext;
    char *key;
    int threads;
    bool sensitive;
    bool help;
} Args;

Args *args_alloc();
void args_parse(Args *this, int argc, char *argv[]);
bool args_valid(const Args *this, int argc, char *argv[]);
void args_free(Args *this);

#endif /* ARGS_H */
