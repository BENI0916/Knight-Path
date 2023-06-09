#include "dirent.h"
#include "lib/var.h" 
#include "lib/output_img.h"
#include "lib/status.h"
#include "lib/effect.h"

extern PIMAGE bg, win_screen;
extern int enemy_num, isNext, inFight, atk_cd, win_screen_cnt, boss_bgm_play;
extern Human player;
extern Monster enemy[3];
extern Bullet skill[6], tp_door[2];
extern Animate loading_animate;
extern char BgName[50];

void output_image()
{
	if(loading_animate.printed)
	{
		loading_animate.output_idx = loading_animate.cnt / 8;
		putimage(0, 0, loading_animate.loading_img[loading_animate.output_idx]);
		loading_animate.cnt++;

		// loading動畫結束時，必定是銜接場景或下一個敵人
		// enemy_num為敵人編號，會換到下一個敵人
		// 玩家的初始位置也會回復
		if(loading_animate.cnt >= 72)
		{
			loading_animate.printed = 0;
			if (isNext) {
				enemy_num++;
				atk_cd = 4;
				printf("enemy_num = %d\n", enemy_num);
				player.x = wid / 4;

				/*if(enemy_num < 3)
				{
					char str[100] = "open audio\\boss_bgm\\1.mp3 alias boss_bgm";
					//sprintf(s, "%d", "open audio\\boss_bgm\\%d.mp3 alias boss_bgm") 
					mciSendString (TEXT(str), NULL,0,NULL);
					mciSendString (TEXT("play boss_bgm repeat"), NULL,0,NULL);
				}*/
				
				//與player_atk的win_music合在一起
				mciSendString (TEXT("stop win"), NULL,0,NULL);
				mciSendString (TEXT("close win"), NULL,0,NULL);
			}
			else {
				loading_animate.printed = 1;
				loading_animate.cnt = 0;
				inFight=0;
            	player.x = (wid-28*3.5) / 2;
				player.y = (hih-33*3.5) / 2 + 80;
            	player.output_idx = 30;// 輸出圖片編號 
	        	player.high = 28*3.5;   // 人物圖片的高 
				player.width = 33*3.5;  // 人物圖片的寬
				sprintf(BgName,"%s","images\\bg\\village.png");
            	loadBG(BgName, 1859*1.2, 1542*1.3);
				mciSendString (TEXT("stop win"), NULL,0,NULL);
				mciSendString (TEXT("close win"), NULL,0,NULL);
				mciSendString (TEXT("open audio\\bgm\\village.mp3 alias bgm"), NULL,0,NULL);
	    		mciSendString (TEXT("play bgm repeat"), NULL,0,NULL);
			}
			
		}
	}
	else
	{
		// 輸出背景 
		putimage(0, 0, bg);
		
		if(enemy[enemy_num].hp > 0)
		{
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_msk[enemy[enemy_num].output_idx], NOTSRCERASE);
			putimage(enemy[enemy_num].x, enemy[enemy_num].y, enemy[enemy_num].enemy_img[enemy[enemy_num].output_idx], SRCINVERT);
			
			for(int i = 0; i < 6; i++)
			{
				// 若技能正在發動會印出 
				if(skill[i].status > 0)
				{
					putimage(skill[i].x, skill[i].y, skill[i].skill_msk[skill[i].output_idx], NOTSRCERASE);
					putimage(skill[i].x, skill[i].y, skill[i].skill_img[skill[i].output_idx], SRCINVERT);
				}
			}
		}
		else
		{ // 若敵人血量歸0，但玩家還沒走到傳送門區域
		  // 則持續印出傳送門
			put_tp_door_img();
			mciSendString (TEXT("stop boss_bgm"), NULL,0,NULL);
			mciSendString (TEXT("close boss_bgm"), NULL,0,NULL);
			boss_bgm_play = 0;
		}
		
		// 輸出玩家
		putimage(player.x, player.y, player.player_msk[player.output_idx], NOTSRCERASE);
		putimage(player.x, player.y, player.player_img[player.output_idx], SRCINVERT);
		playerBlood(player.hp,player.fhp);
		monBlood(enemy[enemy_num].hp,enemy[enemy_num].fhp);

		if(enemy[2].hp <= 0 && win_screen_cnt == 0)
		{
			fadeIn();
			win_screen_cnt++;
		}
		else if(enemy[2].hp <= 0 && win_screen_cnt < 100)
		{
			win_screen_cnt++;
			putimage(0, 0, wid, hih, win_screen, 0, 0, 1920, 1080);
			//printf("%d\n", win_screen_cnt);
		}
		else if(enemy[2].hp <= 0 && win_screen_cnt == 100)
		{
			fadeOut();
			win_screen_cnt++;
		}
	}
}	

//讀取背景圖片 filename:欲讀取背景之路徑及檔名
void loadBG(char filename[]) 
{	
	delimage(bg);
	bg = newimage(wid,hih);
	PIMAGE oriBG = newimage(); //建立暫存之背景圖片
	getimage(oriBG, filename); //取得圖片
	putimage(bg, 0, 0, wid, hih, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG)); //進行拉伸並儲存
	delimage(oriBG); //刪除暫存
}

//讀取背景圖片 filename:欲讀取背景之路徑及檔名 w:伸縮後寬 h:伸縮後高
void loadBG(char filename[],int w,int h) 
{	
	delimage(bg);
	bg = newimage(w,h);
	PIMAGE oriBG = newimage(); //建立暫存之背景圖片
	getimage(oriBG, filename); //取得圖片
	putimage(bg, 0, 0, w, h, oriBG, 0, 0, getwidth(oriBG), getheight(oriBG)); //進行拉伸並儲存
	delimage(oriBG); //刪除暫存
}

//讀取角色圖片 filename:欲讀取圖片之路徑及檔名
//**ori_img:指向圖片將儲存之指標變數 **ori_msk:指向遮罩將儲存之指標變數
//w:圖片輸出後之寬 h: 圖片輸出後之高
void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h,int index) 
{
	PIMAGE *img = NULL,*msk = NULL; //暫存圖片及遮罩之指標變數
	DIR *img_dir = NULL, *msk_dir = NULL; //資料夾的位址
    struct dirent *img_entry, *msk_entry;

	char img_str[100], msk_str[100];
	sprintf(img_str, ".\\%s\\img", filename); //定位
	sprintf(msk_str, ".\\%s\\msk", filename); //定位
	if((img_dir = opendir(img_str)) == NULL || (msk_dir = opendir(msk_str)) == NULL) 
	{ //判斷是否成功開啟所指定之路徑
            printf("opendir failed!\n");   
    }
	else 
	{
		for (int i = index;(img_entry = readdir(img_dir)), (msk_entry = readdir(msk_dir));) 
		{ //判斷是否含有未讀取之檔案，若無則離開迭代
			if (strstr(img_entry->d_name,".png") && strstr(msk_entry->d_name, ".png")) 
			{ //判斷讀取之檔案的副檔名
				//擴充陣列
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				*ori_msk = (PIMAGE *)realloc(*ori_msk,sizeof(PIMAGE)*(i+1));
				
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));
				msk = (PIMAGE *)realloc(msk,sizeof(PIMAGE)*(i+1));	
				
				//建立圖片
				(*ori_img)[i] = newimage(w,h);
				(*ori_msk)[i] = newimage(w,h);
				
				img[i] = newimage();
				msk[i] = newimage();

				//讀取圖片並拉伸至指定長高
				sprintf(img_str, "%s\\img\\%s",filename,img_entry->d_name);
				sprintf(msk_str, "%s\\msk\\%s",filename,msk_entry->d_name);
				
				getimage(img[i], img_str);
				getimage(msk[i], msk_str);
				
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				putimage((*ori_msk)[i], 0, 0, w, h, msk[i], 0, 0, getwidth(msk[i]), getheight(msk[i]));
				
				delimage(img[i]); //刪除暫存
				delimage(msk[i++]); //刪除暫存
			}
		}
		closedir(img_dir);
		closedir(msk_dir);
	}

	free(img);
	free(msk);
}

void loadCHAR(char filename[],PIMAGE **ori_img,int w,int h,int index) 
{
	PIMAGE *img = NULL; //暫存圖片及遮罩之指標變數
	DIR *img_dir = NULL; //資料夾的位址
    struct dirent *img_entry;

	char img_str[100];
	sprintf(img_str, ".\\%s", filename); //定位
	if((img_dir = opendir(img_str)) == NULL) 
	{ //判斷是否成功開啟所指定之路徑
            printf("opendir failed!\n");   
    }
	else 
	{
		for (int i = index;img_entry = readdir(img_dir);) 
		{ //判斷是否含有未讀取之檔案，若無則離開迭代
			if (strstr(img_entry->d_name,".png")) 
			{ //判斷讀取之檔案的副檔名
				//擴充陣列
				*ori_img = (PIMAGE *)realloc(*ori_img,sizeof(PIMAGE)*(i+1));
				
				img = (PIMAGE *)realloc(img,sizeof(PIMAGE)*(i+1));
				
				//建立圖片
				(*ori_img)[i] = newimage(w,h);
				
				img[i] = newimage();

				//讀取圖片並拉伸至指定長高
				sprintf(img_str, "%s\\%s",filename,img_entry->d_name);
				
				getimage(img[i], img_str);
				
				putimage((*ori_img)[i], 0, 0, w, h, img[i], 0, 0, getwidth(img[i]), getheight(img[i]));
				
				delimage(img[i++]); //刪除暫存
			}
		}
		closedir(img_dir);
	}
	free(img);
}


void put_tp_door_img()
{
	for (int i = 0;i<2;i++) {
	if(tp_door[i].power < 20)
		tp_door[i].output_idx = 0;
	else if(tp_door[i].power < 40)
		tp_door[i].output_idx = 1;
	else if(tp_door[i].power < 60)
		tp_door[i].output_idx = 2;
	else if(tp_door[i].power < 80)
		tp_door[i].output_idx = 3;
	else
		tp_door[i].power = 0;
	tp_door[i].power++;

	putimage(tp_door[i].x, tp_door[i].y, tp_door[i].skill_msk[tp_door[i].output_idx], NOTSRCERASE);
	putimage(tp_door[i].x, tp_door[i].y, tp_door[i].skill_img[tp_door[i].output_idx], SRCINVERT);

	}
}
