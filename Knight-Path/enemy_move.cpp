#include "lib/var.h"
#include "lib/enemy_move.h"

extern int key, atk_cnt, player_walk_cnt, flag, enemy_num;
extern Human player;
extern Monster enemy[3];

void enemy_move()
{
	switch(enemy_num)
	{
		case 0:
			if((enemy[enemy_num].x + enemy[enemy_num].width / 2) > (player.x + player.width / 2))
				enemy[enemy_num].dir = 'a';
			else
				enemy[enemy_num].dir = 'd';
				
			// 若敵人與玩家距離大於敵人的兩個身位
			// 則會往玩家方向移動 
			if(abs(enemy[enemy_num].x - player.x) >= enemy[enemy_num].width * 2)
			{
				if(enemy[enemy_num].x > player.x)
				{	
					enemy[enemy_num].x -= enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 1;
				}
				else
				{
					enemy[enemy_num].x += enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 0;
				}
			}
			
			// 讓敵人走路會有浮動 
			if(flag == 40)
			{
				enemy[enemy_num].y -= 3;
			}
			else if(flag == 0)
			{
				enemy[enemy_num].y += 3;
				flag = 81;
			}
			
			flag--;
			break;
		
		case 1:
			if((enemy[enemy_num].x + enemy[enemy_num].width / 2) > (player.x + player.width / 2))
				enemy[enemy_num].dir = 'a';
			else
				enemy[enemy_num].dir = 'd';
			
			if(abs(enemy[enemy_num].x - player.x) >= enemy[enemy_num].width * 3)
			{
				if(enemy[enemy_num].x > player.x)
				{	
					enemy[enemy_num].x -= enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 1;
				}
				else
				{
					enemy[enemy_num].x += enemy[enemy_num].speed;
					enemy[enemy_num].output_idx = 0;
				}

				// hih * 0.6 - 150 + 66
				if(flag == 20)
				{
					enemy[enemy_num].y -= 10;
				}
				else if(flag == 0)
				{
					enemy[enemy_num].y += 10;
					flag = 21;
				}
				flag--;
			}
			else
			{
				enemy[1].y = hih * 0.6 - 150 + 66;
				if(flag <= 0)
					flag = 80;
				flag--;
				
				int table[2] = {0, 2};
				
				if(enemy[enemy_num].dir == 'a')
				{
					enemy[enemy_num].output_idx = table[flag / 40 ] + 1;
				}
				else
				{
					enemy[enemy_num].output_idx = table[flag / 40 ];
				}
			}
			break;
		
		case 2:
			if((enemy[enemy_num].x + enemy[enemy_num].width / 2) > (player.x + player.width / 2))
				enemy[enemy_num].dir = 'a';
			else
				enemy[enemy_num].dir = 'd';
			if(abs(player.x + player.width / 2 - enemy[2].x - enemy[2].width / 2) > enemy[2].width / 2)
			{
				if(enemy[enemy_num].dir == 'a')
					enemy[enemy_num].x -= enemy[enemy_num].speed;
				else
					enemy[enemy_num].x += enemy[enemy_num].speed;
				
				int table[4] = {10, 8, 6, 4};

				if(flag <= 0 || flag > 60)
					flag = 60;
				flag--;

				enemy[enemy_num].output_idx = table[flag / 15];

				if(enemy[enemy_num].dir == 'a')
					enemy[enemy_num].output_idx++;
			}
			else
			{
				enemy[enemy_num].y = hih * 0.6 - 400 + 66;
				if(flag <= 0)
					flag = 80;
				flag--;
				
				int table[2] = {0, 2};
				
				if(enemy[enemy_num].dir == 'a')
				{
					enemy[enemy_num].output_idx = table[flag / 40 ] + 1;
				}
				else
				{
					enemy[enemy_num].output_idx = table[flag / 40 ];
				}
			}
			break;

		default :
			break;
	}
}