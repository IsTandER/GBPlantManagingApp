#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
	char data[4];
	struct listNode *link;
}listNode;

typedef struct {
	listNode * head;
}linkedList_h;

linkedList_h *createLinkedList_h(); //
void freeLinkedList_h(linkedList_h* L); //
void printList(linkedList_h *L); //
linkedList_h *insertFirstNode(linkedList_h *L, char*x); //
void insertMiddleNode(linkedList_h *L, listNode *pre, char *x); //
void insertLastNode(linkedList_h *L, char *x); //
listNode *searchNode (linkedList_h *L, char *x); //


int main() {
	linkedList_h *L;
	listNode *O;
	L= createLinkedList_h();
	L = insertFirstNode(L, "목");
	L = insertFirstNode(L, "금");
	L = insertFirstNode(L, "토");
	L = insertFirstNode(L, "주일");
	O = searchNode(L, "토");
	if(O) {
		insertMiddleNode(L, O, "중간");
	}
	insertLastNode(L, "공");
	printList(L);
	freeLinkedList_h(L);
	return 0;
}

linkedList_h *createLinkedList_h() {
	linkedList_h *L;
	L = (linkedList_h*)malloc(sizeof(linkedList_h));
	L->head = NULL;
	return L;
}

void printList(linkedList_h *L){
	listNode *p = L->head;
	while(p) {
		printf("%s ", p->data);
		p = p->link;
	}
}

linkedList_h *insertFirstNode(linkedList_h *L, char*x) {
	listNode *p;
	p = (listNode*)malloc(sizeof(listNode));
	strcpy(p->data, x);
	p->link = L->head;
	L->head = p;
	return L;
}

void insertLastNode(linkedList_h *L, char *x) {
	listNode *p;
	p = L->head;
	while(p) {
		if(p->link == NULL) {
			break;
		}
		p=p->link; 
	}
	listNode *n = (listNode*)malloc(sizeof(listNode));
	strcpy(n->data, x);
	n->link = NULL;
	p->link = n;
}

listNode *searchNode (linkedList_h *L, char *x) {
	listNode *p;
	p = L->head;
	while(p) {
		if(strcmp(p->data, x) == 0) {
			break;
		}
		p = p->link;
	}
	return p;
}

void insertMiddleNode(linkedList_h *L, listNode *pre, char *x) {
	listNode *p;
	p = (listNode*)malloc(sizeof(listNode));
	strcpy(p->data, x);
	p->link = pre->link;
	pre->link = p;
}

void freeLinkedList_h(linkedList_h* L) {
	listNode *p = L->head;
	while(p) {
		free(p);
		p = p->link;
	}
} 
