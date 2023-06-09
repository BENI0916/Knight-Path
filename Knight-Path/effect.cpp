#include "lib/var.h"
#include "lib/effect.h"

extern PIMAGE screen;

int putLogo() {
    PIMAGE logo = newimage();
    getimage(logo,"images\\bg\\logo.png",0,0);
    for (int i = 0;i<32;delay_fps(30)) {i++;}
    for (int i = 0;i<32;delay_fps(30)) {
		putimage_alphablend(NULL,logo,0,0,0x20,0,0,wid,hih);
		i++;
	}
    for (int i = 0;i<16;delay_fps(30)) {i++;}
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    for (int i = 0;i<32;delay_fps(30)) {
		putimage_alphablend(NULL,blk,0,0,0x20,0,0,wid,hih);
		i++;
	}
    delimage(logo);
    delimage(blk);
    flushkey();
    flushmouse();
    return 0;
}

int fadeIn() {
    cleardevice();
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,screen,0,0,0x30,0,0,wid,hih);
		i++;
	}
    flushkey();
    flushmouse();
    return 0;
}

int fadeOut() {
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    putimage(0,0,screen);
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,blk,0,0,0x30,0,0,wid,hih);
		i++;
	}
    delimage(blk);
    flushkey();
    flushmouse();
    return 0;
}

int flashOut() {
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    for (int j = 0;j<2;j++) {
        putimage(0,0,screen);
        for (int i = 0;i<8;delay_fps(30)) {
		    putimage_alphablend(NULL,blk,0,0,0x60,0,0,wid,hih);
		    i++;
	    }
        cleardevice();
        for (int i = 0;i<8;delay_fps(30)) {
		    putimage_alphablend(NULL,screen,0,0,0x60,0,0,wid,hih);
		    i++;
	    }
    }
    fadeOut();
    delimage(blk);
    flushkey();
    flushmouse();
    return 0;
}

int ending() {
	mciSendString (TEXT("open audio\\bgm\\end.mp3 alias endbgm"), NULL,0,NULL);
	mciSendString (TEXT("play endbgm"), NULL,0,NULL);
    cleardevice();
    PIMAGE end = newimage();
    PIMAGE ending = newimage();
    PIMAGE blk = newimage();
    getimage(blk,"images\\bg\\black.png",0,0);
    getimage(end,"images\\bg\\end.png",0,0);
    getimage(ending,"images\\menu\\ending.png",0,0);
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,end,0,0,0x30,0,0,wid,hih);
		i++;
	}
    for (int i = 0;i<2840;delay_fps(71)) {
        cleardevice();
        putimage(0,0,end);
        putimage_withalpha(NULL,ending,0,720-i);
        i++;
    }
    for (int i = 0;i<64;delay_fps(30)) {
		putimage_alphablend(NULL,blk,0,0,0xd,0,0,wid,hih);
		i++;
	}
    delimage(end);
    delimage(blk);
    delimage(ending);
    flushkey();
    flushmouse();
    mciSendString (TEXT("stop endbgm"), NULL,0,NULL);
	mciSendString (TEXT("close endbgm"), NULL,0,NULL);
    return 0;
}