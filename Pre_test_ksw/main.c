#define PROB 2
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#if PROB == 1
	typedef struct NODE {
		int coef;
		int exp;
		struct NODE* link;
	}Node;

	void addNode(Node** head, int coef, int exp);
	void printPoly(Node* p);
	void freePoly(Node* p);
	void addPoly(Node** c, Node* a, Node* b);

	int main() {
		Node* A = NULL, * B = NULL, * C = NULL;

		addNode(&A, 4, 3);
		addNode(&A, 3, 2);
		addNode(&A, 2, 1);

		printf("A(x) = ");
		printPoly(A);

		addNode(&B, 3, 4);
		addNode(&B, 2, 3);
		addNode(&B, 5, 1);
		addNode(&B, 1, 0);

		printf("B(x) = ");
		printPoly(B);

		return 0;
	}

#elif PROB == 2
	void reverse(char str[], int n);

	int main() {
		char str[100];
		int strSize = 0;
		gets(str, strSize);

		reverse(str, strSize);

		printf("%s", &str);

		return 0;
	}

	void reverse(char *str[], int n) {
		char temp[100];
		int k = 0;
		for (int i = n; i > -1; --i) {
			temp[k] = str[i];
			++k;
		}

		for (int i = 0; i < n; ++i) {
			str[i] = temp[i];
		}
	}

#elif PROB == 3
void bubble_sort(int *arr);

int main() {
	int arr[100];

	printf("정렬 전 데이터\n");
	for (int i = 0; i < 100; ++i){
		arr[i] = rand() % 100;
		printf("%d ", arr[i]);
	}

	bubble_sort(arr);

	printf("\n정렬 후 데이터\n");
	for (int i = 0; i < 100; ++i) {
		printf("%d ", arr[i]);
	}
	return 0;
}

void bubble_sort(int *arr) {
	for (int i = 0; i < 100; ++i) {
		for(int j = 0; j < 99 - i; ++j)
		if (arr[j] > arr[j + 1]) {
			int temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
		}
	}
}

#elif PROB == 4
int main() {
	printf("C = A X B 행렬 곱셈\n");

	int m1, m2, n1, n2 = 0;

	do
	{
		printf("A 행렬의 크기 : ");
		scanf("%d %d", &m1, &n1);

		printf("B 행렬의 크기 : ");
		scanf("%d %d", &m2, &n2);
	} while (n1 != m2);

	int a = malloc(m1 * n1 * sizeof(int));
	int b = malloc(m2 * n2 * sizeof(int));

	printf("행렬 A[%d][%d] 입력 : ", m1, n1);
	gets(a, sizeof(a));
	/*for (int i = 0; i < m1 * n1; ++i){
		scanf("%d", &a + i);
	}*/

	printf("행렬 B[%d][%d] 입력 : ", m2, n2);
	gets(b, sizeof(b));
	/*for (int i = 0; i < m2 * n2; ++i) {
		scanf("%d", &b + i);
	}*/

	for (int i = 0; i < m1 * n1; ++i) {
		printf("%d\t", a + i);
		if (i % n1 == 0)
			printf("\n");
	}
	printf("\n");

	for (int i = 0; i < m2 * n2; ++i) {
		printf("%d\t", b + i);
		if (i % n2 == 0)
			printf("\n");
	}
	printf("\n");

	free(a);
	free(b);

	return 0;
}
#elif PROB == 5
void compute_slope_and_y_intercept(int x1, int y1, int x2, int y2, float *a, float *y);

int main() {
	int x1, x2, y1, y2 = 0;
	float a, y;

	printf("두 점의 좌표를 순서대로 입력하세요. (x1, y1), (x2, y2) : ");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

	

	return 0;
}

void compute_slope_and_y_intercept(int x1, int y1, int x2, int y2, float *a, float *y) {

}

#elif PROB == 6
void swap(int* a, int* b);

int main() {
	int a = 10;
	int b = 20;

	printf("교환 전 a=%d, b=%d \n", a, b);

	swap(&a, &b);

	printf("교환 후 a=%d, b=%d \n", a, b);

	return 0;
}

void swap(int* a, int* b) {
	int temp = a;
	a = b;
	b = temp;
}

#elif PROB == 7
int main() {
	int hour;
	int min;
	int sec;
	printf("초 단위 시간 입력(정수형) : ");
	scanf("%d", &sec);
	
	hour = sec / 3600;
	min = (sec - (hour * 3600)) / 60;
	sec = (sec - (hour * 3600) - (min * 60));

	printf("변환된 형식은 %d:%d:%d 입니다.", hour, min, sec);

	return 0;
}

#endif