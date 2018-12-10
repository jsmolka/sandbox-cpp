#include <locale.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>

#include "args.h"
#include "result.h"
#include "util.h"
#include "vector.h"

#define BUFFER 4096

Args *args;
Vector *results;

char *readline(FILE *file, bool *eof)
{
    int size = 0;
    int len = 0;
    int last = 0;
    char *temp = NULL;

    do
    {
        size += BUFFER;
        temp = (char *)realloc(temp, size);

        if (!fgets(temp + last, BUFFER, file))
        {
            *eof = true;
            break;
        }
        len = strlen(temp);
        last = len - 1;
    }
    while (temp[last] != '\n' && len != 0);

    return temp;
}

void parse_file(const wchar_t *fname)
{
    FILE *file = _wfopen(fname, L"r");

    if (!file)
        return;

    int line = 0;
    bool eof = false;

    while (!eof)
    {
        line++;
        char *temp = readline(file, &eof);
        if (strcnt(temp, args->key, args->sensitive))
        {
            static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

            pthread_mutex_lock(&mutex);
            vector_push(results, result_alloc(fname, line));
            pthread_mutex_unlock(&mutex);
        }
        free(temp);
    }
    fclose(file);
}

void *parse_files(void *arg)
{
    Vector *files = (Vector *)arg;
    for (size_t i = 0; i < vector_len(files); ++i)
        parse_file(vector_get(files, i));

    return NULL;
}

void run_threads(Vector *files)
{
    int threads = args->threads;
    Vector **chunks = vector_chunk(files, &threads);
    pthread_t *pthreads = (pthread_t *)malloc(threads * sizeof(pthread_t));

    for (int i = 0; i < threads; ++i)
        pthread_create(&pthreads[i], NULL, parse_files, chunks[i]);

    for (int i = 0; i < threads; ++i)
    {
        pthread_join(pthreads[i], NULL);
        free(chunks[i]);
    }
    free(chunks);
    free(pthreads);
}

int result_comparer(const void *lhs, const void *rhs)
{
    return result_compare(*(Result **)lhs, *(Result **)rhs);
}

void print_results()
{
    if (vector_len(results) == 0)
    {
        printf("No matching lines found\n");
    }
    else
    {
        qsort(results->array, vector_len(results), sizeof(Result *), result_comparer);
        
        for (size_t i = 0; i < vector_len(results); ++i)
        {
            Result *result = (Result *)vector_get(results, i);
            printf("%05d  %S\n", result->line, result->file);
        }
    }
    
}

void load_dir(const wchar_t *dir, const wchar_t *ext, Vector *files)
{
    wchar_t path[BUFFER];
    wcscpy(path, dir);
    wcscat(path, L"/*.*");

    WIN32_FIND_DATAW wfile;
    HANDLE handle = FindFirstFileW(path, &wfile);
    if (handle == INVALID_HANDLE_VALUE)
        return;
     
    do
    {
        if (wfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (!wcscmp(wfile.cFileName, L".") || !wcscmp(wfile.cFileName, L".."))
                continue;
        }

        memset(path, 0, BUFFER * sizeof(wchar_t));
        wcscpy(path, dir);
        wcscat(path, L"/");
        wcscat(path, wfile.cFileName);

        if (wfile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            load_dir(path, ext, files);
        }
        else
        {
            if (!ext || hasext(path, ext))
                vector_push(files, wcsdup(path));
        }
    }
    while (FindNextFileW(handle, &wfile));

    FindClose(handle);
}

void load_files(Vector *files)
{
    if (args->file)
        vector_push(files, args->file);

    if (args->dir)
        load_dir(args->dir, args->ext, files);
}

void globals_alloc(int argc, char *argv[])
{
    args = args_alloc();

    args_parse(args, argc, argv);
    if (!args_valid(args, argc, argv))
    {
        args_free(args);
        exit(0);
    }
    
    results = vector_alloc(0, (Deallocator)result_free);
}

void globals_free()
{
    vector_free(results);
    args_free(args);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    globals_alloc(argc, argv);

    Vector *files = vector_alloc(0, free);
    load_files(files);

    run_threads(files);
    print_results();

    vector_free(files);

    globals_free();

    return 0;
}
