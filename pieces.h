#ifndef PIECES_H
#define PIECES_H

typedef struct square Square;

typedef struct piece {
	int type;
	int row;
	int col;
	Square** attacking;
} Piece;



#endif
