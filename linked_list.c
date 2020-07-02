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

void* Remove(Node* toRemove) {
	toRemove->prev->next = toRemove->next;
	toRemove->next->prev = toRemove->prev;
	void* oldData = toRemove->data;
	free(toRemove);
	return oldData;
}

void Empty(Node* head) {
	assert(IsHead(head));
	while (!IsEmpty(head)) {
		Remove(head->next);
	}
}

int IsEmpty(Node* head) {
	assert(IsHead(head));
	return head->next == head;
}

int IsHead(Node* node) {
	return node != NULL && node->data == NULL;
}

int Contains(Node* head, void* data) {
	Node* curr = head->next;
	while (curr != head) {
		if (curr->data == data) return 1;
		curr = curr->next;
	}
	return 0;
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
