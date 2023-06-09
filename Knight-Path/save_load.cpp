#include "lib/save_load.h"
#include "lib/var.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "lib/output_img.h"
#include "lib/effect.h"

extern Monster enemy[3];
extern Human player;
extern int bgX,bgY,enemy_num,bp[3][bpL],bpIdx[3][bpL],bpAmount[3],inMaz,folder,mX,mY,equipsword,key,esc,fade,open;
extern char BgName[];
extern PIMAGE CellImg, SavButImg, EmpButImg;
int IsEmpty1,IsEmpty2,IsEmpty3,IsPress1,IsPress2,IsPress3,IsPrintButton;
FILE *fptr;

//概念:
//右下角資料夾圖案
//點進去會顯示三個儲存格(顯示 empty or 有存檔)，且有 delete,back 按鈕(分別執行delete,back)
//點儲存格，會出現 save,load 按鈕(分別執行save,load)

//新遊戲 初始化數值
void newGame() {
	sprintf(BgName,"%s","images\\bg\\home2.png");//當前背景
	inMaz = 0;//是否在迷宮內
	bgX=20,bgY=-20;//背景位置
	//背包相關
	bpAmount[0] = 0;
	bpAmount[1] = 0;
	bpAmount[2] = 0;
	equipsword = 11;
	for (int i = 0;i<bpL;i++) {//清空背包
		bp[0][i] = 0;
		bp[1][i] = 0;
		bp[2][i] = 0;
		bpIdx[0][i] = 0;
		bpIdx[1][i] = 0;
		bpIdx[2][i] = 0;
	}
	player.output_idx = 27;//玩家圖片編號
	player.hp = 10;//血量
	player.fhp = 10;//最大血量
	player.damage = 5;//傷害
	enemy_num = -1;//BOSS數
}

void SaveLoadScreen()
{
    putimage_withalpha(NULL,CellImg,200,160);
	PrintCellinfo();
}

void PrintCellinfo()
{
	//判斷儲存格是否為空，並印出字體
	if(IsEmpty1 == 0)
	{
  		outtextxy(393,366,"EMPTY");
	}
	else if(IsEmpty1 == 1)
	{
		outtextxy(393,366,"SAVED");
	}
	
	if(IsEmpty2 == 0)
	{
  		outtextxy(645,366,"EMPTY");
	}
	else if(IsEmpty2 == 1)
	{
		outtextxy(645,366,"SAVED");
	}
	
	if(IsEmpty3 == 0)
	{
  		outtextxy(895,366,"EMPTY");
	}
	else if(IsEmpty3 == 1)
	{
		outtextxy(895,366,"SAVED");
	}
	
}

void SaveLoadlistener()
{
	if (kbhit()) { // 檢測是否有鍵盤輸入 
		key = getch();
    }
	mousepos(&mX,&mY);
	
	//save:305 538 491 590
	//load:555 543 741 593
	//delete:808 545 991 585
	
	if(IsPrintButton == 2) {
		//按empty儲存格
		if((mX >= 305 && mX <= 491) && (mY >= 538 && mY <= 590) && keystate(key_mouse_l)){
			for(;is_run();delay_fps(60)){
				if(keystate(key_mouse_l) == 0) break;
			}
			flushmouse();
			save();
			IsPress1 = 0;
			IsPress2 = 0;
			IsPress3 = 0;
			IsPrintButton = 0;
		}
	}
	if(IsPrintButton == 1) {
		//按saved儲存格
		if((mX >= 305 && mX <= 491) && (mY >= 538 && mY <= 590) && keystate(key_mouse_l)){
			//按save
			for(;is_run();delay_fps(60)){
				if(keystate(key_mouse_l) == 0) break;
			}
			flushmouse();
			save();
			IsPress1 = 0;
			IsPress2 = 0;
			IsPress3 = 0;
			IsPrintButton = 0;
		}
		else if((mX >= 555 && mX <= 741) && (mY >= 543 && mY <= 593) && keystate(key_mouse_l)){
			//按load
			for(;is_run();delay_fps(60)){
				if(keystate(key_mouse_l) == 0) break;
			}
			flushmouse();
			load();
			IsPress1 = 0;
			IsPress2 = 0;
			IsPress3 = 0;
			IsPrintButton = 0;
		}
		else if((mX >= 808 && mX <= 991) && (mY >= 545 && mY <= 590) && keystate(key_mouse_l)){
			//按delete
			for(;is_run();delay_fps(60)){
				if(keystate(key_mouse_l) == 0) break;
			}
			flushmouse();
			del();
			IsPress1 = 0;
			IsPress2 = 0;
			IsPress3 = 0;
			IsPrintButton = 0;
		}
		
	}
		
	if((mX >= 294 && mX <= 490) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第一個處存格
		for(;is_run();delay_fps(60)){
			if(keystate(key_mouse_l) == 0) break;
		}
		flushmouse();
		IsPress1 = 1;
		IsPress2 = 0;
		IsPress3 = 0;
	}
	else if((mX >= 546 && mX <= 740) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第二個處存格
		for(;is_run();delay_fps(60)){
			if(keystate(key_mouse_l) == 0) break;
		}
		flushmouse();
		IsPress1 = 0;
		IsPress2 = 1;
		IsPress3 = 0;
	}
	else if((mX >= 801 && mX <= 995) && (mY >= 276 && mY <= 447) && keystate(key_mouse_l))
	{
		//按第三個處存格
		for(;is_run();delay_fps(60)){
			if(keystate(key_mouse_l) == 0) break;
		}
		flushmouse();
		IsPress1 = 0;
		IsPress2 = 0;
		IsPress3 = 1;
	}
	else if(((mX >= 1176 && mX <= 1238) && (mY >= 595 && mY <= 638) && keystate(key_mouse_l))||key==key_esc)
	{
		//按第二次資料夾消除畫面
		for(;is_run();delay_fps(60)){
			if(keystate(key_mouse_l) == 0) break;
		}
		flushmouse();
		flushkey();
		folder = 0;
		IsPress1 = 0;
		IsPress2 = 0;
		IsPress3 = 0;
		IsPrintButton = 0;
		key = 0;
	}
	else if(IsPress1==1 || IsPress2==1 || IsPress3==1){
		//點了其中一個處存格
		for(;is_run();delay_fps(60)){
			if(keystate(key_mouse_l) == 0) break;
		}
		//顯示按鈕
		if(IsPress1==1 && IsEmpty1==1) {
			putimage_withalpha(NULL,SavButImg,185,160);
			IsPrintButton = 1;
		}
		else if(IsPress2==1 && IsEmpty2==1) {
			putimage_withalpha(NULL,SavButImg,185,160);
			IsPrintButton = 1;
		}
		else if(IsPress3==1 && IsEmpty3==1) {
			putimage_withalpha(NULL,SavButImg,185,160);
			IsPrintButton = 1;
		}
		else if(IsPress1==1 && IsEmpty1==0) {
			putimage_withalpha(NULL,EmpButImg,185,160);
			IsPrintButton = 2;
		}
		else if(IsPress2==1 && IsEmpty2==0) {
			putimage_withalpha(NULL,EmpButImg,185,160);
			IsPrintButton = 2;
		}
		else if(IsPress3==1 && IsEmpty3==0) {
			putimage_withalpha(NULL,EmpButImg,185,160);
			IsPrintButton = 2;
		}
		
	}
	
}

//存檔用函式 
void save() 
{
	if(IsPress1){
		fptr = fopen("data\\save\\save1.dat", "wb");
	}
	else if (IsPress2){
		fptr = fopen("data\\save\\save2.dat", "wb");
	}
	else if (IsPress3){
		fptr = fopen("data\\save\\save3.dat", "wb");
	}
	
	if(fptr == NULL)
	{
		puts("ERROR: Open file failed.");
		assert(0);
	}
	else if(fwrite(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_fhp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_damage failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write player_output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgX failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write bgY failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy_num failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&inMaz,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write inMaz failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&equipsword,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write equipsword failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&open,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write open failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(BgName,sizeof(char),50,fptr))
	{
		puts("ERROR: Write BgName failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bp,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Write bp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bpIdx,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Write bpIdx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fwrite(bpAmount,sizeof(int),3,fptr))
	{
		puts("ERROR: Write bpAmount failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[0].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[0].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[1].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[1].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[2].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[2].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[0].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[0].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[1].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[1].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[2].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[2].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[0].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[0].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[1].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[1].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fwrite(&enemy[2].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Write enemy[2].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else{
		fclose(fptr);
		puts("Save successfully");
		if(IsPress1) IsEmpty1 = 1;
		else if(IsPress2) IsEmpty2 = 1;
		else if(IsPress3) IsEmpty3 = 1;
	}
    //只須完成寫檔及建檔功能，寫入內容先空著就好
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例 
}

//讀檔用函式 
void load() 
{
	FILE *fptr;
	if(IsPress1){
		fptr = fopen("data\\save\\save1.dat", "rb");
	}
	else if (IsPress2){
		fptr = fopen("data\\save\\save2.dat", "rb");
	}
	else if (IsPress3){
		fptr = fopen("data\\save\\save3.dat", "rb");
	}
	
	if(fptr == NULL)
	{
		puts("ERROR: The file does not exist.");
		assert(0);
	}
	else if(fread(&player.hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.fhp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_fhp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.damage,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_damage failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&player.output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load player_output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&bgX,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgX failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&bgY,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load bgY failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy_num,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy_num failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&inMaz,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load inMaz failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&equipsword,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load equipsword failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&open,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load open failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(BgName,sizeof(char),50,fptr))
	{
		puts("ERROR: Load BgName failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bp,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Load bp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bpIdx,sizeof(int),3*bpL,fptr))
	{
		puts("ERROR: Load bpIdx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(!fread(bpAmount,sizeof(int),3,fptr))
	{
		puts("ERROR: Load bpAmount failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[0].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[0].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[1].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[1].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[2].x,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[2].x failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[0].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[0].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[1].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[1].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[2].hp,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[2].hp failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[0].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[0].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[1].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[1].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else if(fread(&enemy[2].output_idx,sizeof(int),1,fptr) != 1)
	{
		puts("ERROR: Load enemy[2].output_idx failed.");
		fclose(fptr);
		assert(0);
	}
	else{
		mciSendString (TEXT("stop bgm"), NULL,0,NULL);
        mciSendString (TEXT("close bgm"), NULL,0,NULL);
		if (strcmp(BgName, "images\\bg\\home2.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\home.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName,1587/2,1300/2);
		}
		else if (strcmp(BgName, "images\\bg\\home1.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\home.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName,1587/2,1300/2);
		}
		else if (strcmp(BgName, "images\\bg\\village.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\village.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName, 1859*1.2, 1542*1.3);
		}
		else if (strcmp(BgName, "images\\bg\\shop.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\shop.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName,1587/2,1300/2);
		}
		else if (strcmp(BgName, "images\\bg\\cave01.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\cave01.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName, 1463*1.3, 1957*1.3);
		}
		else if (strcmp(BgName, "images\\bg\\cave02.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\cave02.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName, 1480*1.3, 1374*1.3);
		}
		else if (strcmp(BgName, "images\\bg\\cave03.png")==0) {
			mciSendString (TEXT("open audio\\bgm\\cave03.mp3 alias bgm"), NULL,0,NULL);
	    	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			loadBG(BgName, 1935*1.3, 1744*1.3);
		}
		fclose(fptr);
		puts("Load successfully");

		folder = 0;
		IsPress1 = 0;
		IsPress2 = 0;
		IsPress3 = 0;
		IsPrintButton = 0;
		key = 0;
		esc = 0;
        fadeOut();
		fade = 1;
		flushmouse();
		flushkey();
	}
	
	
    //只需進行開檔及讀檔，若檔案不存在須告知玩家
	//三個存檔的檔名分別為save1.dat save2.dat sav3.dat
	//寫入之檔案須放置在data/save裡
	//已經先放了一個save1.dat當作範例  
}

//刪除存檔用函式
void del(){
	//檔案清空
	//print empty
	if(IsPress1){
		fptr = fopen("data\\save\\save1.dat", "wb");
		IsEmpty1 = 0;
	}
	else if (IsPress2){
		fptr = fopen("data\\save\\save2.dat", "wb");
		IsEmpty2 = 0;
	}
	else if (IsPress3){
		fptr = fopen("data\\save\\save3.dat", "wb");
		IsEmpty3 = 0;
	}
	
	if(fptr == NULL){
		puts("ERROR: clean file failed.");
		assert(0);
	}
	else{
		puts("clean file successfully");
		fclose(fptr);
	}
}