#ifndef VAR_H
#define VAR_H

//ï¿½ï¿½ï¿½ï¿½ï¿½`ï¿½ï¿½ï¿½xï¿½sï¿½ï¿½
#include <ege.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <graphics.h>
#pragma comment(lib, "Winmm.lib")

const int hih = 720; //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
const int wid = 1280; //ï¿½ï¿½ï¿½ï¿½ï¿½e
const int bpL = 10;
const char dropName[][50] {
	"·s¥x¹ô",
	"S¯Å­¹§÷-¨ß¦×",
	"ÃZ§Z¥Û",
	"¶ÂÂ`¥Û"
};
const char swordName[][20] = {"¥Û¼C", "ÅK¼C", "³½"};
const char potionName[][20] = {"¦^´_ÃÄ¤ô", "¤j¦^´_ÃÄ¤ô"};

// ï¿½ï¿½ï¿½aï¿½ï¿½ï¿½ï¿½ï¿½c 
typedef struct 
{
	int x;	// x ï¿½yï¿½ï¿½ 
	int y;	// y ï¿½yï¿½ï¿½  
	int hp;	// ï¿½ï¿½q
	int fhp;
	int damage; // ï¿½ï¿½Ä¤Hï¿½yï¿½ï¿½ï¿½ï¿½ï¿½Ë®`  
	int atked;// ï¿½Pï¿½wï¿½Oï¿½_ï¿½ï¿½ï¿½yï¿½ï¿½ï¿½Ë®` 
	char dir;// ï¿½Hï¿½ï¿½ï¿½ï¿½ï¿½Âªï¿½ï¿½ï¿½V 
	int output_idx; // ï¿½Î©ï¿½ï¿½xï¿½sï¿½nï¿½ï¿½Xï¿½ï¿½ï¿½Ï¤ï¿½ï¿½sï¿½ï¿½ 
	PIMAGE *player_img, *player_msk;  //ï¿½ï¿½ï¿½ï¿½ï¿½xï¿½sï¿½Ï¤ï¿½ 
	int high;
	int width;
	int power;// ï¿½ï¿½ï¿½hï¿½Ä¤Hï¿½ï¿½ï¿½Zï¿½ï¿½ 
	int atk_type; // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 
}Human;

typedef struct 
{
	int x;
	int y;
	int hp;
	int fhp;
	int damage;
	char dir;
	int output_idx;
	PIMAGE *enemy_img, *enemy_msk;
	int high;
	int width;
	int power;
	int speed;
	int atk_0_cnt;
	int atk_1_cnt;
}Monster;

typedef struct 
{
	int cnt;
	int output_idx;
	int printed;
	PIMAGE *loading_img;
}Animate;


typedef struct 
{
	int x;
	int y;
	int output_idx;
	int status;
	PIMAGE *skill_img, *skill_msk;
	int high;
	int width;
	int power;
}Bullet;

#endif
