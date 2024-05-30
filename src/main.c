#include <stdio.h>
#include <math.h>

#include "Vector.h"

DECLAREVECTOR(Vector, int);

int main() {

    Vector* v = Vector_new();
    
    if(!v) {
        printf("failed to allocate memory");
        return -1;
    }

    for(int i = 0; i < 8; i++) {
        Vector_pushBack(v, 12 - i + 3);
    }
    
    Vector_print(v);
    printf("\n");

    Vector_insert(v, 96, 3);

    Vector_print(v);
    printf("\n");

    Vector_remove(v, 1);

    Vector_print(v);
    printf("\n");

    Vector_pushFront(v, 83);

    Vector_print(v);
    printf("\n");

    Vector_free(v);

    return 0;
}

