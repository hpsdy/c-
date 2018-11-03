#include<cstdio>
void print(int *c, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d:%d:%p\n", i, c[i], c + i);
	}
}
int main(){
	int a[][3] = {{1,2,3}};
	int (*b)[3] = a;
	int *c = (int*)a;
	int *d = a[0];
	printf("%p\n:%p\n", c, d);
	int *arr1 = new int[6]();
	arr1[0] = 100;
	arr1[1] = 200;
	int *arr2 = new int[1]();
	arr1[2] = 300;
	arr1[3] = 400;
	arr1[4] = 500;
	arr1[5] = 600;
	arr1[6] = 700;
	arr1[7] = 800;
	arr1[8] = 900;
	arr1[9] = 100;
	arr1[10] = 110;
	arr1[11] = 120;

	//arr2[0] = 99;
	//arr2[1] = 88;
	//arr1[2] = 77; 
	print(arr1, 12);
	print(arr2, 1);
	return 0;
}
