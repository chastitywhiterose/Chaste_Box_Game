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

int fps_current; /*only used when I am debugging the game*/

void fps_test()
{
 time(&std_time_now);
 
 seconds=std_time_start-std_time_now; /*subtract current time from start time to get seconds since game started*/
  
  sprintf(text,"Frame %d",frame);
  chaste_font_draw_string(text,text_x,main_font.char_height*15);
  
  if(seconds!=0)
  {
   fps_current=frame/seconds;
   sprintf(text,"FPS %d",fps_current);
   chaste_font_draw_string(text,text_x,main_font.char_height*16);
  }
 
 frame++;
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
 
 chaste_font_draw_string_scaled_color("Party",text_x,main_font.char_height*80,4,0xFF0000);
 chaste_font_draw_string_scaled_color("on",text_x+main_font.char_width*30,main_font.char_height*80,4,0x00FF00);
 chaste_font_draw_string_scaled_color("dudes!",text_x+main_font.char_width*50,main_font.char_height*80,4,0x0000FF);


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
 
 add_block(rectsize*0,height-rectsize*1,rectsize*80,rectsize*1); /*bottom floor*/
 
 add_block(rectsize*0,rectsize*0,rectsize*1,rectsize*44); /*bottom floor*/

 
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
 

 
 
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level %d",game_level);
  /*chaste_font_draw_string(text,text_x,main_font.char_height*1);*/
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

  sprintf(text,"Move the square with arrows");
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*35,4);
  sprintf(text,"Space bar to jump");
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*40,4);

  
  player_update();
  
  draw_blocks(); /*draw walls*/
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
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
 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 chaste_font_draw_string_pixels_scaled_add_boxes("Chastity White Rose",main_font.char_width*10,main_font.char_height*50,16);
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level %d",game_level);
  /*chaste_font_draw_string(text,text_x,main_font.char_height*1);*/
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

  sprintf(text,"This game programmed by");
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*40,4);

  /*chaste_font_draw_string("Chastity White Rose",main_font.char_width*100,main_font.char_height*100);*/
  
  /*chaste_font_draw_string_pixels("Chastity White Rose",main_font.char_width*50,main_font.char_height*100);*/
  
  draw_blocks(); /*draw walls*/
  
  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_pixels_scaled_rainbow("Chastity White Rose",main_font.char_width*10,main_font.char_height*50,16);

  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
 
  player_update();
      
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  
   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}







/*
 The third level. I have no idea what kind of game I am making!
*/
void boxgame_level_3()
{


 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_2_rectangles();
 chaste_font_draw_string_pixels_scaled_add_boxes("Chaste the Rainbow",main_font.char_width*10,main_font.char_height*50,16);
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level %d",game_level);
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);

/*  sprintf(text,"This game programmed by");
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*40,4);*/

  /*chaste_font_draw_string("Chastity White Rose",main_font.char_width*100,main_font.char_height*100);*/
  
  /*chaste_font_draw_string_pixels("Chastity White Rose",main_font.char_width*50,main_font.char_height*100);*/
  
  draw_blocks(); /*draw walls*/
  
  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_pixels_scaled_rainbow("Chaste the Rainbow",main_font.char_width*10,main_font.char_height*50,16);

  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
 
  player_update();
  

    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}






/*

*/
void boxgame_level_4()
{
 level_2_rectangles();

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 
 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/


 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level %d",game_level);
  /*chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);*/

  sprintf(text,"But most of the sdl_time the text will be\nwhite because it is easier to read");
  chaste_font_draw_string_scaled(text,main_font.char_width*8,main_font.char_height*48,8);

  /*chaste_font_draw_string("Chastity White Rose",main_font.char_width*100,main_font.char_height*100);*/
  
  /*chaste_font_draw_string_pixels("Chastity White Rose",main_font.char_width*50,main_font.char_height*100);*/
  
  chaste_palette_index=chaste_palette_index1;
  chaste_font_draw_string_pixels_scaled_rainbow("Made with the C Programming Language\nand SDL.\n\nRainbow text made with Chastity's\nfabulous direct pixel access!",main_font.char_width*8,main_font.char_height*1,8);

  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
 
  player_update();
  
  draw_blocks(); /*draw walls*/
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}




void level_5_rectangles()
{
 blocks_count=0;
 
 add_block(rectsize*0,height-rectsize*1,rectsize*80,rectsize*1);



}




/*

*/
void boxgame_level_5()
{

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

  level_5_rectangles();

  sprintf(text,"You can jump\non this text!");
  chaste_font_draw_string_pixels_scaled_add_boxes(text,main_font.char_width*32,main_font.char_height*64,16);
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  sprintf(text,"Level %d",game_level);
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);
  



  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
 
  player_update();
  
  draw_blocks(); /*draw walls*/
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}








void boxgame_level_6()
{

 main_font=font_pico8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_5_rectangles();

 sprintf(text,"Rainbow\nPro Life\nAlliance");
 chaste_font_draw_string_pixels_scaled_add_boxes(text,main_font.char_width*64,main_font.char_height*8,24);
  
 sprintf(text,"LGBTQ+ Rights Start at Conception");
 chaste_font_draw_string_pixels_scaled_add_boxes(text,main_font.char_width*16,main_font.char_height*96,8);
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

/*  sprintf(text,"Level %d",game_level);
  chaste_font_draw_string_scaled(text,text_x,1*main_font.char_height*text_scale,text_scale);*/
  

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  chaste_palette_index=chaste_palette_index1;
  
  sprintf(text,"Rainbow\nPro Life\nAlliance");
  chaste_font_draw_string_pixels_scaled_rainbow(text,main_font.char_width*64,main_font.char_height*8,24);
  
  sprintf(text,"LGBTQ+ Rights Start at Conception");
  chaste_font_draw_string_pixels_scaled_rainbow(text,main_font.char_width*16,main_font.char_height*96,8);
  
  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}



void boxgame_level_7()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 

 
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_5_rectangles();

 sprintf(text,"Rainbow\nPro Life\nAlliance");
 /*chaste_font_draw_string_pixels_scaled_add_boxes(text,main_font.char_width*64,main_font.char_height*8,24);*/
  
 sprintf(text,"LGBTQ+ Rights Start at Conception");
 chaste_font_draw_string_pixels_scaled_add_boxes(text,main_font.char_width*16,main_font.char_height*96,8);
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  chaste_palette_index=chaste_palette_index1;
  
  sprintf(text,"gcc main.c -o main `sdl2-config --cflags --libs` -lSDL2_mixer -lm");
  chaste_font_draw_string_pixels_scaled_rainbow(text,main_font.char_width*8,main_font.char_height*8,2);
  sprintf(text,"./main");
  chaste_font_draw_string_pixels_scaled_rainbow(text,main_font.char_width*8,main_font.char_height*12,2);
  
  chaste_palette_index1++;
  if(chaste_palette_index1>=chaste_palette_length)
  {
   chaste_palette_index1=0;
  }
  
  sprintf(text,"Remember, everything is made of\nlittle squares called pixels!\nIncluding this text!");
  chaste_font_draw_string_scaled(text,main_font.char_width*8,main_font.char_height*40,4);
  
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}



void boxgame_level_8()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
  
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_5_rectangles();

 init_polygon();
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.cx=200;
 main_polygon.cy=500;
 main_polygon.radius=50;
 
/*  main_polygon.color=0xFF00;*/
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"Here is a pixel ->");
  chaste_font_draw_string_scaled(text,main_font.char_width*1,main_font.char_height*1,4);
  chaste_pixel(surface,600,20,0xFFFFFF);

  sprintf(text,"Here is a line ->");
  chaste_font_draw_string_scaled(text,main_font.char_width*1,main_font.char_height*16,4);
  chaste_line(surface,600,100,700,200,0xFFFFFF);
  
  sprintf(text,"Here is a triangle ->");
  chaste_font_draw_string_scaled(text,main_font.char_width*1,main_font.char_height*36,4);
  chaste_trigon_fill(surface,700,350,800,350,750,250,0xFFFFFF);


  main_polygon.cx=300;
  chaste_polygon_draw();
  
  main_polygon.cx=500;
  chaste_polygon_draw_filled();
  
  main_polygon.cx=700;
  chaste_polygon_draw_star();
  
  
    
  SDL_FillRect(surface,&player.rect,player.color);
  

  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}









void boxgame_level_9()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_5_rectangles();

 init_polygon();
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.cx=200;
 main_polygon.cy=500;
 main_polygon.radius=300;
 main_polygon.color=0xFFFFFF;
 
 main_polygon.cx=640;
 main_polygon.cy=360;

 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"This is a big star!");
  chaste_font_draw_string_scaled(text,main_font.char_width*20,main_font.char_height*1,4);
  
  chaste_polygon_draw_star();
  
  
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  /*fps_test();*/
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}






void boxgame_level_10()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 wall_color=SDL_MapRGB(surface->format,255,255,255); /*change color of walls for this level*/

 level_5_rectangles();

 init_polygon();
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.cx=200;
 main_polygon.cy=500;
 main_polygon.radius=300;
 main_polygon.color=0xFFFFFF;
 
 main_polygon.cx=640;
 main_polygon.cy=360;

 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0,0,0));
  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"This is a big circle!");
  chaste_font_draw_string_scaled(text,main_font.char_width*20,main_font.char_height*1,4);
    
  chaste_circle(surface,main_polygon.cx,main_polygon.cy,main_polygon.radius,main_polygon.color);
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  /*fps_test();*/
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}



/*
this level uses a software renderer
this allows it to use any renderer functions but targetting a surface.
This means that I can freely mix surface and renderer drawing functions in the same program!
*/
void boxgame_level_11()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 level_5_rectangles();

 init_polygon();
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.cx=200;
 main_polygon.cy=500;
 main_polygon.radius=300;
 main_polygon.color=0xFFFFFF;
 
 main_polygon.cx=640;
 main_polygon.cy=360;
 
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"This is a spinning star in a circle!");
  chaste_font_draw_string_scaled(text,main_font.char_width*8,main_font.char_height*1,4);
  
  chaste_polygon_draw_star_filled1();

  main_polygon.radians+=PI/180;
    
  chaste_circle(surface,main_polygon.cx,main_polygon.cy,main_polygon.radius,main_polygon.color);
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  /*fps_test();*/
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  
   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }

  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}



/*
this level uses a software renderer
this allows it to use any renderer functions but targetting a surface.
This means that I can freely mix surface and renderer drawing functions in the same program!
*/
void boxgame_level_12()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 level_5_rectangles();

 init_polygon();
 main_polygon.sides=5;
 main_polygon.step=2;
 main_polygon.cx=200;
 main_polygon.cy=500;
 main_polygon.radius=300;
 main_polygon.color=0xFFFFFF;
 
 main_polygon.cx=640;
 main_polygon.cy=360;
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);

  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"This is a pentagon in a circle!");
  chaste_font_draw_string_scaled(text,main_font.char_width*8,main_font.char_height*1,4);
  
  
  chaste_polygon_draw_filled1();

  main_polygon.radians+=PI/180;
    
  chaste_circle(surface,main_polygon.cx,main_polygon.cy,main_polygon.radius,main_polygon.color);
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  /*fps_test();*/
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}




/*
this level uses a software renderer
this allows it to use any renderer functions but targetting a surface.
This means that I can freely mix surface and renderer drawing functions in the same program!
*/
void boxgame_level_13()
{

 main_font=font_8;
 text_scale=16;
 text_x=2*main_font.char_width*text_scale;
 
 level_5_rectangles();

 init_circle();
 main_circle.radius=300;
 main_circle.slices_max=36;
 
 
 loop=1;
 while(loop) /*the beginning of the game loop*/
 {
  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;
  
  SDL_SetRenderDrawColor(renderer,128,128,128,255);
  SDL_RenderClear(renderer);

  
  /*chaste_checker();*/
 

  player_update();
  
  draw_blocks(); /*draw walls*/
  
  sprintf(text,"Yin and Yang");
  chaste_font_draw_string_scaled(text,main_font.char_width*8,main_font.char_height*1,4);
  
  
  yinyang();

  main_circle.radians+=PI/180;
    
  SDL_FillRect(surface,&player.rect,player.color);
  
  /*fps_test();*/
  
  SDL_UpdateWindowSurface(window); /*update the screen*/
  

   /*test for events and only process if they exist*/
 while(SDL_PollEvent(&e))
 {
  keyboard();
 }
  
  /*the ULTRA important timing loop. Without it the game is way too fast to see!*/
  while(sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
   /*sdl_time=sdl_time1;*/
  }
  
 }

}

