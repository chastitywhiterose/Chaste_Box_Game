/*sdl_input.h*/


/*this function is an SDL port of the keyboard function from the Raylib version of Chaste Tris*/
void keyboard()
{
 int key;
 SDL_PollEvent( &e );
  if( e.type == SDL_QUIT ){loop=0; printf("X clicked! This program will close!\n");}
  
  
  /*check key down events*/
  if (e.type == SDL_KEYDOWN && e.key.repeat==0 )
  {
   key=e.key.keysym.sym;

   switch(key)
   {
    case SDLK_ESCAPE:
    loop=0;
    break;
    
    /*the main 4 directions*/
    case SDLK_UP:
    case SDLK_w:
     /*move_up();*/
    break;
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
    
    case SDLK_SPACE:
     if(player_can_jump)
     {
      if(player.jump_time==0)
      {
       player.jump_time=player_max_jump;
      }
      player_can_jump=0;
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




