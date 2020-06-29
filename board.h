#ifndef BOARD_H
#define BOARD_H
#include "linked_list.h"

typedef struct piece Piece;

typedef struct square {
	int x; // Actual screen x 
	int y; // Actual screen y
	Node* attackers;
	Piece* resident;
} Square;

int DrawBoard(void);

#endif
