#include <stdlib.h>
#include "pieces.h"
#include "assets.h"
#include "consts.h"

Piece* NewPiece(int id, int side) {
	Piece* res = (Piece*) malloc(sizeof(Piece));
	res->id = id;
	res->side = side;
	res->state = UNMOVED;
	res->attacking = NewHead();
	return res;
}

void DrawPiece(Piece* p, float x, float y) {
	Vector2 pos = {x, y};
	Rectangle rect = {SQUARE_SIZE * p->id, SQUARE_SIZE * p->side, SQUARE_SIZE, SQUARE_SIZE};
	DrawTextureRec(spriteSheet, rect, pos, WHITE);
}

void DrawPieceCenter(Piece* p, float x, float y) {
	float posX = x - SQUARE_SIZE / 2;
	float posY = y - SQUARE_SIZE / 2;
	DrawPiece(p, posX, posY);
}

void DestroyPiece(Piece* p) {
	if (p) {
		DestroyList(p->attacking);
		free(p);
	}
}
