#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

Node* NewHead() {
	Node* res = (Node*) malloc(sizeof(Node));
	res->data = NULL;
	res->next = res;
	res->prev = res;
	return res;
}

void Push(Node* head, void* data) {
	assert(IsHead(head));

	Node* newLast = (Node*) malloc(sizeof(Node));
	Node* oldLast = head->prev;

	newLast->data = data;
	newLast->prev = oldLast;
	newLast->next = head;

	oldLast->next = newLast;
	head->prev = newLast;
}

void* Pop(Node* head) {
	assert(IsHead(head) && !IsEmpty(head));
	return Remove(head->prev->prev);
}

void* Remove(Node* prevNode) {
	assert(prevNode->next != prevNode);

	Node* oldNode = prevNode->next;
	prevNode->next->next->prev = prevNode;
	prevNode->next = prevNode->next->next;

	void* oldData = oldNode->data;
	free(oldNode);
	return oldData;
}

int IsEmpty(Node* head) {
	assert(IsHead(head));
	return head->next == head;
}

int IsHead(Node* node) {
	return node != NULL && node->data == NULL;
}

void DestroyList(Node* head) {
	if (IsEmpty(head)) {
		free(head);
		return;
	}

	Node* curr = head->next;
	while (curr != head) {
		free(curr->data);
		curr = curr->next;
		free(curr);
	}

	free(head);
}
