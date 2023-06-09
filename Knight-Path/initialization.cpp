#include "dirent.h"
#include "lib/var.h"
#include "lib/initialization.h"
#include "lib/output_img.h"
#include "lib/enemy_atk.h"

extern int atk_cnt, player_walk_cnt, flag, enemy_atk_type, player_jump_cnt, atked, enemy_num,player_walk_cnt3D,bgX,bgY, inFight, get_dmg_cnt, dash_cnt, combine_cnt, atk_cd, win_screen_cnt, boss_bgm_play, talk;
extern double start;
extern Human player;
extern Monster enemy[3];
extern Bullet skill[6], tp_door[2];
extern Animate loading_animate;
extern char BgName[50];
extern PIMAGE bloodLine, blood[21], dropImg[],bpImg[], win_screen, swordImg[], potionImg[],BpswordImg[];

void initialization()
{
	loadBG(BgName,1587/2,1300/2); //Ū���I��
	
	printf("load background succes\n");
	char s[50];
	player.player_img = NULL;
	player.player_msk = NULL;
	sprintf(s,"%s","images\\main_char"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66, 0); //Ū���D���Ϥ�
	sprintf(s,"%s","images\\3D\\player");
	loadCHAR(s,&player.player_img,&player.player_msk,38*3.5,33*3.5,26);
	sprintf(s,"%s","images\\main_char_skill"); //C++�L�k�N�r��`�ƪ����নchar pointer�A�G������
	loadCHAR(s,&player.player_img,&player.player_msk,76,66, 38); //Ū���D���Ϥ�
	printf("load player image succes\n");
	// �]�w��l�� 
	player.x = (wid-28*3.5) / 2;
	player.y = (hih-33*3.5) / 2 + 80; 
	player.atked = 0;   // �P�w�O�_���y���ˮ`  
	player.dir = 'd';   // ��V 
	player.high = 28*3.5;   // �H���Ϥ����� 
	player.width = 33*3.5;  // �H���Ϥ����e 
	player.power = 30;  // ���h�ĤH���Z�� 
	player.atk_type = 0;
	
	player_walk_cnt = 11; // �����p�ɾ� 
	player_walk_cnt3D = 0;
	
	printf("player setting succes\n");

	drop_ini();
	printf("drop ini succes\n");

	blood_ini();
	printf("blood ini succes\n");
	
	enemy_ini(); // ��l�ƼĤH 
	
	printf("enemy ini succes\n");
	flag = 10;
	
	enemy_ini_01();
	printf("enemy_ini_01 succes\n");
	
	enemy_ini_02();
	printf("enemy_ini_02 succes\n");

	skill_ini_00();
	printf("skill_ini_00 succes\n");
	
	skill_ini_01(); // ��l�ƼĤH���ޯ� 
	printf("skill_ini_01 succes\n");
	
	skill_ini_02();
	printf("skill_ini_02 succes\n");
	
	skill_ini_03();
	printf("skill_ini_03 succes\n");

	skill_ini_04();
	printf("skill_ini_04 succes\n");
	
	skill_ini_05();
	printf("skill_ini_05 succes\n");

	tp_door_ini();
	printf("tp_door_ini succes\n");

	shop_ini();
	printf("shop_ini succes\n");

	start = fclock(); // �Ω�p�ɼĤH�������ɶ����j 
	enemy_atk_type = -1; // �ĤH�ϥΪ��ޯ�s�� 
	player_jump_cnt = -1;// �H�����D�p�ɾ�
	
	
	loading_img_ini();
	printf("loading_img_ini succes\n");
	
	inFight = 0;
	get_dmg_cnt = 0;
	dash_cnt = 0;
	combine_cnt = 0;
	atk_cd = 4;

	// 勝利畫面
	win_screen_cnt = 0;
	getimage(win_screen, "images\\menu\\win_screen.png", wid, hih);

	// 0 表示沒放boss bgm
	// 1 代表有放
	boss_bgm_play = 0;

	talk = 1; // 1代表還沒講 0代表講完了
}

void enemy_ini()
{
	char s[100];
	
	enemy[0].enemy_img = NULL;
	enemy[0].enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_0");
	loadCHAR(s, &enemy[0].enemy_img, &enemy[0].enemy_msk, 165, 165, 0);
	
	enemy[0].x = 900;
	enemy[0].y = hih * 0.6 - 165 + 66;
	enemy[0].dir = 'a';
	enemy[0].hp = 100;
	enemy[0].fhp = 100;
	enemy[0].damage = 1; // �ĤH�y�����ˮ` 
	enemy[0].output_idx = 1;
	enemy[0].high = 165;
	enemy[0].width = 165;
	enemy[0].power = 100; // �ĤH���h���a���Z�� 
	enemy[0].speed = 5;    
	enemy[0].atk_0_cnt = 99; // �ĤH���ޯ�p�ƾ� 
	enemy[0].atk_1_cnt = 99;  
}

void enemy_ini_01()
{
	char s[100];
	
	enemy[1].enemy_img = NULL;
	enemy[1].enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_1");
	loadCHAR(s, &enemy[1].enemy_img, &enemy[1].enemy_msk, 136, 150, 0);
	//508
	enemy[1].x = 900;
	enemy[1].y = hih * 0.6 - 150 + 66;
	enemy[1].dir = 'a';
	enemy[1].hp = 100;
	enemy[1].fhp = 100;
	enemy[1].damage = 1; // �ĤH�y�����ˮ` 
	enemy[1].output_idx = 1;
	enemy[1].high = 150;
	enemy[1].width = 136;
	enemy[1].power = 100; // �ĤH���h���a���Z�� 
	enemy[1].speed = 5;    
	enemy[1].atk_0_cnt = -1; // �ĤH���ޯ�p�ƾ� 
	enemy[1].atk_1_cnt = -1;  
}

void enemy_ini_02()
{
	char s[100];
	
	enemy[2].enemy_img = NULL;
	enemy[2].enemy_msk = NULL;
	
	sprintf(s,"%s","images\\enemy_2");
	loadCHAR(s, &enemy[2].enemy_img, &enemy[2].enemy_msk, 500, 400, 0);
	//508
	enemy[2].x = 900;
	enemy[2].y = hih * 0.6 - 400 + 66;
	enemy[2].dir = 'a';
	enemy[2].hp = 100;
	enemy[2].fhp = 100;
	enemy[2].damage = 1; // �ĤH�y�����ˮ` 
	enemy[2].output_idx = 1;
	enemy[2].high = 400;
	enemy[2].width = 500;
	enemy[2].power = 100; // �ĤH���h���a���Z�� 
	enemy[2].speed = 4;    
	enemy[2].atk_0_cnt = -1; // �ĤH���ޯ�p�ƾ� 
	enemy[2].atk_1_cnt = -1;  
}

// �ޯ�1 
void skill_ini_00()
{
	char s[100];
	
	skill[0].x = 0;
	skill[0].y = 0;
	skill[0].output_idx = 0;
	skill[0].status = 0;
	skill[0].skill_img = NULL;
	skill[0].skill_msk = NULL;
	
	sprintf(s, "%s", "images\\enemy_0_0_skill");
	loadCHAR(s, &skill[0].skill_img, &skill[0].skill_msk, 250, 126, 0);
	
	skill[0].high = 126;
	skill[0].width = 250;
	skill[0].power = 200;
}

// �ޯ�2 
void skill_ini_01()
{
	char s[100];
	
	skill[1].x = 0;
	skill[1].y = 0;
	skill[1].status = 0;
	skill[1].output_idx = 0;
	skill[1].skill_img = NULL;
	skill[1].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_0_1_skill");
	loadCHAR(s, &skill[1].skill_img, &skill[1].skill_msk, 608, 256, 0);
	
	skill[1].high = 256;
	skill[1].width = 608;
	skill[1].power = 200;
}

void loading_img_ini()
{
	char s[100];
	
	loading_animate.loading_img = (PIMAGE *)malloc(sizeof(PIMAGE) * 8);
	
	for(int i = 0; i < 9; i++)
	{
		loading_animate.loading_img[i] = newimage();
		sprintf(s, "images\\loading\\0%d_loading_img.png", i);
		getimage(loading_animate.loading_img[i], s);
	}
	
	loading_animate.cnt = 0;
	loading_animate.output_idx = 0;
	loading_animate.printed = 1;
}

void skill_ini_02()
{
	char s[100];
	
	skill[2].x = 0;
	skill[2].y = 0;
	skill[2].status = 0;
	skill[2].output_idx = 0;
	skill[2].skill_img = NULL;
	skill[2].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_0_2_skill"); // 34 21
	loadCHAR(s, &skill[2].skill_img, &skill[2].skill_msk, 170, 105, 0);
	
	skill[2].high = 105;
	skill[2].width = 170;
	skill[2].power = 100;
}

void skill_ini_03()
{
	char s[100];
	
	skill[3].x = 0;
	skill[3].y = 0;
	skill[3].status = 0;
	skill[3].output_idx = 0;
	skill[3].skill_img = NULL;
	skill[3].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_1_0_skill");
	loadCHAR(s, &skill[3].skill_img, &skill[3].skill_msk, 125, 125, 0);
	
	skill[3].high = 125;
	skill[3].width = 125;
	skill[3].power = 50;
}

void skill_ini_04()
{
	char s[100];
	skill[4].x = 0;
	skill[4].y = 0;
	skill[4].status = 0;
	skill[4].output_idx = 0;
	skill[4].skill_img = NULL;
	skill[4].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_1_1_skill");
	loadCHAR(s, &skill[4].skill_img, &skill[4].skill_msk, 336, 296, 0);
	
	skill[4].high = 296;
	skill[4].width = 336;
	skill[4].power = 5;
}

void skill_ini_05()
{
	char s[100];
	skill[5].x = 0;
	skill[5].y = 0;
	skill[5].status = 0;
	skill[5].output_idx = 0;
	skill[5].skill_img = NULL;
	skill[5].skill_msk = NULL;
	sprintf(s, "%s", "images\\enemy_1_2_skill");
	loadCHAR(s, &skill[5].skill_img, &skill[5].skill_msk, 116, 280, 0);
	
	skill[5].high = 280;
	skill[5].width = 116;
	skill[5].power = 60;
}

// �ΨӦs��ǰe��
// .power���@��X���p�ƾ�
void tp_door_ini()
{
	char s[100];
	sprintf(s, "%s", "images\\tp_door\\right");

	tp_door[0].x = wid - 77;
	tp_door[0].y = hih * 0.6 -11;
	tp_door[0].status = 0;
	tp_door[0].output_idx = 0;
	tp_door[0].skill_img = NULL;
	tp_door[0].skill_msk = NULL;
	loadCHAR(s, &(tp_door[0]).skill_img, &(tp_door[0]).skill_msk, 77, 77, 0);
	
	tp_door[0].high = 77;
	tp_door[0].width = 77;
	tp_door[0].power = 0;

	sprintf(s, "%s", "images\\tp_door\\left");
	tp_door[1].x = 7;
	tp_door[1].y = hih * 0.6 -11;
	tp_door[1].status = 0;
	tp_door[1].output_idx = 0;
	tp_door[1].skill_img = NULL;
	tp_door[1].skill_msk = NULL;
	loadCHAR(s, &(tp_door[1]).skill_img, &(tp_door[1]).skill_msk, 77, 77, 0);
	
	tp_door[1].high = 77;
	tp_door[1].width = 77;
	tp_door[1].power = 0;
}

void blood_ini() {
	bloodLine = newimage();
	getimage(bloodLine,"images\\blood\\line.png",0,0);
	char s[50];
	for (int i = 0;i<21;i++) {
		blood[i] = newimage();
		sprintf(s, "images\\blood\\20\\%d.png", i);
		getimage(blood[i],s,0,0);
	}
}

void drop_ini() {
	char s[50];
	for (int i = 0;i<bpL;i++) {
		dropImg[i] = newimage();
		sprintf(s, "images\\3D\\drop\\%d.png", i);
		getimage(dropImg[i],s,0,0);
	}
	for (int i = 0;i<3;i++) {
		bpImg[i] = newimage();
		sprintf(s, "images\\menu\\bp%d.png", i+1);
		getimage(bpImg[i],s,0,0);
	}
}

void shop_ini() {
	char s[50];
	for (int i = 0;i<3;i++) {
		swordImg[i] = newimage();
		sprintf(s, "images\\3D\\shop\\sword%d.png", i);
		getimage(swordImg[i],s,0,0);
	}
	for (int i = 0;i<3;i++) {
		BpswordImg[i] = newimage();
		sprintf(s, "images\\menu\\sword%d.png", i);
		getimage(BpswordImg[i],s,0,0);
	}
	for (int i = 0;i<2;i++) {
		potionImg[i] = newimage();
		sprintf(s, "images\\3D\\shop\\potion%d.png", i);
		getimage(potionImg[i],s,0,0);
	}
}