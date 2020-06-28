typedef struct node {
	struct node* prev;
	void* data;
	struct node* next;
} Node;

void push(Node* head, void* data);
void insert(Node* prev, void* data);
