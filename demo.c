// examples for using two-dimensional arrays
#include <stdio.h>

void change(int *a,int m, int n){
	int i, j; 
						 
	for(i = 0; i < n; i++) { 
		for(j = 0; j < m; j++) {
			*(a + i*m + j) = 1;
		}
	} 
}

void print(int a[4][4]){
	int i, j; 
							 
	for(i = 0; i < 4; i++) { 
		for(j = 0; j < 4; j++) {
			printf("%d ",a[i][j]);
		}
		printf("\n");
	} 
	printf("-------\n");
}

int main(int argc, char *argv[]) {
	int a[4][4];
	int i,j;
	
	for (i=0;i<4;i++) {
		for (j=0;j<4;j++) {
			a[i][j] = i * j;
		}
	}
	
	print(a);
	
	change(&a[0][0],4,4);
	
	print(a);
}