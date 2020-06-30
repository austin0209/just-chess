#include <stdlib.h>
#include "pieces.h"
#include "assets.h"
#include "consts.h"

Piece* NewPiece(int id, int side) {
	Piece* res = (Piece*) malloc(sizeof(Piece));
	res->id = id;
	res->side = side;
	res->attacking = NewHead();
	return res;
}

void DrawPiece(Piece* p, float x, float y) {
	Vector2 pos = {x, y};
	Rectangle rect = {SQUARE_SIZE * p->id, SQUARE_SIZE * p->side, SQUARE_SIZE, SQUARE_SIZE};
	DrawTextureRec(spriteSheet, rect, pos, WHITE);
}
