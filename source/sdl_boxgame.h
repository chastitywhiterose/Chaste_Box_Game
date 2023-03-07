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
   sprintf(text,"Press enter key to begin!");
 chaste_font_draw_string_scaled(text,text_x,4*main_font.char_height*text_scale,4);

 SDL_UpdateWindowSurface(window); /*update the screen*/

 loop=1;
 while(loop)
 {
  SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0;}
  if(e.type == SDL_KEYUP)
  {
   if(e.key.keysym.sym==SDLK_RETURN){loop=0;}
   if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
  }
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
 
 player_init(); /*must init player before starting level*/
 
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





void level_2_rectangles()
{
 blocks_count=0;
 
 add_block(rectsize*0,height-rectsize*1,rectsize*80,rectsize*1);


}




/*
 The second level. I have no idea what kind of game I am making!
*/
void boxgame_level_2()
{
 level_2_rectangles();

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 delay=1000/fps;
 
 player_init(); /*must init player before starting level*/
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  time = SDL_GetTicks();
  time1 = time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level 2");
  /*chaste_font_draw_string(text,text_x,main_font.char_height*1);*/
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

  /*sprintf(text,"Move the square with arrows.");
  chaste_font_draw_string_scaled(text,text_x,3*main_font.char_height*text_scale,4);*/

  /*chaste_font_draw_string("This text is tiny. LOL",main_font.char_height*100,main_font.char_height*100);*/
  
  chaste_font_draw_string_pixels("Chastity White Rose",main_font.char_height*100,main_font.char_height*100);
  
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



