#include "raylib.h"
#include "linked_list.h"

typedef struct square Square;

typedef struct piece {
	int id;
	int side;
	Node* attacking;
} Piece;

Piece* NewPiece(int, int);
void DrawPiece(Piece*, float, float);
