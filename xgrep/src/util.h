#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <wchar.h>
#include <Windows.h>

static inline wchar_t *strtowcs(const char *str)
{
    const int len = strlen(str) + 1;
    wchar_t *wchar = (wchar_t *)malloc(len * sizeof(wchar_t));
    mbstowcs(wchar, str, len);

    return wchar;
}

static inline int wcscmpc(const wchar_t *a, const wchar_t *b)
{
    wchar_t *ca = wcsdup(a);
    wchar_t *cb = wcsdup(b);

    _wcslwr_s(ca, wcslen(ca) + 1);
    _wcslwr_s(cb, wcslen(cb) + 1);
    int cmp = wcscmp(ca, cb);

    free(ca);
    free(cb);

    return cmp;
}

static inline wchar_t *wcsrpl(wchar_t *wchar, wchar_t old, wchar_t new)
{
    for (wchar_t *p = wchar; (p = wcschr(p, old)); ++p)
        *p = new;

    return wchar;
}

static inline bool strcnt(const char *a, const char *b, bool sensitive)
{
    if (sensitive)
        return strstr(a, b) != NULL;

    char *ca = strdup(a);
    char *cb = strdup(b);

    _strlwr_s(ca, strlen(ca) + 1);
    _strlwr_s(cb, strlen(cb) + 1);
    const bool cnt = strstr(ca, cb) != NULL;

    free(ca);
    free(cb);

    return cnt;
}

static inline wchar_t *getcwd()
{
    wchar_t *cwd = _wgetcwd(NULL, 0);
    return wcsrpl(cwd, L'\\', L'/'); 
}

static inline bool isfile(const wchar_t *src)
{
    const DWORD attr = GetFileAttributesW(src);
    return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

static inline bool isdir(const wchar_t *src)
{
    const DWORD attr = GetFileAttributesW(src);
    return attr != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_DIRECTORY;
}

static inline bool hasext(const wchar_t *file, const wchar_t *ext)
{
    const wchar_t *end = wcsrchr(file, L'.');
    return end && wcscmpc(&end[1], ext) == 0;
}

#endif /* UTIL_H */
