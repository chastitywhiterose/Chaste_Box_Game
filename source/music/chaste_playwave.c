/*
  PLAYWAVE:  A test application for the SDL mixer library.
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/*
 This file has been modified from its original version. The above text is the original license text.
 All I did was removed the things from this version that I didn't need and add a few things.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_mixer.h>

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

static int audio_open = 0;
static Mix_Chunk *wave = NULL;

/* rcg06192001 abstract this out for testing purposes. */
static int still_playing(void)
{
 return(Mix_Playing(0));
}

static void CleanUp(int exitcode)
{
    if (wave) {
        Mix_FreeChunk(wave);
        wave = NULL;
    }
    if (audio_open) {
        Mix_CloseAudio();
        audio_open = 0;
    }
    SDL_Quit();

    exit(exitcode);
}


static void Usage(char *argv0)
{
    SDL_Log("Usage: %s [-8] [-f32] [-r rate] [-c channels] [-f] [-F] [-l] [-m] <wavefile>\n", argv0);
}

static void flip_sample(Mix_Chunk *wave)
{
    Uint16 format;
    int channels, i, incr;
    Uint8 *start = wave->abuf;
    Uint8 *end = wave->abuf + wave->alen;

    Mix_QuerySpec(NULL, &format, &channels);
    incr = (format & 0xFF) * channels;

    end -= incr;

    switch (incr) {
        case 8:
            for (i = wave->alen / 2; i >= 0; i -= 1) {
                Uint8 tmp = *start;
                *start = *end;
                *end = tmp;
                start++;
                end--;
            }
            break;

        case 16:
            for (i = wave->alen / 2; i >= 0; i -= 2) {
                Uint16 tmp = *start;
                *((Uint16 *) start) = *((Uint16 *) end);
                *((Uint16 *) end) = tmp;
                start += 2;
                end -= 2;
            }
            break;

        case 32:
            for (i = wave->alen / 2; i >= 0; i -= 4) {
                Uint32 tmp = *start;
                *((Uint32 *) start) = *((Uint32 *) end);
                *((Uint32 *) end) = tmp;
                start += 4;
                end -= 4;
            }
            break;

        default:
            SDL_Log("Unhandled format in sample flipping.\n");
            return;
    }
}


int main(int argc, char *argv[])
{
    int audio_rate;
    Uint16 audio_format;
    int audio_channels;
    int loops = 0;
    int i;
    int reverse_stereo = 0;
    int reverse_sample = 0;

    (void) argc;

    /* Initialize variables */
    audio_rate = MIX_DEFAULT_FREQUENCY;
    audio_format = MIX_DEFAULT_FORMAT;
    audio_channels = MIX_DEFAULT_CHANNELS;

    /* Check command line usage */
    for (i=1; argv[i] && (*argv[i] == '-'); ++i) {
        if ((strcmp(argv[i], "-r") == 0) && argv[i+1]) {
            ++i;
            audio_rate = atoi(argv[i]);
        } else
        if (strcmp(argv[i], "-m") == 0) {
            audio_channels = 1;
        } else
        if ((strcmp(argv[i], "-c") == 0) && argv[i+1]) {
            ++i;
            audio_channels = atoi(argv[i]);
        } else
        if (strcmp(argv[i], "-l") == 0) {
            loops = -1;
        } else
        if (strcmp(argv[i], "-8") == 0) {
            audio_format = AUDIO_U8;
        } else
        if (strcmp(argv[i], "-f32") == 0) {
            audio_format = AUDIO_F32;
        } else
        if (strcmp(argv[i], "-f") == 0) { /* rcg06122001 flip stereo */
            reverse_stereo = 1;
        } else
        if (strcmp(argv[i], "-F") == 0) { /* rcg06172001 flip sample */
            reverse_sample = 1;
        } else {
            Usage(argv[0]);
            return(1);
        }
    }
    if (! argv[i]) {
        Usage(argv[0]);
        return(1);
    }

    /* Initialize the SDL library */
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_Log("Couldn't initialize SDL: %s\n",SDL_GetError());
        return(255);
    }
    
#ifdef HAVE_SIGNAL_H
    signal(SIGINT, CleanUp);
    signal(SIGTERM, CleanUp);
#endif

    /* Open the audio device */
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0) {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        CleanUp(2);
    } else {
        Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
        SDL_Log("Opened audio at %d Hz %d bit%s %s", audio_rate,
            (audio_format&0xFF),
            (SDL_AUDIO_ISFLOAT(audio_format) ? " (float)" : ""),
            (audio_channels > 2) ? "surround" :
            (audio_channels > 1) ? "stereo" : "mono");
        if (loops) {
          SDL_Log(" (looping)\n");
        } else {
          putchar('\n');
        }
    }
    audio_open = 1;

    /* Load the requested wave file */
    wave = Mix_LoadWAV(argv[i]);
    if (wave == NULL) {
        SDL_Log("Couldn't load %s: %s\n",
                        argv[i], SDL_GetError());
        CleanUp(2);
    }

    if (reverse_sample) {
        flip_sample(wave);
    }

    if ((!Mix_SetReverseStereo(MIX_CHANNEL_POST, reverse_stereo)) &&
         (reverse_stereo))
    {
        SDL_Log("Failed to set up reverse stereo effect!\n");
        SDL_Log("Reason: [%s].\n", Mix_GetError());
    }

    /* Play and then exit */
    Mix_PlayChannel(0, wave, loops);

    while (still_playing())
    {
     /*optionally, stuff could be done while music was playing.*/
     /*Mix_HaltChannel(0);*/ /*this can stop the music!*/
    } /* while still_playing() loop... */

    CleanUp(0);

    /* Not reached, but fixes compiler warnings */
    return 0;
}

/*
 gcc chaste_playwave.c -o chaste_playwave `sdl2-config --cflags --libs` -lSDL2_mixer
 
 
 ./chaste_playwave "Sonic_the_Hedgehog_3_Ice_Cap_Zone_(Pulse_Mix)_OC_ReMix.mp3"
 
*/
