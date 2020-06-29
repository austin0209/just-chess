
typedef struct node {
	struct node* prev;
	void* data;
	struct node* next;
} Node;

Node* NewHead(void); // Return a new head.
void Push(Node* head, void* data); // Add new node with data to back of list.
void* Pop(Node* head); // Remove node at back of list (returns and does not free data).
void* Remove(Node* prevNode); // Remove the node after prevNode.
int IsEmpty(Node* head); // Returns true if list is empty.
int IsHead(Node* head); // Returns true if node is a head.
void DestroyList(Node* head); // Frees memory for nodes AND internal data.

