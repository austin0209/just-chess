#include "raylib.h"
#include "linked_list.h"

typedef struct square Square;

typedef struct piece {
	int id;
	int side;
	int row;
	int col;
	Node* attacking;
} Piece;

Piece* NewPiece(int, int, int, int);
void DrawPiece(Piece*);
