#include "lib/lunch.h"
#include "lib/var.h" 
#include "lib/initialization.h"
#include "lib/enemy_move.h"
#include "lib/enemy_atk.h"
#include "lib/player_move.h"
#include "lib/output_img.h"
#include "lib/player_move3D.h"
#include "lib/esc.h"
#include "lib/effect.h"
#include "lib/status.h"
#include "lib/enemy_move3D.h"
#include "lib/event.h"
#include "lib/bebao.h"
#include "lib/save_load.h"

extern PIMAGE bg, dropImg[bpL], win_screen,screen;
extern int enemy_atk_type, enemy_num, inFight, bgX, bgY, win_screen_cnt,inMaz,atk_cd,player_walk_cnt,player_jump_cnt,dash_cnt,atk_cnt, boss_bgm_play, IsEmpty1, IsEmpty2, IsEmpty3, IsPress1, IsPress2, IsPress3, IsPrintButton, talk;
extern Human player;
extern Monster enemy[3];
extern Bullet skill[6];
extern Animate loading_animate;
extern double end;
extern char BgName[];
extern FILE *fptr;

long int size1, size2, size3;
int esc,fade,metEvent,victory,inBp,fOn,inMaz,inHelp,folder;
PIMAGE escBG,pauseImg,bgF,victoryUI,dropImg[bpL],gray,bpImg[3],gameover,fbt,swordImg[3],potionImg[2],helpImg,keyHelp,BpswordImg[3],FolderImg,CellImg,SavButImg,EmpButImg;
FILE *IsEmpty1_ptr, *IsEmpty2_ptr, *IsEmpty3_ptr;

void lunch()
{
	initialization();
	printf("initialization succes\n");
	randomize();
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	setfont(20,0,"number");
	settextjustify(1,1);
	
	folder = 0;
	IsPress1 = 0;
	IsPress2 = 0;
	IsPress3 = 0;
	IsPrintButton = 0;
	inHelp = 0;
	inBp = 0;
	inFight = 0;
	esc = 0;
	fade = 0;
	metEvent = 0;
	victory = 0;
	escBG = newimage();
	pauseImg = newimage();
	victoryUI = newimage();
	gray = newimage();
	gameover = newimage();
	fbt = newimage();
	helpImg = newimage();
	keyHelp = newimage();
	FolderImg = newimage();
	CellImg = newimage();
	SavButImg = newimage();
	EmpButImg = newimage();
	getimage(escBG,"images\\bg\\black.png",0,0);
	getimage(pauseImg,"images\\menu\\pause.png",0,0);
	getimage(victoryUI,"images\\menu\\victoryUI.png",0,0);
	getimage(gray,"images\\menu\\bk.png",0,0);
	getimage(gameover,"images\\bg\\gameover.png",0,0);
	getimage(fbt,"images\\menu\\F.png",0,0);
	getimage(helpImg,"images\\menu\\help.png",0,0);
	getimage(keyHelp,"images\\menu\\keyHelp.png",0,0);
	getimage(FolderImg,"images\\menu\\white_folder.png");
	getimage(CellImg,"images\\save_load_img\\three_cell.png");
	getimage(SavButImg,"images\\save_load_img\\saved_button.png");
	getimage(EmpButImg,"images\\save_load_img\\empty_button.png");

	mciSendString (TEXT("open audio\\bgm\\home.mp3 alias bgm"), NULL,0,NULL);
	mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);

	//一開始判斷三個儲存格有沒有東西
	IsEmpty1_ptr = fopen("data\\save\\save1.dat", "rb");
	IsEmpty2_ptr = fopen("data\\save\\save2.dat", "rb");
	IsEmpty3_ptr = fopen("data\\save\\save3.dat", "rb");

	fseek(IsEmpty1_ptr, 0, SEEK_END);
	size1 = ftell(IsEmpty1_ptr);
	if(!size1) IsEmpty1 = 0;
	else IsEmpty1 = 1;
	
	fseek(IsEmpty2_ptr, 0, SEEK_END);
	size2 = ftell(IsEmpty2_ptr);
	if(!size2) IsEmpty2 = 0;
	else IsEmpty2 = 1;
	
	fseek(IsEmpty3_ptr, 0, SEEK_END);
	size3 = ftell(IsEmpty3_ptr);
	if(!size3) IsEmpty3 = 0;
	else IsEmpty3 = 1;
	
	fclose(IsEmpty1_ptr);
	fclose(IsEmpty2_ptr);
	fclose(IsEmpty3_ptr);

	flushkey();
	// is_run 檢視程序是否收到關閉消息, 收到的話會返回false, 即退出程序 
	// delay_fps 控制幀率, 60 表示"平均延時"為1000/60毫秒 
	for (; is_run() && enemy_num < 3; delay_fps(60))
	{
		cleardevice(); // 把輸出的窗口清空 

		if(talk) {
			talk = 0;
			talking();
		}

		if (player.hp<=0) {
			if (inFight) {
				inFight=0;
				atk_cd = 4;
				enemy[enemy_num].hp = enemy[enemy_num].fhp;
				enemy[enemy_num].x = 900;
				enemy[enemy_num].output_idx = 1;
				enemy[enemy_num].dir = 'a';
				enemy[0].y = hih * 0.6 - 165 + 66;
				enemy[1].y = hih * 0.6 - 150 + 66;
				enemy[2].y = hih * 0.6 - 400 + 66;
				enemy_atk_type = -1;
				boss_bgm_play = 0; // 當不在Boss戰時，下次進Boss戰會撥放Bgm
				for(int i = 0; i < 6; i++)
					skill[i].status = 0;
			}
			else {
				mciSendString (TEXT("stop battlemusic"), NULL,0,NULL);
        		mciSendString (TEXT("close battlemusic"), NULL,0,NULL);
				delimage(bgF);
    			metEvent = 0;
				inMaz=0;
			}
			mciSendString (TEXT("open audio\\bgm\\gameover.mp3 alias gameover"), NULL,0,NULL);
	    	mciSendString (TEXT("play gameover"), NULL,0,NULL);
			putimage(0,0,screen);
			for (int i = 0;i<32;delay_fps(30)) {
				putimage_alphablend(NULL,gameover,0,0,0x18,0,0,wid,hih);
				i++;
			}
            player.x = (wid-28*3.5) / 2;
			player.y = (hih-33*3.5) / 2 + 80;
            player.output_idx = 27;// 輸出圖片編號 
	        player.high = 28*3.5;   // 人物圖片的高 
			player.width = 33*3.5;  // 人物圖片的寬
			player.atk_type = 0;
			player_walk_cnt = 11;
			player_jump_cnt = -1;
			atk_cnt = -1;
			dash_cnt = 0;
			sprintf(BgName,"%s","images\\bg\\home2.png");
            bgX=20;
            bgY=-20;
			loadBG(BgName,1587/2,1300/2);
    		flushkey();
    		flushmouse();
			victory = -1;
			player.hp = player.fhp;
		}
		else if (inBp) {
			bpScreen();
			bpListener();
		}
		else if (victory) {
			if (victory==1) {
				putimage(0,0,screen);
				putimage_withalpha(NULL,victoryUI,0,0);
				putDrop();
				vicListener();
			}
			if (victory==-1) {
				putimage(0,0,gameover);
				goListener();
			}
		}
		else if (esc) {
			if (folder) {
				escScreen();
				SaveLoadScreen();
				SaveLoadlistener();
			}
			else if (inHelp) {
				putimage_withalpha(NULL,keyHelp,0,0);
				escListener();
			}
			else {
				escScreen();
				escListener();
			}
		}
		else {
			if (inFight) 
			{//判斷是否在戰鬥中
				if(enemy[enemy_num].hp > 0) // 若敵人血量不為 0 則會行動 
				{
					if(enemy_atk_type == -1) // -1 代表 敵人未開始攻擊  
						enemy_move();		 // 則敵人會開始移動 
					enemy_atk();			 // 否則會進行攻擊  

					if(!boss_bgm_play)
					{
						boss_bgm_play = 1;
						char str[100] = "open audio\\boss_bgm\\1.mp3 alias boss_bgm";
						//sprintf(s, "%d", "open audio\\boss_bgm\\%d.mp3 alias boss_bgm") 
						mciSendString (TEXT(str), NULL,0,NULL);
						mciSendString (TEXT("play boss_bgm repeat"), NULL,0,NULL);
					}
				}

				if(player.hp <= 0)
				{
					mciSendString (TEXT("stop boss_bgm"), NULL,0,NULL);
					mciSendString (TEXT("close boss_bgm"), NULL,0,NULL);
				}

				move(5);
				output_image();

				if (enemy_num >= 3)
				{
					inFight = 0;
					ending();
					delimage(escBG);
					delimage(pauseImg);
					delimage(victoryUI);
					delimage(gray);
					delimage(gameover);
					delimage(fbt);
					delimage(helpImg);
					delimage(keyHelp);
				}
				
			}
			else if (!metEvent){
				keyListener();
				putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
				putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
				putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
				if(fOn) putimage(720,430,fbt);
			}

			if (metEvent) {
				if (metEvent<10) {
					move(5);
					putimage(0,0,bgF);
					putEnemy(metEvent);
					if (victory==0) {
						putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
						putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
						playerBlood(player.hp,player.fhp);
					}
				}
			}
			getimage(screen,0,0,wid,hih);
			if (fade) {
				fade = fadeIn();
			}
		}
	}
}

void talking()
{
	int idx = 1;
	char s[100], ch;
	PIMAGE img = newimage();

	PIMAGE pic[33];
	for(int i = 1; i < 33; i++)
	{
		sprintf(s, "images\\talk\\%d.png", i);
		pic[i] = newimage();
		getimage(pic[i], s, 0, 0);
		printf("%d\n", i);
	}
	printf("get pic succes\n");

	putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
	putimage_withalpha(NULL,pic[idx],0,0);
	getimage(img,0,0,wid,hih);
	cleardevice();
    for (int i = 0;i<16;delay_fps(30)) {
		putimage_alphablend(NULL,img,0,0,0x30,0,0,wid,hih);
		i++;
	}
	delimage(img);
    flushkey();
    flushmouse();


	for(;is_run()&&idx<33;delay_fps(60))
	{
		cleardevice();
		putimage(abs(wid-getwidth(bg))/2 + bgX, abs(hih-getheight(bg))/2 + bgY, bg);
		putimage_withalpha(NULL,pic[idx],0,0);
		if (kbhit()) {
			ch = getch();
		}
		
		if(ch != NULL||keystate(key_mouse_l))
		{
			for(;is_run();delay_fps(60))if(keystate(key_mouse_l)==0) break;
			printf("idx = %d\n", idx);
			idx++;
			delimage(pic[idx - 1]);
			
			ch = NULL;
			flushmouse();
			flushkey();
		}
	}
}
