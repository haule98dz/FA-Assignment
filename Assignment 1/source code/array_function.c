#include "array_function.h"

void swap(int *a, int *b);

void array_insert(int* a, int *size, int insert_position, int value) { 
    int i;
    for (i=*size-1; i >= insert_position; i--) {
        a[i+1] = a[i];
    }
    a[insert_position] = value;
    (*size)++;
}

void array_delete(int* a, int *size, int position) {   
    int i;
    for (i=position; i<*size-1; i++) {
        a[i] = a[i+1];
    }
    (*size)--;
}

void array_sort_ascending(int* a, int *size) { 
    if (*size != 0) {
        int i, j;
        for (i=*size-1; i>0; i--) {
            for (j=0; j<i; j++) {
                if (a[j]>a[j+1]) {
                    swap(a+j, a+j+1);
                }
            }
        }
    }
}

void array_sort_decending(int* a, int *size) { 
    if (*size != 0) {
        int i, j;
        for (i=*size-1; i>0; i--) {
            for (j=0; j<i; j++) {
                if (a[j]<a[j+1]) {
                    swap(a+j, a+j+1);
                }
            }
        }
    }
}

int array_search(int* a, int *size, int value) {   
    int res = -1;
    int i;
    for (i=0; i<*size; i++) {
        if (a[i] == value) {
            res = i;
            break;
        }
    }
    return res;
}

int array_max(int* a, int *size) { 
    int res = a[0];
    int i;
    for (i=1; i<*size; i++) {
        if (a[i] > res) res = a[i];
    }
    return res;
}

int array_min(int* a, int *size) { 
    int res = a[0];
    int i;
    for (i=1; i<*size; i++) {
        if (a[i] < res) res = a[i];
    }
    return res;
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}
