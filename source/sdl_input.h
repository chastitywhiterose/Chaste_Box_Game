/*sdl_input.h*/


/*this function is an SDL port of the keyboard function from the Raylib version of Chaste Tris*/
void keyboard()
{
 int key;
 if( e.type == SDL_QUIT ){loop=0; printf("X clicked! This program will close!\n");}
  
  
  /*check key down events*/
  if (e.type == SDL_KEYDOWN && e.key.repeat==0 )
  {
   key=e.key.keysym.sym;

   switch(key)
   {
    case SDLK_ESCAPE:
    loop=0;
    game_level=0;
    break;
    
    /*the main 4 directions*/

    case SDLK_DOWN:
    case SDLK_s:
     /*move_down();*/
    break;
    case SDLK_LEFT:
    case SDLK_a:
     player.xstep=-1;
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     player.xstep=1;
    break;
    
    case SDLK_UP:
    case SDLK_w:
    case SDLK_SPACE:
     if(player_jumps)
     {
      if(player.jump_time==0)
      {
       player.jump_time=player_max_jump;
      }
      player_jumps--;
     }
    break;
    
    /*music control*/
    case SDLK_m:
    if(Mix_Playing(0))
    {
     chaste_audio_stop(); /*stop the music playing if it currently is playing*/
    }
    else
    {
     chaste_audio_play(music[song_index]); /*start the music at the current song index*/
    }
    break;
    
    
   }
  }
  
  

  
  
  /*check key releases next*/
  
  
  
  if (e.type == SDL_KEYUP /*&& e.key.repeat==0*/ )
  {
   key=e.key.keysym.sym;

   switch(key)
   {
    case SDLK_LEFT:
    case SDLK_a:
     player.xstep=0;
    break;
    case SDLK_RIGHT:
    case SDLK_d:
     player.xstep=0;
    break;
    
   }
   
  }
  
  
  
  
  
}



/*
Important SDL references for keyboard handling.

https://wiki.libsdl.org/SDL2/CategoryKeyboard
*/




