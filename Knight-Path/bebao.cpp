#include "lib/var.h"
#include "lib/bebao.h"
#include "lib/status.h"

int bp[3][bpL],bpIdx[3][bpL],bpAmount[3],equipsword;
extern int key,inBp;
extern PIMAGE screen,bpImg[],escBG,gray,dropImg[],swordImg[],potionImg[],BpswordImg[];
extern Human player;

int extern mX,mY;

void bpScreen() {
    putimage(0, 0, screen);
    putimage_alphablend(NULL,escBG,0,0,0xC0,0,0,wid,hih);
    putimage_withalpha(NULL,bpImg[inBp-1],0,0);
    putBpItem(inBp-1);
    playerBlood(player.hp,player.fhp);
    putMoney();
    if (equipsword!=11) putimage_withalpha(NULL,BpswordImg[equipsword],498,168);
}

void bpListener() {
    if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
        if (key == key_esc||key == 101) {
            key = 0;
            inBp = 0;
        }
    }
    mousepos(&mX,&mY);
	if((mX >= 1144 && mX <= 1263) && (mY >= 141 && mY <= 250) && keystate(key_mouse_l)) {
        //第一層背包
        flushmouse();
        inBp = 1;
	}
    if((mX >= 1144 && mX <= 1263) && (mY >= 251 && mY <= 361) && keystate(key_mouse_l)) {
        //第二層背包
        flushmouse();
        inBp = 2;
	}
    if((mX >= 1144 && mX <= 1263) && (mY >= 362 && mY <= 473) && keystate(key_mouse_l)) {
        //第三層背包
        flushmouse();
        inBp = 3;
	}
    useBpItem();
}

void updateBp(int type,int idx, int tf) {
    if (tf==-1) {
        bpIdx[type][bpAmount[type]++] = idx;
        for (int i = 0;i<bpAmount[type]-1;i++) {
            for (int j = 0;j<bpAmount[type]-1-i;j++) {
                if (bpIdx[type][j]>bpIdx[type][j+1]) {
                    int tem = bpIdx[type][j];
                    bpIdx[type][j] = bpIdx[type][j+1];
                    bpIdx[type][j+1] = tem;
                }
            }
        }
    }
    else {
        for (int i = 0;i<bpAmount[type];i++) {
            if (bpIdx[type][i]==idx) {
                tf = i;
                break;
            }
        }
        for (int i = tf;i<bpAmount[type]-1;i++) {
            bpIdx[type][i] = bpIdx[type][i+1];
        }
        bpIdx[type][--bpAmount[type]]=0;
    }
}

void putBpItem(int idx) {
    for (int i = 0;i<bpAmount[idx];i++) {
        int x,y;
        i > 4 ? x = 477 : x = 0;
        i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
        putimage_alphablend(NULL,gray,180+x,y-6,0x70,0,0,442,45);
        if (idx == 0) {
            putimage_withalpha(NULL,dropImg[bpIdx[idx][i]],216+x-getwidth(dropImg[bpIdx[idx][i]])/2,y);
            xyprintf(401+x,y+getheight(dropImg[bpIdx[idx][i]])/2,"%s",dropName[bpIdx[idx][i]]);
            xyprintf(586+x,y+getheight(dropImg[bpIdx[idx][i]])/2,"%d",bp[idx][bpIdx[idx][i]]);
        }
        else if (idx == 1){
            putimage_withalpha(NULL,swordImg[bpIdx[idx][i]],216+x-getwidth(swordImg[bpIdx[idx][i]])/2,y);
            xyprintf(401+x,y+getheight(swordImg[bpIdx[idx][i]])/2,"%s",swordName[bpIdx[idx][i]]);
        }
        else if (idx == 2){
            putimage_withalpha(NULL,potionImg[bpIdx[idx][i]],216+x-getwidth(potionImg[bpIdx[idx][i]])/2,y);
            xyprintf(401+x,y+getheight(potionImg[bpIdx[idx][i]])/2,"%s",potionName[bpIdx[idx][i]]);
        }
    }
}

void useBpItem() {
    if (inBp == 2 ||inBp == 3) {
        flushmouse();
        mousepos(&mX,&mY);
        for (int i=0;i<bpAmount[inBp-1];i++){
            int x,y;
            i > 4 ? x = 477 : x = 0;
            i > 4 ? y = 60*(i-5)+320 : y = 60*i+320;
            if ((mX >= 180+x && mX <= 180+x+442) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                //按物品
                PIMAGE choose = newimage();
                PIMAGE equip= newimage();
                PIMAGE use= newimage();
                PIMAGE canceluse= newimage();
                getimage(choose, "images\\menu\\choose.png",0,0);
                getimage(equip, "images\\menu\\equip.png",0,0);
                getimage(use, "images\\menu\\use.png",0,0);
                getimage(canceluse, "images\\menu\\canceluse.png",0,0);
                for (;is_run();delay_fps(60)) {
                    flushmouse();
                    mousepos(&mX,&mY);
                    cleardevice();
                    bpScreen();
                    putimage_withalpha(NULL,choose,180+x,y-6);
                    if (inBp == 2) {
                        putimage_alphablend(NULL,equip,180+x+442+10,y-6,0xE0,0,0,71,45);
                        putimage_alphablend(NULL,canceluse,180+x+442+10,y+45+4,0xE0,0,0,71,45);
                        if ((mX >= 180+x+442+10 && mX <= 180+x+442+10+71) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                            //按裝備
                            for(;is_run();delay_fps(60)) {
                                if (keystate(key_mouse_l)==0) break;
                            }
                            equipsword=bpIdx[1][i];
                            if(bpIdx[1][i] == 0) player.damage=20;
                            else if (bpIdx[1][i] == 1) player.damage=30;
                            else if (bpIdx[1][i] == 2) player.damage=15;
                            break;
                        }
                        if ((mX >= 180+x+442+10 && mX <= 180+x+442+10+71) && (mY >= y+45+4 && mY <= y+45+4+45) && keystate(key_mouse_l)) {
                            //按取消
                            for (;is_run();delay_fps(60)) {
                                if (keystate(key_mouse_l)==0) break;
                            }
                            break;
                        }
                    }
                    if (inBp == 3) {
                        putimage_alphablend(NULL,use,180+x+442+10,y-6,0xE0,0,0,71,45);
                        putimage_alphablend(NULL,canceluse,180+x+442+10,y+45+4,0xE0,0,0,71,45);
                        if ((mX >= 180+x+442+10 && mX <= 180+x+442+10+71) && (mY >= y-6 && mY <= y-6+45) && keystate(key_mouse_l)) {
                            //按使用
                            for (;is_run();delay_fps(60)) {
                                if (keystate(key_mouse_l)==0) break;
                            }
                            if (bpIdx[2][i] == 0) {
                                if (player.hp+2>10) player.hp=10;
                                else player.hp+=2;
                            } else {
                                if (player.hp+5>10) player.hp=10;
                                else player.hp+=5;
                            }
                            updateBp(2,i,1);
                            break;
                        }
                        if ((mX >= 180+x+442+10 && mX <= 180+x+442+10+71) && (mY >= y+45+4 && mY <= y+45+4+45) && keystate(key_mouse_l)) {
                            //按取消
                            for (;is_run();delay_fps(60)) {
                                if (keystate(key_mouse_l)==0) break;
                            }
                            break;
                        }
                    }
                }
                delimage(choose);
                delimage(equip);
                delimage(use);
                delimage(canceluse);
            }
        }
    }
}