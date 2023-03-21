#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>

/*
most variables in the program are global. Unless I create temporary variables in other functions.
*/
int width=1280,height=720;
int loop=1;
SDL_Window *window = NULL;
SDL_Surface *surface;
SDL_Surface *surface_temp; /*possible temporary surface that may be used*/
SDL_Renderer *renderer;
SDL_Event e;
SDL_Rect rect;

int game_level=0;

/*timing variables*/
int frame=0,lastframe=0,fps=60,delay,framelimit=1; /*only used for animation demos*/
int seconds;
time_t std_time_start,std_time_now; /*for standard library time functions*/

Uint32 sdl_time,sdl_time1; /*for sdl time functions*/


char text[0x200];
char movetext[256],move_id;
int text_x; /*the x position of where text will go*/
int text_scale; /*the current scale of the text used in some functions*/

/*music variables section*/
int songs=3,song_index=0,music_is_on=0;
char *music_files[]=
{
 "music/Castlevania_Harmony_of_Dissonance_Swingin'_with_Death_OC_ReMix.mp3",
 "music/Pokemon_Silver_Version_Lucky_Coin_OC_ReMix.mp3",
 "music/Sonic_the_Hedgehog_3_Ice_Cap_Zone_(Pulse_Mix)_OC_ReMix.mp3"
};

Mix_Chunk *music[3]; /*chunks the music is loaded into*/


#include "sdl_chastefont.h"
#include "sdl_chaste_box_game_music.h"
#include "chaste_the_rainbow.h"
#include "sdl_chaste_pixel.h"
#include "sdl_chaste_pixel_polygon.h"
#include "sdl_chaste_polygon_render.h"
#include "sdl_boxes.h"
#include "sdl_boxgame_player.h"
#include "sdl_input.h"
#include "sdl_boxgame.h"



int main(int argc, char* args[])
{
 int i=0;

 chaste_audio_init(); /*get the audio device ready*/
 
 /*load all songs*/
 i=0;
 while(i<songs)
 {
/*  music[i]=chaste_audio_load(music_files[i]);*/
  i++;
 }


 if(SDL_Init(SDL_INIT_VIDEO)){printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;}
 window=SDL_CreateWindow( "SDL Chaste Box Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 /*set up the screen*/
 surface = SDL_GetWindowSurface(window);
 
 /*create temporary surface that may be used for polygons at some point*/
 /*surface_temp=SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);*/
 surface_temp=SDL_ConvertSurface(surface, surface->format, 0);
 SDL_SetColorKey(surface_temp,SDL_TRUE,0x000000); /*black will be used as transparent in blits*/
 SDL_FillRect(surface_temp,NULL,0x000000);/*erase temp surface*/

 SDL_FillRect(surface,NULL,SDL_MapRGB(surface->format,0x80,0x80,0x80));
 SDL_UpdateWindowSurface(window);

 /*this game will only load two fonts*/
 font_pico8=chaste_font_load("./font/PICO-8_4x6.bmp");
 font_8=chaste_font_load("./font/FreeBASIC Font 8.bmp");

 checker_init(); /*set up initial checkerboard values*/
 player.size=rectsize; /*set same player size as checker grid*/
 
 wall_color=SDL_MapRGB(surface->format,255,255,255);
 
 fps=360; /*change the speed AKA Frames Per Second */
 delay=1000/fps;
 delay=0;
 
 /*load the rainbow colors!*/
 chaste_palette_rainbow(255);
 /*chaste_palette_make(12);*/
 /*chaste_palette_view();*/

 game_level=0;
 if(game_level==0){boxgame_title();}
 
 player_init(); /*must init player before starting levels*/

 /*audio_play(music_files[song_index]);*/ /*start playing music just before the game starts*/
 song_index=0;
 chaste_audio_play(music[song_index]);

 game_level=11; /*level to start on. this makes for easier testing of my levels*/
 
 /*get time before the game starts using standard library time function*/
 time(&std_time_start);

 while(game_level!=0)
 {
  if(game_level==1){boxgame_level_1();}
  else if(game_level==2){boxgame_level_2();}
  else if(game_level==3){boxgame_level_3();}
  else if(game_level==4){boxgame_level_4();}
  else if(game_level==5){boxgame_level_5();}
  else if(game_level==6){boxgame_level_6();}
  else if(game_level==7){boxgame_level_7();}
  else if(game_level==8){boxgame_level_8();}
  else if(game_level==9){boxgame_level_9();}
  else if(game_level==10){boxgame_level_10();}
  else if(game_level==11){boxgame_level_11();}
  else {break;}
  
  if(!Mix_Playing(0)) /*if music is no longer playing*/
  {
   song_index=(song_index+1)%songs; /*go to next song*/
   chaste_audio_play(music[song_index]); /*start the music at the current song index*/
  }

 }

 SDL_FreeSurface(font_pico8.surface);
 SDL_FreeSurface(font_8.surface);

 SDL_DestroyWindow(window);
 
 
 /*unload and free the music*/
 i=0;
 while(i<songs)
 {
  if(music[i]!=NULL)
  {
   Mix_FreeChunk(music[i]);
   music[i]=NULL;
  }
  i++;
 }
 
  if (audio_open)
  {
   Mix_CloseAudio();
   audio_open = 0;
  }
  /*end of music closing section*/
 
 SDL_Quit();

 return 0;
}















/*
Compile within Unix/Linux/msys
gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --libs` && ./main

Static Compile within Unix/Linux/msys
gcc -Wall -ansi -pedantic main.c -o main `sdl2-config --cflags --static-libs` && ./main

Compiling on Windows:

can dynamic link with my msys install
set PATH=C:\msys64\mingw32\bin;
gcc -Wall -ansi -pedantic main.c -o main -IC:\msys64\mingw32\include\SDL2 -Dmain=SDL_main -LC:\msys64\mingw32\lib -lmingw32 -lSDL2main -lSDL2 && main

More frequently, I compile with my official Windows install in C:\SDL
set PATH=C:\TDM-GCC-32\bin;C:\SDL\bin;
gcc -Wall -ansi -pedantic main.c -o main -IC:\SDL\include\SDL2 -Dmain=SDL_main -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 && main

can static compile too. (only works with my install in C:\SDL)
gcc -Wall -ansi -pedantic main.c -o main -IC:\SDL\include\SDL2 -Dmain=SDL_main -LC:\SDL\lib -lmingw32 -lSDL2main -lSDL2 -mwindows  -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc -static && main
*/
