#include "lib/var.h"
#include "lib/player_atk.h"
#include "lib/enemy_give_dmg.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked, enemy_num, inFight, player_skill_type;
extern double start, end;
extern Human player;
extern Monster enemy[3],monster;

// 玩家攻擊  
void player_atk(int val)
{	
	if (inFight) 
	{
		switch(enemy_num)
		{
			case 0:
				if(player_skill_type == 1)
				{
					if((is_middle(enemy[0].x + enemy[0].width * 0.90, player.x + player.width * 0.5, enemy[0].x + enemy[0].width * 0.1)
					||  is_middle(enemy[0].x + enemy[0].width * 0.90, player.x + player.width, enemy[0].x + enemy[0].width * 0.1)
			    	||  is_middle(enemy[0].x + enemy[0].width * 0.90, player.x, enemy[0].x + enemy[0].width * 0.1)))
					{
						enemy[0].hp-player.damage<=0 ? enemy[0].hp=0 : enemy[0].hp-=player.damage;

						if((player.x + player.width / 2) < (enemy[0].x + enemy[0].width / 2))
							enemy[0].x += player.power;
						else
							enemy[0].x -= player.power;
						player.atked = 1;
					}
				}
				else if(player.dir == 'd')
				{	
					// 若敵人在玩家攻擊範圍  
					if(is_middle(enemy[0].x + enemy[0].width * 0.90, player.x + player.width * 0.9, enemy[0].x + enemy[0].width * 0.1)
					|| is_middle(enemy[0].x + enemy[0].width * 0.90, player.x + player.width * 0.65, enemy[0].x + enemy[0].width * 0.1))
					{
						enemy[0].hp-player.damage<=0 ? enemy[0].hp=0 : enemy[0].hp-=player.damage;
						enemy[0].x += player.power;// 敵人會被玩家擊退  
						player.atked = 1;// 若有造成傷害則會記錄 避免一次攻擊有多次傷害  
					}
				}
				else
				{
					if(is_middle(enemy[0].x + enemy[0].width , player.x + player.width * 0.05, enemy[0].x + enemy[0].width * 0.1)
					|| is_middle(enemy[0].x + enemy[0].width , player.x + player.width * 0.35, enemy[0].x + enemy[0].width * 0.1))
					{
						enemy[0].hp-player.damage<=0 ? enemy[0].hp=0 : enemy[0].hp-=player.damage;
						enemy[0].x -= player.power;	
						player.atked = 1;
					}
				}
				break;
			
			case 1:
				if(player_skill_type == 1)
				{
					if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.64, player.x + player.width * 0.5, enemy[enemy_num].x + enemy[enemy_num].width * 0.36)
					||  is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.64, player.x + player.width, enemy[enemy_num].x + enemy[enemy_num].width * 0.36)
			    	||  is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.64, player.x, enemy[enemy_num].x + enemy[enemy_num].width * 0.36)))
					{
						enemy[enemy_num].hp-player.damage<=0 ? enemy[enemy_num].hp=0 : enemy[enemy_num].hp-=player.damage;

						if((player.x + player.width / 2) < (enemy[enemy_num].x + enemy[enemy_num].width / 2))
							enemy[enemy_num].x += player.power;
						else
							enemy[enemy_num].x -= player.power;
						player.atked = 1;
					}
				}
				else if(player.dir == 'd')
				{
					if((is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width, enemy[1].x + enemy[1].width * 0.36)
					|| is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width * 0.6, enemy[1].x + enemy[1].width * 0.36))
					&& is_middle(enemy[1].y + enemy[1].high, player.y + player.high / 2, enemy[1].y + enemy[1].high * 0.17))
					{
						enemy[1].hp-player.damage<=0 ? enemy[1].hp=0 : enemy[1].hp-=player.damage;
						enemy[1].x += player.power;	
						player.atked = 1;
					}
				}
				else
				{
					if((is_middle(enemy[1].x + enemy[1].width * 0.64, player.x, enemy[1].x + enemy[1].width * 0.36)
					||  is_middle(enemy[1].x + enemy[1].width * 0.64, player.x + player.width * 0.4, enemy[1].x + enemy[1].width * 0.36))
					&& is_middle(enemy[1].y + enemy[1].high, player.y + player.high / 2, enemy[1].y + enemy[1].high * 0.17))
					{
						enemy[1].hp-player.damage<=0 ? enemy[1].hp=0 : enemy[1].hp-=player.damage;
						enemy[1].x -= player.power;	
						player.atked = 1;
					}
				}
				
				break;
			
			case 2:
				if(player_skill_type == 1)
				{
					if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.56, player.x + player.width * 0.5, enemy[enemy_num].x + enemy[enemy_num].width * 0.44)
					||  is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.56, player.x + player.width, enemy[enemy_num].x + enemy[enemy_num].width * 0.44)
			    	||  is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.56, player.x, enemy[enemy_num].x + enemy[enemy_num].width * 0.44)))
					{
						enemy[enemy_num].hp-player.damage<=0 ? enemy[enemy_num].hp=0 : enemy[enemy_num].hp-=player.damage;

						if((player.x + player.width / 2) < (enemy[enemy_num].x + enemy[enemy_num].width / 2))
							enemy[enemy_num].x += player.power;
						else
							enemy[enemy_num].x -= player.power;
						player.atked = 1;
					}
				}
				else if(player.dir == 'd')
				{
					if((is_middle(enemy[2].x + enemy[2].width * 0.56, player.x + player.width * 0.9, enemy[2].x + enemy[2].width * 0.44)
					|| is_middle(enemy[2].x + enemy[2].width * 0.56, player.x + player.width *0.6, enemy[2].x + enemy[2].width * 0.44))
					&& is_middle(enemy[2].y + enemy[2].high, player.y + player.high / 3, enemy[2].y + enemy[2].high * 0.3))
					{
						enemy[2].hp - player.damage <= 0 ? enemy[2].hp = 0 : enemy[2].hp -= player.damage;
						enemy[2].x += player.power;	
						player.atked = 1;
					}
				}
				else
				{
					if((is_middle(enemy[2].x + enemy[2].width * 0.56, player.x + player.width * 0.1, enemy[2].x + enemy[2].width * 0.44)
					|| is_middle(enemy[2].x + enemy[2].width * 0.56, player.x + player.width *0.4, enemy[2].x + enemy[2].width * 0.44))
					&& is_middle(enemy[2].y + enemy[2].high, player.y + player.high / 3, enemy[2].y + enemy[2].high * 0.3))
					{
						enemy[2].hp - player.damage <= 0 ? enemy[2].hp = 0 : enemy[2].hp -= player.damage;
						enemy[2].x -= player.power;	
						player.atked = 1;
					}
				}

				break;

			default :
				break;
		}
		// cur enemy die
		win_music();
	}
	else 
	{
		if (player.dir=='d') 
		{
			if (player.x+player.width>monster.x&&player.x+player.width<monster.x+monster.width) 
			{
				monster.hp-player.damage<=0 ? monster.hp = 0 : monster.hp-=player.damage;
				player.atked = 1;
			}
		}
		else 
		{
			if (player.x<monster.x+monster.width&&player.x>monster.x) 
			{
				monster.hp-player.damage<=0 ? monster.hp = 0 : monster.hp-=player.damage;
				player.atked = 1;
			}
		}
	}
}

void win_music()
{
	if(enemy_num > -1 && enemy[enemy_num].hp <= 0)
	{
		mciSendString (TEXT("open audio\\bgm\\vic.mp3 alias win"), NULL,0,NULL);
		mciSendString (TEXT("play win"), NULL,0,NULL);
	}
}
