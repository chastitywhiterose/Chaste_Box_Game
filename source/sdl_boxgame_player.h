/*sdl_boxgame_player.h*/

struct box_player
{
 int size,color;
 SDL_Rect rect;
 int xstep,ystep;
 int jump_time;
};

struct box_player player,temp_player;
int player_max_jump=256;
int player_max_jumps=2;
int player_jumps=2;

int pstep=1;

/*set up default values for player at start of a level*/
void player_init()
{
 /*set up the values of the player*/
 player.color=SDL_MapRGB(surface->format,255,255,0);
 player.size=16;
 player.rect.x=1*player.size;
 player.rect.y=height-player.size*2;
 player.rect.w=player.size;
 player.rect.h=player.size;
 player.xstep=0;
 player.ystep=1;
 player.jump_time=0;
 
 
}

/*
void move_left()
{
 player.rect.x-=player.xstep;
}

void move_right()
{
 player.rect.x+=player.xstep;
}

void move_up()
{
 player.rect.y-=pstep;
}

void move_down()
{
 player.rect.y+=pstep;
}
*/













/*checks the array of blocks for collision with player*/
int player_touches_any_block()
{
 int i=0;
 while(i<blocks_count)
 {
  if(SDL_HasIntersection(&player.rect, &blocks[i]))
  {
   return 1;
  }
  i++;
 }
 
 return 0;
}








void player_update()
{
 temp_player=player; /*backup player in case we need to reset something*/  

 /*update the x*/
 player.rect.x+=player.xstep;
 
 if(player_touches_any_block())
 {
  /*printf("Collision after x change!\n");*/
  player.rect.x=temp_player.rect.x;
 }
 
  /*if move horizontally off screem come back at other side*/
  if(player.rect.x>=width){player.rect.x=0; game_level++; loop=0;}
  if(player.rect.x<0){player.rect.x=width-player.rect.w; game_level--; loop=0;}

 /*update the y depending on if we are currently jumping.*/
 if(player.jump_time!=0)
 {
  player.jump_time--;
  player.rect.y-=player.ystep;
 }
 else
 {
  player.rect.y+=player.ystep;
 }
 
 if(player_touches_any_block())
 {
  /*printf("Collision after y change!\n");*/
  player.rect.y=temp_player.rect.y;
  player_jumps=player_max_jumps;
 }
 
   /*if move vertically off screem come back at other side*/
  if(player.rect.y>=height){player.rect.y=0;}
  if(player.rect.y<0){player.rect.y=height-player.rect.w;}

 
}
