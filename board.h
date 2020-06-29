#include "linked_list.h"
#include "raylib.h"

typedef struct piece Piece;

typedef struct square {
	float x; // Actual screen x 
	float y; // Actual screen y
	Color c;
	Node* attackers;
	Piece* resident;
} Square;

void InitBoard(void);
void DrawBoard(void);

