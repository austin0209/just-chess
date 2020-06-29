#ifndef BOARD_H
#define BOARD_H
#include "linked_list.h"
#include "raylib.h"

typedef struct piece Piece;

typedef struct square {
	int x; // Actual screen x 
	int y; // Actual screen y
	Color c;
	Node* attackers;
	Piece* resident;
} Square;

void InitBoard(void);
void DrawBoard(void);

#endif
