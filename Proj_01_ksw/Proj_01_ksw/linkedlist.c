#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void addNode(node** head, int id, char name[]) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->id = id;
	strcpy(newNode->name, name);
	if (head == NULL) {

	}
}
node* searchNode(node* p, int id) {

}
node* deleteNode(node* p, int id) {

}
void printNode(node* p) {

}
void freeAllNode(node* p) {

}