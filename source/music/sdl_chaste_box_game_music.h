/*
I don't know what I am doing with this file!
*/

#include <SDL_mixer.h>

int audio_open = 0;
Mix_Chunk *wave = NULL;

 int audio_rate;
    Uint16 audio_format;
    int audio_channels;
    int loops = 0;
    int i;
    int reverse_stereo = 0;
    int reverse_sample = 0;



/*
this function is meant to return 0 if everything is fine. Nonzero if any error happens.
*/
int audio_init()
{
 /* Initialize variables */
 audio_rate = MIX_DEFAULT_FREQUENCY;
 audio_format = MIX_DEFAULT_FORMAT;
 audio_channels = MIX_DEFAULT_CHANNELS;

 /*loops = -1;*/ /*for infinite loop*/
 
     /* Initialize the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
     SDL_Log("Couldn't initialize SDL: %s\n",SDL_GetError());
     return(255);
    }
 
 return 0;
}








/*
 gcc main.c -o main `sdl2-config --cflags --libs` -lSDL2_mixer
 
 
 ./chaste_playwave "Sonic_the_Hedgehog_3_Ice_Cap_Zone_(Pulse_Mix)_OC_ReMix.mp3"
 
*/
