#include <stdlib.h>
#include <stdio.h>


#include "pacman.h"

static const char initial_field[24][23] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
	{ 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0 },
	{ 0, 5, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 5, 0 },
	{ 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
	{ 0, 3, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 3, 0 },
	{ 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 3, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 3, 1, 1, 1, 1, 1 },
	{ 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 3, 0, 0, 0, 0, 0 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
	{ 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0 },
	{ 0, 5, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 5, 0 },
	{ 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0 },
	{ 0, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 0 },
	{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
	{ 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 },
	{ 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
static int x = 0;

static char field_dots[24][23];
static char field_pups[24][23];

static const int bot_r[4] = {205,128,190,0  };
static const int bot_g[4] = {0  ,0  ,160,228};
static const int bot_b[4] = {128,205,30 ,155};

struct pos_t
{
	signed int x;
	signed int y;
};

struct bot_t
{
	struct pos_t pos;
	int orientation;
	int dying;
};

static struct bot_t bots[4];
static struct bot_t player;

#define DOOR_X 10
#define DOOR_Y 11

static int door = 0;
static int pupmode = 0;
static int hurt = 0;
static int lives = 4;
static int eaten = 0;
static int levels = 0;

void pacman_init(void)
{
	x=0;
	door = 0;
	pupmode = 0;
	hurt = 0;
	lives = 4;
	eaten = 0;


	bots[0].pos.x = 9;
	bots[0].pos.y = 11;
	bots[0].orientation=1;
	bots[1].pos.x = 11;
	bots[1].pos.y = 11;
	bots[1].orientation=1;
	bots[2].pos.x = 11;
	bots[2].pos.y = 10;
	bots[2].orientation=1;
	bots[3].pos.x = 11;
	bots[3].pos.y = 12;
	bots[3].orientation=1;
	player.pos.x = 17;
	player.pos.y = 11;
	player.orientation=1;


	for(int x=0;x<24;x++)
		for(int y=0;y<23;y++)
		{
			if((initial_field[x][y]&2)==2)
				field_dots[x][y]=1;
			else
				field_dots[x][y]=0;
			
			if((initial_field[x][y]&4)==4)
				field_pups[x][y]=1;
			else
				field_pups[x][y]=0;
		}
				
}

struct pos_t translate(struct pos_t start,int orientation)
{
	struct pos_t target;

	if(orientation==0)
	{
		target.x=start.x+1;
		target.y=start.y;
	}
	if(orientation==1)
	{
		target.x=start.x;
		target.y=start.y+1;
	}
	if(orientation==2)
	{
		target.x=start.x-1;
		target.y=start.y;
	}
	if(orientation==3)
	{
		target.x=start.x;
		target.y=start.y-1;
	}

	if(target.y>22)
		target.y=0;
	if(target.x>23)
		target.x=0;
	if(target.x<0)
		target.x=23;
	if(target.y<0)
		target.y=22;

	return target;
}


int check(struct pos_t start,int orientation)
{

	struct pos_t target = translate(start,orientation);

	if((door==0)&&(target.x==DOOR_X)&&(target.y)==DOOR_Y)
	{
		return 0;
	}


	if(( initial_field[target.x][target.y] & 1) == 1)
	{
		return 1;
	}

	return 0;
	
}

void move(struct pos_t start,int orientation,struct pos_t* target)
{
	struct pos_t new = translate(start,orientation);
	target->x=new.x;
	target->y=new.y;
}

static int rotate_left(int orientation)
{
	if(orientation == 0)
	{
		return 3;
	}
	else
	{
		return orientation-1;
	}
}

static int rotate_right(int orientation)
{
	if(orientation == 3)
	{
		return 0;
	}
	else
	{
		return orientation+1;
	}
}
static int rotate_full(int orientation)
{
	if(orientation > 1)
	{
		return orientation - 2;
	}
	else
	{
		return orientation + 2;
	}
}

static int look(struct pos_t pos,int orientation)
{

	struct pos_t target;

	target = translate(pos,orientation);

	if((player.pos.x == target.x)&&(player.pos.y == target.y))
	{
		return 1;
	}
	if(initial_field[target.x][target.y] == 0)
	{
		return 0;
	}
	return look(target,orientation);

}


static void movebot(struct bot_t* bot)
{

	if(bot->dying > 0)
	{
		return;
	}

	struct pos_t target;

	int option_count = 0;
	int options[3];

	if(check(bot->pos,bot->orientation))
	{
		options[option_count]=1;
		option_count++;
	}
	if(check(bot->pos,rotate_left(bot->orientation)))
	{
		options[option_count]=2;
		option_count++;
	}
	if(check(bot->pos,rotate_right(bot->orientation)))
	{
		options[option_count]=3;
		option_count++;
	}

	if(option_count == 0)
	{
		bot->orientation = rotate_full(bot->orientation);
		return;
	}

	if(look(bot->pos,bot->orientation))
	{
		option_count=1;
		options[0]=1;
	}
	else if(look(bot->pos,rotate_left(bot->orientation)))
	{
		option_count=1;
		options[0]=2;
	}
	else if(look(bot->pos,rotate_right(bot->orientation)))
	{
		option_count=1;
		options[0]=3;
	}


	int selected =	rand()%option_count;

	if(options[selected]==1)
	{
		move(bot->pos,bot->orientation,&target);
		bot->pos = target;
	}
	if(options[selected]==2)
	{
		move(bot->pos,rotate_left(bot->orientation),&target);
		bot->orientation = rotate_left(bot->orientation);
		bot->pos = target;
	}
	if(options[selected]==3)
	{
		move(bot->pos,rotate_right(bot->orientation),&target);
		bot->orientation = rotate_right(bot->orientation);
		bot->pos = target;
	}



}

static void eat(struct pos_t pos)
{
	if(field_dots[pos.x][pos.y]==1)
	{
		eaten++;
		field_dots[pos.x][pos.y]=0;
	}
	if(field_pups[pos.x][pos.y]==1)
	{
		field_pups[pos.x][pos.y]=0;
		pupmode=100;
		for(int i =0;i<4;i++)
			bots[i].orientation = rotate_full(bots[i].orientation);
	}
}

static int check_collision(struct bot_t *bot,struct bot_t *player)
{
	if((bot->pos.x == player->pos.x)&&(bot->pos.y == player->pos.y))
	{
		return 1;
	}
	return 0;
}



static void collision_check(void)
{
	for(int i =0;i<4;i++)
		if(check_collision(&bots[i],&player))
		{
			if(pupmode)
			{
				if(bots[i].dying==0)
				{
					bots[i].dying=25;
				}
			}
			else
			{
				if(hurt==0)
				{
					lives--;
					hurt = 30;
				}
			}
		}

}


void pacman_tick(int getkey(int)) {

	x++;


	if(eaten==191)
	{
		pacman_init();
		levels++;
	}
	
	if(lives==0)
	{
		pacman_init();
		levels = 0;
		return;
	}

	
	for(int i = 0;i<4;i++)
	{
		if(bots[i].dying > 1)
		{
			bots[i].dying--;
		}
		if(bots[i].dying == 1)
		{
			bots[i].dying=0;
			bots[i].pos.x=11;
			bots[i].pos.y=10;
		}
	}



	if((pupmode)&&(x%3))
	{
	}
	else
	{
		if((x%7) == 0) movebot(&bots[0]);
		if((x%8) == 0) movebot(&bots[1]);
		if((x%9) == 0) movebot(&bots[2]);
		if((x%10) == 0) movebot(&bots[3]);
	}


	collision_check();

	if((x%4) == 0)
	{
		
		if(getkey(0))
		{
			if(check(player.pos,2))
			{
				struct pos_t target;
				move(player.pos,2,&target);
				player.pos = target;
			}
		}
		if(getkey(2))
		{
			if(check(player.pos,0))
			{
				struct pos_t target;
				move(player.pos,0,&target);
				player.pos = target;
			}
		}
		if(getkey(3))
		{
			if(check(player.pos,3))
			{
				struct pos_t target;
				move(player.pos,3,&target);
				player.pos = target;
			}
		}
		if(getkey(1))
		{
			if(check(player.pos,1))
			{
				struct pos_t target;
				move(player.pos,1,&target);
				player.pos = target;
			}
		}



	}
	//	movebot(&player);

	collision_check();

	if(pupmode > 0)
		if((x%2)==0)	pupmode--;
	if(hurt > 0)
		if((x%2)==0)	hurt--;

	
	if((x%100) == 0) door = 1;
	if((x%100) == 15) door = 0;

	eat(player.pos);


	return;
}

static void set_block(unsigned int* pixelbuffer,unsigned int zoom,unsigned int x,unsigned int y,unsigned int r,unsigned int g,unsigned int b)
{
		unsigned int col = (r<<16)+(g<<8)+b;


		for(unsigned int a = 0; a < zoom-1;a++)
		{
			for(unsigned int b = 0;b < zoom-1;b++)
			{
				pixelbuffer[((x*zoom+a)*23*zoom)+y*zoom+b] = col;
			}
		}
	
}


void pacman_render(unsigned int* pixelbuffer,int zoom)
{
//	lcdFillRGB(0,0,0);
	
	for(int x =0;x<24;x++)
		for(int y=0;y<23;y++)
		{
			if(field_dots[x][y]==1)
			{
				set_block(pixelbuffer,zoom,x,y,32,200,32);
			}
			else if(field_pups[x][y]==1)
			{
				set_block(pixelbuffer,zoom,x,y,64,220,220);
			}
			else if(initial_field[x][y]==0)
			{
				set_block(pixelbuffer,zoom,x,y,20,20,220);
			}
			else
			{
				set_block(pixelbuffer,zoom,x,y,20,20,20);
			}
		}

	if(door==0)
		set_block(pixelbuffer,zoom,DOOR_X,DOOR_Y,120,50,160);
	
	for(int i = 0;i<4;i++)
	{
		int r = bot_r[i];
		int g = bot_g[i];
		int b = bot_b[i];

	
		if((bots[i].dying%2)==1)
		{
			r=255;
			g=255;
			b=255;
		}
		else if(pupmode>20)
		{
			if(pupmode%2)
			{
				r = 264;
				g = 32;
				b = 148;
			}
			else
			{
				r=32;
				g=164;
				b=248;
			}
		}
		else if(pupmode)
		{
			if(pupmode%2)
			{
				r = 264;
				g = 32;
				b = 148;
			}
		}
		set_block(pixelbuffer,zoom,bots[i].pos.x,bots[i].pos.y,r,g,b);
	}

	if(hurt%2)
	{
		set_block(pixelbuffer,zoom,player.pos.x,player.pos.y,64,64,0);
	}
	else
	{
		set_block(pixelbuffer,zoom,player.pos.x,player.pos.y,255,255,0);
	}

	for(int i = 0;i<24;i++)
	{
	//	if(levels>i)
			//setLedXY(0,i,255,255,255);
	}
	for(int i = 0;i<(lives-1);i++)
	{
		set_block(pixelbuffer,zoom,13,1+i,255,255,0);
	}

}


