/*sdl_boxes.h*/

int wall_color; /*default color of walls. Will be set in main function before game begins.*/

int blocks_count=0; /*how many blocks there currently are*/
SDL_Rect blocks[0x1000]; /*array of blocks which can be walls or other obstacles*/

void add_block(int x,int y,int w,int h)
{
 blocks[blocks_count].x=x;
 blocks[blocks_count].y=y;
 blocks[blocks_count].w=w;
 blocks[blocks_count].h=h;
 blocks_count++;
}



/*draws all the blocks/walls*/
void draw_blocks()
{
 int i=0;
 while(i<blocks_count)
 {
  SDL_FillRect(surface,&blocks[i],wall_color);
  i++;
 }
 
}


/*this function tells me the formats of the current main font and the screen surface*/
void check_surface_formats()
{
 printf("Source Surface Format: BitsPerPixel %d\n",main_font.surface->format->BitsPerPixel);
 printf("Source Surface Format: BytesPerPixel %d\n",main_font.surface->format->BytesPerPixel);
 
 printf("Dest Surface Format: BitsPerPixel %d\n",surface->format->BitsPerPixel);
 printf("Dest Surface Format: BytesPerPixel %d\n",surface->format->BytesPerPixel);

}


/*
 this next function is kinda complicated
 It is an application of my font library but using direct pixel access instead of using SDL blitting functions.
 The purpose is for my learning only because it is not as fast as the official SDL way.
 I may need this direct pixel access for a feature in my game.
 
 Helpful reference for surfaces here:
 https://wiki.libsdl.org/SDL2/SDL_PixelFormat
*/

void chaste_font_draw_string_pixels(char *s,int cx,int cy)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*I'll explain this later*/
 
 SDL_Rect rect_source,rect_dest;



 SDL_LockSurface(main_font.surface);
 SDL_LockSurface(surface);
 
 ssp=(Uint32*)main_font.surface->pixels;
 dsp=(Uint32*)surface->pixels;

 
 x=100;y=500;
 dsp[x+y*width]=0xFFFFFF; /*test drawing a single white pixel*/
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   rect_dest=rect_source;
   rect_dest.x=cx;
   rect_dest.y=cy;
   
   /*now for the complicated stuff!*/
   
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=rect_dest.x;
   dy=rect_dest.y;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=rect_dest.x;
    sx=rect_source.x;
    while(sx<sx2)
    {
     /*dsp[dx+dy*width]=ssp[sx+sy*width];*/
   dsp[dx+dy*width]=0xFFFFFF;
     sx++;
     dx++;
    }
    sy++;
    dy++;
   }

 /*end of really complicated section*/

   cx+=main_font.char_width;
  }
  i++;
 }

 SDL_UnlockSurface(main_font.surface);
 SDL_UnlockSurface(surface);
 
}

