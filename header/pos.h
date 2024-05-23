//
// Created by 정지현 on 5/23/24.
//

#ifndef POS_H
#define POS_H

typedef struct pos {
	int x;
	int y;
} Position;

Position move_to(Position pos, int dir);

#endif