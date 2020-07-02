#ifndef LLIST_H
#define LLIST_H

typedef struct node {
	struct node* prev;
	void* data;
	struct node* next;
} Node;

Node* NewHead(void); // Return a new head.
void Push(Node* head, void* data); // Add new node with data to back of list.
void* Pop(Node* head); // Remove node at back of list (returns and does not free data).
void* Remove(Node*); // Remove the node after prevNode.
void Empty(Node* head); // Empties list and clears internal data.
int IsEmpty(Node* head); // Returns true if list is empty.
int IsHead(Node* head); // Returns true if node is a head.
int Contains(Node*, void*); // Returns true if in list
void DestroyList(Node* head); // Frees memory for nodes AND internal data.

#endif
