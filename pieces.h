#include "raylib.h"
#include "linked_list.h"

typedef struct square Square;

typedef struct piece {
	int id;
	int side;
	int state;
	Node* attacking;
} Piece;

Piece* NewPiece(int, int);
void DrawPiece(Piece*, float, float);
void DrawPieceCenter(Piece*, float, float);

// TODO: need a function to free pieces so that linked list is freed
