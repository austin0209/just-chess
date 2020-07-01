#include "linked_list.h"
#include "raylib.h"

typedef struct piece Piece;

typedef struct square {
	int row;
	int col;
	Color c;
	Node* attackers;
	Piece* resident;
} Square;

void InitBoard(void);
void DrawBoard(void);
Square* GetSquareAt(int, int);

