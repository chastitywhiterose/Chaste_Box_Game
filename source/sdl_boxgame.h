/*
sdl_graphics.h

this header file is meant to contain all the important functions which write things to the screen
*/



int rectsize=16;
int palette[2];

/*set up initial checkerboard values*/
void checker_init()
{
 rectsize=16;
 palette[0]=SDL_MapRGB(surface->format,0,0,0);
 palette[1]=SDL_MapRGB(surface->format,255,255,255);
}

/*fill with a checkerboard whatever is the current surface pointed to*/
void chaste_checker()
{
 int index,index1;
 int width=surface->w;
 int height=surface->h;
 SDL_Rect rect;
 rect.w = rectsize;
 rect.h = rectsize;
 index=0;
 rect.y = 0;
 while(rect.y<height)
 {
  index1=index;
  rect.x = 0;
  while(rect.x<width)
  {
   SDL_FillRect(surface,&rect,palette[index]);
   index^=1;
   rect.x+=rectsize;
  }
  index=index1^1;
  rect.y+=rectsize;
 }
}






/*
 this function is now the official welcome screen.
 It can show text or other things on a screen that will stay there until I press a key.
*/
void boxgame_title()
{
 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;

 sprintf(text,"Chaste Box Game");
 /*chaste_font_draw_string(text,text_x,main_font.char_height*1);*/
 chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

  sprintf(text,"The game where everything is a rectangle!");
 chaste_font_draw_string_scaled(text,text_x,3*main_font.char_height*text_scale,4);
   sprintf(text,"Press any key to begin!");
 chaste_font_draw_string_scaled(text,text_x,4*main_font.char_height*text_scale,4);

 SDL_UpdateWindowSurface(window); /*update the screen*/

 while(e.type != SDL_KEYUP && e.type != SDL_QUIT) /*wait until any key is pressed and then released*/
 {
  SDL_PollEvent( &e );
 }

}



void level_1_rectangles()
{
 blocks_count=0;
 
 add_block(rectsize*0,height-rectsize*1,rectsize*80,rectsize*1);
 
 add_block(rectsize*0,rectsize*40,rectsize*41,rectsize*1);
 
 add_block(rectsize*30,rectsize*30,rectsize,rectsize*10);
 
 add_block(rectsize*40,rectsize*20,rectsize,rectsize*20);
 
 add_block(rectsize*50,rectsize*20,rectsize*10,rectsize*1);

 add_block(rectsize*60,rectsize*30,rectsize*10,rectsize*1);


}




/*
 The very first level. This is the start of it all.
*/
void boxgame_level_1()
{
 level_1_rectangles();

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 delay=1000/fps;
 
 /*set up the values of the player*/
 player.color=SDL_MapRGB(surface->format,255,255,0);
 player.size=rectsize;
 player.rect.x=8*player.size;
 player.rect.y=16*player.size;
 player.rect.w=player.size;
 player.rect.h=player.size;
 player.xstep=0;
 player.ystep=1;
 player.jump_time=0;
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  time = SDL_GetTicks();
  time1 = time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level 1");
  /*chaste_font_draw_string(text,text_x,main_font.char_height*1);*/
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

  /*sprintf(text,"Move the square with arrows.");
  chaste_font_draw_string_scaled(text,text_x,3*main_font.char_height*text_scale,4);*/

  
  player_update();
  
  draw_blocks(); /*draw walls*/
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

  keyboard();
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(time<time1)
  {
   /*time=SDL_GetTicks();*/
   time=time1;
  }
  
 }

}





