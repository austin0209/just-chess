#include <stdlib.h>
#include "pieces.h"
#include "assets.h"
#include "consts.h"

Piece* NewPiece(int id, int side, int row, int col) {
	Piece* res = (Piece*) malloc(sizeof(Piece));
	res->id = id;
	res->side = side;
	res->row = row;
	res->col = col;
	res->attacking = NewHead();
	return res;
}

void DrawPiece(Piece* p) {
	Vector2 pos = {p->col * SQUARE_SIZE, p->row * SQUARE_SIZE};
	Rectangle rect = {SQUARE_SIZE * p->id, SQUARE_SIZE * p->side, SQUARE_SIZE, SQUARE_SIZE};
	DrawTextureRec(spriteSheet, rect, pos, WHITE);
}
