#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdlib.h>

typedef void (*Deallocator)(void *);

typedef struct 
{
    void **array;
    size_t used;
    size_t size;
    Deallocator dealloc;
} Vector;

static inline Vector *vector_alloc(size_t size, Deallocator dealloc)
{
    Vector *this = (Vector *)malloc(sizeof(Vector));
    this->array = (void **)malloc(size * sizeof(void *));
    this->used = 0;
    this->size = size;
    this->dealloc = dealloc;

    return this;
}

static inline void vector_set(Vector *this, size_t index, void *elem)
{
    this->array[index] = elem;
}

static inline void *vector_get(Vector *this, size_t index)
{
    return this->array[index];
}

static inline void vector_push(Vector *this, void *elem)
{
    if (this->used == this->size)
    {
        this->size = (3 * this->size) / 2 + 2; 
        this->array = (void **)realloc(this->array, this->size * sizeof(void *));
    }
    this->array[this->used++] = elem;
}

static inline void *vector_first(Vector *this)
{
    return this->array[0];
}

static inline void *vector_last(Vector *this)
{
    return this->array[this->used - 1];
}

static inline size_t vector_len(Vector *this)
{
    return this->used;
}

static inline Vector **vector_chunk(Vector *this, int *n)
{
    *n = fmin(*n, this->used);

    Vector **chunks = (Vector **)malloc(*n * sizeof(Vector *));
    const int quo = this->used / *n;
    const int rem = this->used % *n;
    for (int i = 0; i < *n; ++i)
    {
        chunks[i] = (Vector *)malloc(sizeof(Vector));
        chunks[i]->dealloc = NULL;

        const int l = i * quo + fmin(i, rem);
        const int r = (i + 1) * quo + fmin(i + 1, rem);
        chunks[i]->array = &this->array[l];
        chunks[i]->used = r - l;
    }
    return chunks;
}

static inline void vector_free(Vector *this)
{
    if (this->dealloc != NULL)
    {
        for (size_t i = 0; i < this->used; ++i)
            (*this->dealloc)(this->array[i]);
    }
    free(this->array);
    free(this);
}

#endif /* VECTOR_H */
