#include "lib/var.h"
#include "lib/enemy_move3D.h"
#include "lib/status.h"
#include "lib/event.h"

extern int victory;
extern Monster monster;
extern Human player;
int cnt,atk;

void enemyMove(int idx) {
    if (idx==1) {   //雜燴兔
        if (monster.x>player.x&&monster.x-player.x<=176&&player.dir=='d') {
            monster.dir='a';
            monster.x -= 20;
        } 
        else if (monster.x>player.x) {
            monster.dir='d';
            if (monster.x<1179) {
                monster.x += 10;
            }
        }
        else if (monster.x<=player.x&&player.x-monster.x<=201&&player.dir=='a') {
            monster.dir='d';
            monster.x += 20;
        } 
        else if (monster.x<=player.x) {
            monster.dir='a';
            if (monster.x>0) {
                monster.x -= 10;
            }
        }
        cnt++;
        if (monster.dir=='d') {
            if (cnt/10) {
                monster.output_idx = 2;
                cnt = 0;
            }
            else if (cnt/5) {
                monster.output_idx = 3;
            }
        }
        else {
            if (cnt/10) {
                monster.output_idx = 0;
                cnt = 0;
            }
            else if (cnt/5) {
                monster.output_idx = 1;
            }
        }
    }
    else if (idx==2) {
        int table[] = {0,0,-1,0,0,1};
        int atkTable[] = {0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        int walkTable[] ={0,0,1,0,0,1};
        if (monster.x+monster.width/2>player.x+player.width/2) monster.dir='a';
        else monster.dir = 'd';
        if (atk!=0) {
            if (atk>0) {
                monster.output_idx = 1 + atkTable[atk/2];
                if (atk==152) {
                    if (!(monster.x>player.x+player.width)&&!(monster.x+50<player.x)) player.hp-monster.damage<0 ? player.hp = 0 : player.hp -= monster.damage;
                }
                if ((atk+1)/2>=104) atk = -1;
                atk++;
            }
            else if (atk<0) {
                monster.output_idx = 7 + atkTable[atk/2*-1];
                //printf("%d %d %d %d\n",monster.x+197,player.x+player.width,monster.x+monster.width,player.x);
                if (atk==-152) {
                    if (!(monster.x+138>player.x+player.width)&&!(monster.x+monster.width<player.x)) player.hp-monster.damage<0 ? player.hp = 0 : player.hp -= monster.damage;
                }
                if ((atk*-1+1)/2>=104) atk = 1;
                atk--;
            }         
        }
        else if (monster.x>player.x+player.width-10) {
            cnt++;
            if (cnt/15>=6) cnt = 0;
            monster.x-= walkTable[cnt/15];
            monster.output_idx = 1 + table[cnt/15];
        }
        else if (monster.x+monster.width<player.x+10) {
            cnt++;
            if (cnt/15>=6) cnt = 0;
            monster.x+= walkTable[cnt/15];
            monster.output_idx = 7 + table[cnt/15];
        }
        else {
            if (monster.dir=='a') {
                monster.output_idx = 1;
                atk = 1;
            }
            else {
                monster.output_idx = 7;
                atk = -1;
            }
        }
    }
}

void putEnemy(int idx) {
    enemyMove(idx);
    if (monster.hp>0) {
        putimage_withalpha(NULL,monster.enemy_img[monster.output_idx],monster.x,monster.y);
        monBlood(monster.hp,monster.fhp);
    }
    else {
        mciSendString (TEXT("open audio\\bgm\\vic.mp3 alias vic"), NULL,0,NULL);
	    mciSendString (TEXT("play vic"), NULL,0,NULL);
        int i = 0;
        if (idx==1) i=4;
        if (idx==2) i=12;
        for (i;i>0;i--) {
            delimage(monster.enemy_img[i-1]);
        }
        free(monster.enemy_img);
        mciSendString (TEXT("stop battlemusic"), NULL,0,NULL);
        mciSendString (TEXT("close battlemusic"), NULL,0,NULL);
        victory = 1;
        flushkey();
        drop(idx);
    }
}