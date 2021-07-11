#include <stdio.h>

#define MAX_SIZE 100

int arr[MAX_SIZE];
int size = 0;

int main(int argc, char** argv) {
	//tutorial
	printf("___ CHUONG TRINH QUAN LY DAY SO BANG MANG ___\n");
	printf("Nhap \'c\' de tao mang so nguyen Neu da co mang thi clear data cua mang cu\nNhap \'p\' de in day Neu day chua co gia tri thi bao day trong\nNhap \'i\' de them 1 phan tu vao day\nNhap \'d\' de xoa 1 phan tu tai vi tri thu k Neu vi tri k khong chua gia tri thi bao ko co phan tu k\nNhap \'s\' de sap xep day so theo chieu tang dan\nNhap \'x\' de sap xep theo chieu giam \n");
	
	char ch;
	unsigned int i;
	while (1) {
		scanf("%c", &ch);
		switch (ch) {
			case 'c':
				printf("Tao mang:\n  Nhap do dai mang: ");
				scanf("%d", size);
				if (size > MAX_SIZE) {
					printf("\nToi da MAX_SIZE phan tu!");
					//break;
				}
				for ( i=0; i<size; i++) {
					printf("    Phan tu thu %u: ", i);
					scanf("%d", arr[i]);
				}
				break;
 		}
	}
	return 0;
}
