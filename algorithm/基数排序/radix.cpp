#include<cstdio>
//https://www.cnblogs.com/skywang12345/p/3603669.html#a42

int max(int a[], int n) {
	int tmp = 0;
	for(int i = 0; i < n; ++i) {
		if (a[i] > tmp){
			tmp = a[i];
		}
	}
	return tmp;
}
void p(int a[], int n) {
	printf("+++++begin+++++\n");
	for (int i = 0; i < n; ++i) {
		printf("%d\n", a[i]);
	}
	printf("+++++end+++++\n\n");
}
void countSort(int a[], int n, int exp){
	int i,output[n] = {0};
	int buckets[10] = {0};
	for (i = 0; i < n; ++i) {
		++buckets[(a[i] / exp) % 10];
	}
	for (i = 1; i < 10; ++i) {
		buckets[i] += buckets[i-1];
	}
	for (i = n - 1; i >= 0; --i) {
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		--buckets[(a[i] / exp) % 10];
	}
	for (i = 0; i < n; ++i) {
		a[i] = output[i];
	}
	p(a, n);
}

void radixSort(int a[], int n) {
	int mx = max(a, n);
	printf("n:%d,max:%d\n", n, mx);
	int exp = 1;
	for (exp; mx / exp > 0; exp *= 10) {
		countSort(a, n, exp);
	}
}

int main() {
	int a[] = {44,12,22,90,189,1,888,123,4,789,999,0,654,34,67};
	int len = sizeof(a)/sizeof(int);
	radixSort(a, len); 
	p(a, len);
	return 0;
}


