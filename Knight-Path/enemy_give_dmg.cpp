// enemy_give_damage
#include "lib/var.h"
#include "lib/player_move.h"
#include "lib/enemy_give_dmg.h"
 
extern int key, atk_cnt, player_walk_cnt, flag, enemy_atk_cnt, enemy_atk_type, player_enemy_dir, atked, enemy_num, player_jump_cnt, get_dmg_cnt;
extern double start, end;
extern Human player;
extern Monster enemy[3];
extern Bullet skill[6];
int is_middle(int up, int pos, int down);

void enemy_give_dmg()
{
	switch(enemy_atk_type)
	{
		case 0:
			case_0();
			break;
			
		case 1:
			case_1();
			break;
		
		case 2:
			case_2();
			break;
		
		case 3:
			case_3();
			break;
		
		case 4:
			case_4();
			break;

		case 5:
			case_5();
			break;

		case 6:
			case_6();
			break;

		case 7:
			case_7();
			break;

		case 8:
			case_8();
			break;

		case 9:
			case_9();
			break;

		case 10:
			case_10();

		default :
			break;
	}
}

// �Ω�P�_ pos �O�_�b up �M down ���� 
int is_middle(int up, int pos, int down)
{
	if(up >= pos && pos >= down)
		return 1;
	return 0;
}

void case_0()
{
	if(enemy[enemy_num].dir == 'a')
	{
		// �P�w���a�O�_�b�ĤH�������d�� 
		if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 1.1, player.x + player.width / 2, enemy[enemy_num].x - enemy[enemy_num].width / 10)
		&& (enemy[enemy_num].output_idx == 4 || enemy[enemy_num].output_idx == 5))
		{
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x -= enemy[enemy_num].power;
			get_dmg_cnt = 1;
		}
		
		// �P�w���a�O�_�b�ĤH���ޯ�d�� 
		if(skill[0].status && is_middle(skill[0].x + skill[0].width, player.x + player.width / 2, skill[0].x))
		{
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x -= skill[0].power;
			//skill[0].status = 0;
			get_dmg_cnt = 1;

			if(player_jump_cnt == -1)
				player_jump_cnt = 15;
			jump();
		}
	}
	else
	{
		// player.x > enemy.x + 64 && enemy.x + 165 > player.x
		if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width, player.x + player.width / 2, enemy[enemy_num].x)
		&& (enemy[enemy_num].output_idx == 4 || enemy[enemy_num].output_idx == 5))
		{
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x += enemy[enemy_num].power;
			get_dmg_cnt = 1;
		}
		
		if(skill[0].status && is_middle(skill[0].x + skill[0].width, player.x + player.width / 2, skill[0].x))
		{
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x += skill[0].power;
			//skill[0].status = 0;
			get_dmg_cnt = 1;

			if(player_jump_cnt == -1)
				player_jump_cnt = 15;
			jump();
		}
	}	
}

void case_1()
{
	if(is_middle(62, enemy_atk_cnt, 56))
	{
		//player.x >= enemy.x && player.x <= enemy.x + 165
		if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width, player.x + player.width / 2, enemy[enemy_num].x))
		{
			//player.y - 10 > enemy.y - 165
			if(is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 1.5, player.y + player.high / 2, enemy[enemy_num].y))
			{
				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
				get_dmg_cnt = 1;

				if(enemy[enemy_num].dir == 'a')
					player.x -= enemy[enemy_num].power;
				else
					player.x += enemy[enemy_num].power;	
				if(player_jump_cnt == -1)
					player_jump_cnt = 15;
				jump();
			}	
		}	
	}
	
	//printf("%d %d %d %d\n", skill[1].x, player.x + player.width / 2, skill[1].x + skill[1].width / 10, is_middle(skill[1].x, player.x + player.width / 2, skill[1].x + skill[1].width / 10));
	// ���ޯ�����S�� �@���@���|�ӽd��y���ˮ` �G�������k��� 
	if(is_middle(56, enemy_atk_cnt, 0))
	{
		// �� 
		if(is_middle(skill[1].x + skill[1].width / 10, player.x + player.width / 2, skill[1].x) == 1
		|| is_middle(skill[1].x + skill[1].width * 30 / 100, player.x + player.width / 2, skill[1].x + skill[1].width * 21 / 100) == 1)
		{
			if(player_jump_cnt == -1)
				player_jump_cnt = 15;
			jump();
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x -= skill[1].power;
			skill[1].status = 0;
			get_dmg_cnt = 1;
		}
		// �k 
		else if(is_middle(skill[1].x + skill[1].width * 84 / 100, player.x + player.width / 2, skill[1].x + skill[1].width * 74 / 100) == 1
			 || is_middle(skill[1].x + skill[1].width, player.x + player.width / 2, skill[1].x + skill[1].width * 9 / 10) == 1)
		{
			if(player_jump_cnt == -1)
				player_jump_cnt = 15;
			jump();
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			player.x += skill[1].power;
			skill[1].status = 0;
			get_dmg_cnt = 1;
		}
	}	
}

void case_2()
{
	if(enemy_atk_cnt < 60)
	{
		if(is_middle(skill[2].y + 80, player.y + player.high / 2, skill[2].y + 40)
		&& is_middle(skill[2].x + 85, player.x + player.width / 2, skill[2].x + 70))
		{
			player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
			get_dmg_cnt = 1;

			if(player_jump_cnt == -1)
				player_jump_cnt = 15;
			jump();
			
			if(enemy[0].dir == 'a')
				player.x -= skill[2].power;
			else
				player.x += skill[2].power;
			
			skill[2].status = 0;
		}
	}
}

void case_3()
{
	if(is_middle(skill[3].x + skill[3].width * 0.8, player.x + player.width / 2, skill[3].x + skill[3].width * 0.2)
	&& is_middle(skill[3].y + skill[3].high * 0.8, player.y + player.high / 3, skill[3].y + skill[3].high * 0.1))
	{
		player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
		get_dmg_cnt = 1;

		if(player_jump_cnt == -1)
			player_jump_cnt = 15;
		jump();
		
		if(enemy[enemy_num].dir == 'a' && (player.x > 10))
		{
			player.x -= skill[3].power;
		}
		else if(enemy[enemy_num].dir == 'd' && player.x + 10 < wid)
			player.x += skill[3].power;
		
		skill[2].status = 0;
	}	
}

void case_4()
{
	if(is_middle(skill[4].x + skill[4].width * 0.9, player.x + player.width / 2, skill[4].x + skill[4].width * 0.1)
	&& enemy_atk_cnt < 37)
	{
		player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
		get_dmg_cnt = 1;
		
		if(player_jump_cnt == -1)
			player_jump_cnt = 15;
		jump();

		if(enemy[enemy_num].dir == 'a' && (player.x > 10))
		{
			player.x += skill[4].power;
		}
		else if(enemy[enemy_num].dir == 'd' && player.x + 10 < wid)
			player.x -= skill[4].power;
	}
}

void case_5()
{
	if(is_middle(skill[5].x + skill[5].width , player.x + player.width / 2, skill[5].x)
	&& (player.y + player.high * 0.2 < skill[5].y + skill[5].high * 0.9))
	{
		player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;
		get_dmg_cnt = 1;

		if(enemy[enemy_num].dir == 'a' && (player.x > 10))
			player.x += skill[5].power;
		else if(enemy[enemy_num].dir == 'd' && player.x + 10 < wid)
			player.x -= skill[5].power;
	} 
}

void case_6()
{
	if(enemy_atk_cnt <= 10)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.95, player.x + player.width * 0.3, enemy[enemy_num].x + enemy[enemy_num].width * 0.35)
			|| is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.95, player.x + player.width * 0.7, enemy[enemy_num].x + enemy[enemy_num].width * 0.35))
			&& (is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high * 0.3, enemy[enemy_num].y + enemy[enemy_num].high * 0.7)
			||  is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high, enemy[enemy_num].y + enemy[enemy_num].high * 0.7)))
			{
				if(player_jump_cnt == -1)
					player_jump_cnt = 15;
				jump();
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(enemy[enemy_num].dir == 'd' && player_move_check('d', enemy[enemy_num].power) == 1)
					player.x += enemy[enemy_num].power;
				//else if(enemy[enemy_num].dir == 'a' && player_move_check('a', enemy[enemy_num].power) == 1)
					//player.x -= enemy[enemy_num].power;
			}
		}
		else
		{
			if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.35, player.x + player.width * 0.3, enemy[enemy_num].x + enemy[enemy_num].width * 0.05)
			|| is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.35, player.x + player.width * 0.7, enemy[enemy_num].x + enemy[enemy_num].width * 0.05))
			&& (is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high * 0.3, enemy[enemy_num].y + enemy[enemy_num].high * 0.7)
			||  is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high, enemy[enemy_num].y + enemy[enemy_num].high * 0.7)))
			{
				if(player_jump_cnt == -1)
					player_jump_cnt = 15;
				jump();
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(enemy[enemy_num].dir == 'a' && player_move_check('a', enemy[enemy_num].power) == 1)
					player.x -= enemy[enemy_num].power;
			}
		}
	}
}

void case_7()
{
	if(enemy_atk_cnt < 16)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.6, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.1)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 0.4, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.1))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(enemy[enemy_num].dir == 'd' && player_move_check('d', enemy[enemy_num].power) == 1)
					player.x += enemy[enemy_num].power;
			}
		}
		else
		{
			if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.9, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.4)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 0.4, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.1))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(enemy[enemy_num].dir == 'a' && player_move_check('a', enemy[enemy_num].power) == 1)
					player.x -= enemy[enemy_num].power;
			}
		}
	}
	
	if(enemy_atk_cnt < 8)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.95, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.75)
			&&(is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high / 4, enemy[enemy_num].y + enemy[enemy_num].high * 0.3)))
			|| (is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.75, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.6)
			&&(is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 0.7, player.y + player.high / 4, enemy[enemy_num].y + enemy[enemy_num].high * 0.5))))
			{
				get_dmg_cnt = 1;
			
				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('d', enemy[enemy_num].power * 2) == 1)
					player.x += enemy[enemy_num].power * 2;
			}
		}
		else
		{
			if((is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.25, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.05)
			&&(is_middle(enemy[enemy_num].y + enemy[enemy_num].high, player.y + player.high / 4, enemy[enemy_num].y + enemy[enemy_num].high * 0.3)))
			|| (is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.4, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.25)
			&&(is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 0.7, player.y + player.high / 4, enemy[enemy_num].y + enemy[enemy_num].high * 0.5))))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('a', enemy[enemy_num].power * 2) == 1)
					player.x -= enemy[enemy_num].power * 2;
			}
		}
	}
}

void case_8()
{
	if(enemy_atk_cnt < 8)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			judge_dmg(0.5, 0.5, 0.95, 0.6, 0.8, 0.65, 0, 0, 0, 0,0, enemy[enemy_num].dir, 0);
			/*if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.95, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.6)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 8, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.65))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('d', enemy[enemy_num].power) == 1)
					player.x += enemy[enemy_num].power;
			}*/
		}
		else
		{
			judge_dmg(0.5, 0.5, 0.4, 0.05, 0.8, 0.65, 0, 0, 0, 0,0, enemy[enemy_num].dir, 0);
			/*if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.4, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.05)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 8, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.65))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('a', enemy[enemy_num].power) == 1)
					player.x -= enemy[enemy_num].power;
			}*/
		}
	}
	else if(enemy_atk_cnt < 16)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			judge_dmg(0.5, 0.5, 0.55, 0.4, 0.85, 0.7, 0, 0, 0, 0,0, enemy[enemy_num].dir, 0);
			/*if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.55, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.4)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 85, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.7))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('d', enemy[enemy_num].power) == 1)
					player.x += enemy[enemy_num].power;
			}*/
		}
		else
		{
			judge_dmg(0.5, 0.5, 0.6, 0.45, 0.85, 0.7, 0, 0, 0, 0,0, enemy[enemy_num].dir, 0);
			/*if(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * 0.6, player.x + player.width / 2, enemy[enemy_num].x + enemy[enemy_num].width * 0.45)
			&& is_middle(enemy[enemy_num].y + enemy[enemy_num].high * 85, player.y + player.high / 2, enemy[enemy_num].y + enemy[enemy_num].high * 0.7))
			{
				get_dmg_cnt = 1;

				player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

				if(player_move_check('a', enemy[enemy_num].power) == 1)
					player.x -= enemy[enemy_num].power;
			}*/
		}
	}
}

void case_9()
{
	if(enemy_atk_cnt < 8)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			judge_dmg(0.5, 0.5, 0.95, 0.75, 1, 0.6, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 1);
		}
		else
		{
			judge_dmg(0.5, 0.5, 0.25, 0.05, 1, 0.6, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 1);
		}
	}
	else if(enemy_atk_cnt < 16)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			judge_dmg(0.5, 0.5, 0.75, 0.4, 1, 0.7, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 0);
		}
		else
		{
			judge_dmg(0.5, 0.5, 0.6, 0.25, 1, 0.7, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 0);
		}
	}
}

void case_10()
{
	if(enemy_atk_cnt < 8)
	{
		if(enemy[enemy_num].dir == 'd')
		{
			judge_dmg(0.5, 0.5, 0.75, 0.6, 1, 0, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 1);
		}
		else
		{
			judge_dmg(0.5, 0.5, 0.4, 0.25, 1, 0, 0, 0, 0, 0, 0, enemy[enemy_num].dir, 1);
		}
	}
}

void judge_dmg(double player_x, double player_y, double fir_up_x, double fir_dw_x, double fir_up_y, double fir_dw_y, int sec, double sec_up_x, double sec_dw_x, double sec_up_y, double sec_dw_y, char dir, int jum)
{
	int first = 0, second = 0;

	if(!(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * fir_up_x, player.x + player.width * player_x, enemy[enemy_num].x + enemy[enemy_num].width * fir_dw_x) && is_middle(enemy[enemy_num].y + enemy[enemy_num].high * fir_up_y, player.y + player.high * player_y, enemy[enemy_num].y + enemy[enemy_num].high * fir_dw_y)))
		first = 1;
	if(sec == 1)
		if(!(is_middle(enemy[enemy_num].x + enemy[enemy_num].width * sec_up_x, player.x + player.width * player_x, enemy[enemy_num].x + enemy[enemy_num].width * sec_dw_x) && is_middle(enemy[enemy_num].y + enemy[enemy_num].high * sec_up_y, player.y + player.high * player_y, enemy[enemy_num].y + enemy[enemy_num].high * sec_dw_y)))
			second= 1;
	
	if(!sec && first)
		return ;
	if(sec && first && second)
		return ;
		
	get_dmg_cnt = 1;

	player.hp = (player.hp - enemy[enemy_num].damage) > 0 ? player.hp - enemy[enemy_num].damage : 0;

	if(player_move_check(dir, enemy[enemy_num].power) == 1)
		player.x -= enemy[enemy_num].power;
	
	if(jum)
	{
		if(player_jump_cnt == -1)
			player_jump_cnt = 15;
		jump();
	}
}
