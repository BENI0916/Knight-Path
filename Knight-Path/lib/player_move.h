#ifndef PLAYER_MOVE_H
#define PLAYER_MOVE_H

void move(int speed);

void player_walk(int val);

void atk(int val);

void jump();

int player_move_check(char dir, int speed);

void dash(int val);

void player_skill_0(int val);

void player_skill_1(int val);

#endif
