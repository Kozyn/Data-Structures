/*


TABLE OF CONTENTS:
    How to Use API
    Return Code Reference
    Documentation

HOW TO USE API:
    First, you need to add in whatever file needs the Vector,
        DECLAREVECTOR(typename, type)
    This is just a macro to a ton of code defining structs and functions, so try to use it sparingly

    The documentation assumes that you called it like
        DECLAREVECTOR(Vector, int)
    
    Functions that return a value return a struct called VectorResult (assuming you called it like above). See documentation.

RETURN CODE REFERENCE:
     0: everything ok :D
    -1: input out of bounds or invalid
    -2: input vector is NULL or invalid
    -3: memory could not be allocated for given operation (or freed)        (see implementation)

DOCUMENTATION

    VectorResult

        .errcode
            int representing a potential error code (see return code reference)

        .result
            the value returned if the error code is 0

    Vector

        .length
            amount of elements currently in the Vector

        .capacity
            number of elements the Vector is capable of holding

        .data
            pointer to an allocated block of memory of type int

        Vector* Vector_new()
            returns a pointer to a Vector
        
        int Vector_free(Vector* v)
            frees memory where a Vector is stored

        int Vector_clear(Vector* v)
            removes all elements from a Vector, while keeping capacity

        int Vector_pushBack(Vector* v, int value)
            adds a new element to the end of the Vector

        int Vector_pushFront(Vector*v, int value)
            adds a new element to the beginning of the vector

        int Vector_insert(Vector* v, int value, long long int index)
            inserts a new element in the middle (or end) of the Vector

        VectorResult Vector_get(Vector* v, long long int index)
            reads an element at a specified index in the Vector

        VectorResult Vector_pop(Vector* v)
            gets the last element from the Vector, and removes it

        int Vector_set(Vector* v, int value, long long int index)
            sets the value of a specific element in the Vector

        VectorResult Vector_remove(Vector* v, long long int index)
            gets the element at a specified index, and then removes it from the Vector, shifting everythingright to the left


*/



#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

#define typeresult typename##Result

#define DECLAREVECTOR(typename, type) \
\
typedef struct { \
    long long int length, capacity; \
\
    type* data; \
} typename; \
\
typedef struct { \
    int errcode; \
    type result; \
} typeresult; \
\
typename* typename##_new() { \
    typename *ret = (typename*) malloc(sizeof(typename)); \
    if(!ret) return NULL; \
\
    ret->length = 0; \
    ret->capacity = 8; \
    ret->data = (type*) calloc(ret->capacity, sizeof(type)); \
    if(!ret->data) return NULL; \
\
    return ret; \
} \
\
int typename##_free(typename *v) { \
    if(!v) return -2; \
    free(v->data); \
    free(v); \
\
    return 0; \
} \
\
int typename##_clear(typename *v) { \
    if(!v) return -2; \
\
    free(v->data); \
    v->data = calloc(v->capacity, sizeof(type)); \
    if(!v->data) return -3; \
\
    v->length = 0; \
\
    return 0; \
} \
\
int typename##_pushBack(typename *v, type value) { \
    if(!v) return -2; \
\
    if(v->length + 1 > v->capacity) { \
        long long int new_capacity = v->capacity * 2; \
        type* new_data = (type*) realloc(v->data, new_capacity * sizeof(type)); \
\
        if(!new_data) return -3; \
\
        v->capacity = new_capacity; \
        v->data = new_data; \
    } \
\
    v->data[v->length] = value; \
    v->length++; \
\
    return 0; \
} \
\
int typename##_insert(typename *v, type value, long long int index) { \
    if(!v) return -2; \
    if(index > v->length) return -1; \
\
    long long int old_max = v->length - 1; \
\
    typename##_pushBack(v, v->data[v->length - 1]); \
\
    for(long long int i = old_max; i >= index + 1; i--) { \
        v->data[i] = v->data[i - 1]; \
    } \
\
    v->data[index] = value; \
\
    return 0; \
} \
\
int typename##_pushFront(typename *v, int value) { \
    if(!v) return -2; \
\
    typename##_insert(v, value, 0); \
\
    return 0; \
} \
\
typeresult typename##_get(typename *v, long long int index) { \
    if(!v) return (typeresult) {.errcode = -2}; \
    if(index > v->length - 1) return (typeresult) {.errcode = -1}; \
\
    return (typeresult) {.errcode = 0, .result = v->data[index]}; \
} \
\
typeresult typename##_pop(typename* v) { \
    if(!v) return (typeresult) {.errcode = -2}; \
\
    int ret = v->data[v->length - 1]; \
    v->length--; \
\
    return (typeresult) {.errcode = 0, .result = ret}; \
} \
\
int typename##_set(typename *v, type value, long long int index) { \
    if(!v) return -2; \
    if(index > v->length - 1) return -1; \
\
    v->data[index] = value; \
    return 0; \
} \
\
typeresult typename##_remove(typename *v, long long int index) { \
    if(!v) return (typeresult) {.errcode = -2}; \
    if(index > v->length - 1) return (typeresult) {.errcode = -1}; \
\
    int ret = typename##_get(v, index).result; \
\
    for(long long int i = index; i < v->length - 1; i++) { \
        v->data[i] = v->data[i + 1]; \
    } \
\
    v->length--; \
\
    return (typeresult) {.errcode = 0, .result = ret}; \
\
} \
\
void typename##_print(typename *v) { \
    for(long long int i = 0; i < v->length; i++) { \
        int tmp; \
        tmp = v->data[i]; \
        printf("%d\t", tmp); \
    } \
} 

#endif