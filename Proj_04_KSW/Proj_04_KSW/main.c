// 문제 1번에 값 정적으로 할당해도됨(입력받는 함수 필요 없음)
// 그냥 덧셈, 곱셈만 구현하면됨

// 문제 2번. MAX_NUMBER 로 정의해서 크기 결정
// fread, fwrite

#include <stdio.h>
#include <stdlib.h>

#define PROB 1

#if PROB == 1

typedef struct PolyNode {
	int coef;
	int exp;
	struct PolyNode* link;
}node;

node* addPoly(node*, node*);
node* mulPoly(node*, node*);

int main()
{

}

node* addPoly(node* a, node* b)
{
	// 더미 노드를 만들고 더미를 노드를 헤드가 가리키는 방식으로 구현?
	// 마지막 값 리턴해줄 때는 더미 노드의 link의 주소값을 리턴해주면 출력도 그대로 하면됨
	node* dummyNode = (node*)malloc(sizeof(node));
	node* head = dummyNode;
	node* cur = dummyNode;
	// 두 리스트의 현재 위치의 차수를 비교
	// if a == b 그냥 더한 후 c에 저장 후 a, b 둘 다 다음 요소로 이동
	// if a > b a의 값을 c에 저장 후 a는 다음 요소로 이동, b는 그대로
	// if a < b b의 값을 c에 저장 후 b는 다음 요소로 이동, a는 그대로
	while (a != NULL && b != NULL) {
		if (a->exp == b->exp) {
			node* newNode = (node*)malloc(sizeof(node));
			newNode->coef = a->coef + b->coef;
			newNode->exp = a->exp;
			a = a->link;
			b = b->link;
			cur->link = newNode;
			cur = cur->link;
		}
		else if (a->exp > b->exp) {
			node* newNode = (node*)malloc(sizeof(node));
			newNode->coef = a->coef;
			newNode->exp = a->exp;
			a = a->link;
			cur->link = newNode;
			cur = cur->link;
		}
		else {
			node* newNode = (node*)malloc(sizeof(node));
			newNode->coef = b->coef;
			newNode->exp = b->exp;
			b = b->link;
			cur->link = newNode;
			cur = cur->link;
		}
	}
	return head;
}

node* mulPoly(node* a, node* b) {
	// a의 연결리스트마다 b의 각 차수들을 곱해서 총 a의 요소만큼의 다항식 연결리스트를 만들고
	// 그 연결리스트들을 전부 더해서 최종값 구함?
	// 근데 이렇게 되면 다항식이 너무 크면 너무 많은 연결리스트를 생성하게됨
}


#elif PROB == 2

#endif