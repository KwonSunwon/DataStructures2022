// ���� 1���� �� �������� �Ҵ��ص���(�Է¹޴� �Լ� �ʿ� ����)
// �׳� ����, ������ �����ϸ��

// ���� 2��. MAX_NUMBER �� �����ؼ� ũ�� ����
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
	// ���� ��带 ����� ���̸� ��带 ��尡 ����Ű�� ������� ����?
	// ������ �� �������� ���� ���� ����� link�� �ּҰ��� �������ָ� ��µ� �״�� �ϸ��
	node* dummyNode = (node*)malloc(sizeof(node));
	node* head = dummyNode;
	node* cur = dummyNode;
	// �� ����Ʈ�� ���� ��ġ�� ������ ��
	// if a == b �׳� ���� �� c�� ���� �� a, b �� �� ���� ��ҷ� �̵�
	// if a > b a�� ���� c�� ���� �� a�� ���� ��ҷ� �̵�, b�� �״��
	// if a < b b�� ���� c�� ���� �� b�� ���� ��ҷ� �̵�, a�� �״��
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
	// a�� ���Ḯ��Ʈ���� b�� �� �������� ���ؼ� �� a�� ��Ҹ�ŭ�� ���׽� ���Ḯ��Ʈ�� �����
	// �� ���Ḯ��Ʈ���� ���� ���ؼ� ������ ����?
	// �ٵ� �̷��� �Ǹ� ���׽��� �ʹ� ũ�� �ʹ� ���� ���Ḯ��Ʈ�� �����ϰԵ�
}


#elif PROB == 2

#endif