/*sdl_boxgame_player.h*/

struct box_player
{
 int size,color;
 SDL_Rect rect;
 int xstep,ystep;
 int jump_time;
};

struct box_player player,temp_player;

int pstep=1;

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

void player_update()
{
 if(player.jump_time!=0)
 {
  player.jump_time--;
  player.rect.y-=player.ystep;
 }
 else
 {
  player.rect.y+=player.ystep;
 }
}
