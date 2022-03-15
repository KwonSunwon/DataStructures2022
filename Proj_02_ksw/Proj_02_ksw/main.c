#include <chrono> 

#include "linkedlist.h"

int main() {
	int dataSize;

	printf("Data Size : ");
	scanf("%d", &dataSize);

	int start = time(NULL);
	
	node *head;

	srand(100);
	for(int i = 0; i < dataSize; ++i){
		addNode(&head, rand());
	}

	int end = time(NULL);

	printf("Linked List time cost : %d", end-start);
	

	return;
}