/*
Assignment 1
Author:
   Name: HauLD3
   Class: HN21_FR_EMB_03
Submission Date: 05/07/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include "array_function.h"

#define MAX_SIZE 100

int main(int argc, char** argv) {
/*--Print tutorial--*/
    printf(" CHUONG TRINH QUAN LY DAY SO BANG MANG\n");
    printf("   Nhap \'c\' de tao mang so nguyen\n   Nhap \'p\' de in day \n   Nhap \'i\' de them 1 phan tu vao day \n   Nhap \'d\' de xoa 1 phan tu tai vi tri k\n   Nhap \'s\' de sap xep day so theo chieu tang dan \n");
    printf("   Nhap \'x\' de sap xep theo chieu giam \n   Nhap \'t\' de tim kiem 1 so x co trong day khong x\n   Nhap tu ban phim \n   Nhap \'a\' de in ra man hinh so lon nhat \n   Nhap \'w\' de in ra man hinh so nho nhat\n");
    printf("   Nhap \'e\' de thoat chuong trinh.\n---------------------------------------------------------- \n");

/*--Main process--*/
    int array[MAX_SIZE];
    int array_size = 0;

    char ch = '\n';
    int value;
    unsigned int i;
    unsigned int position;

    while (1) {
/*------Scan command--*/
        if (ch != '\n') putchar('\n');
        else printf(">> ");
        scanf("%c", &ch);
        switch (ch) {
/*----------Create array--*/
            case 'c': case 'C':
                printf("Tao mang:\n  Nhap do dai mang: ");
                scanf("%d", &array_size);
                if (array_size <= 0 || array_size > MAX_SIZE) {
                    printf("Failed: Kich thuoc mang khong hop le (size <= %d)!\n", MAX_SIZE);
                    break;
                }

                for ( i=0; i<array_size; i++) {
                    printf("    Phan tu thu %u: ", i);
                    scanf("%d", &array[i]);
                }
                printf("Tao thanh cong mang co %d phan tu.\n", array_size);
                break;

/*----------Print array--*/
            case 'p': case 'P':
                if (array_size == 0) {
                    printf("Mang chua co phan tu nao.\n");
                    break;
                }
                printf("[%d", array[0]);
                for ( i=1; i<array_size; i++) {
                    printf(", %d", array[i]);
                }
                printf("]\n");
            break;

/*----------Insert into array--*/
            case 'i':case 'I':
                if (array_size == MAX_SIZE) {
                    printf("Failed: Out of memory :V\n");
                    break;
                }

                printf("Them phan tu vao mang:\n");
                printf("  Phan tu can them: ");
                scanf("%d", &value);
                printf("  Vi tri them: ");
                scanf("%u", &position);
                while (position < 0 || position > array_size) {
                    printf("  Vi tri khong hop le! Moi nhap lai: ");
                    scanf("%u", &position);
                }

                array_insert(array, &array_size, position, value);
                printf("Da chen %d vao vi tri %d.\n", value, position);
                break;

/*----------Delete element--*/
            case 'd': case 'D':
                if (array_size == 0) {
                    printf("Failed: Mang chua co phan tu.\n");
                    break;
                }
                
                printf("Xoa phan tu tai vi tri: ");
                scanf("%u", &position);
                if (position < 0 || position >= array_size) {
                    printf("Khong co phan tu thu %d.\n", position);
                    break;
                }

                array_delete(array, &array_size, position);
                printf("Da xoa phan tu thu %d.\n", position);
                break;

/*----------Ascending order sorting--*/
            case 's': case 'S':
                array_sort_ascending(array, &array_size);
                printf("Da sap xep theo chieu tang.\n");
                break;

/*----------Descending order sorting--*/
            case 'x': case 'X':
                array_sort_decending(array, &array_size);
                printf("Da sap xep theo chieu giam.\n");
                break;

/*----------Searching--*/
            case 't': case 'T':
                printf("Tim kiem: ");
                scanf("%d", &value);
                int res = array_search(array, &array_size, value);
                if (res == -1) {
                    printf("So %d khong co trong mang.\n", value);
                } else {
                    printf("So %d co trong mang.\n", value);
                }
                break;

/*--------- Find maximum--*/
            case 'a': case 'A':
                if (array_size == 0) {
                    printf("Failed: Mang chua co phan tu.\n");
                } else {
                    printf("So lon nhat: %d\n", array_max(array, &array_size));
                }
                break;

/*--------- Find minimum--*/
            case 'w': case 'W':
                if (array_size == 0) {
                    printf("Failed: Mang chua co phan tu.\n");
                } else {
                    printf("So nho nhat: %d\n", array_min(array, &array_size));
                }
                break;
            case 'e': case 'E':
                exit(0);
         }

    }
    return 0;
}

