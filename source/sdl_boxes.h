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
 Uint8 r,g,b; /*red green and blue for mapping colors*/
 Uint32 pixel; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 SDL_LockSurface(main_font.surface);
 SDL_LockSurface(surface);
 
 ssp=(Uint32*)main_font.surface->pixels;
 dsp=(Uint32*)surface->pixels;

 
 /*x=100;y=500;
 dsp[x+y*width]=0xFFFFFF;*/ /*test drawing a single white pixel*/
  
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
     pixel=ssp[sx+sy*source_surface_width];
     /*printf("0x%06X\n",ssp[sx+sy*width]);*/

     if(pixel!=0)
     {
      /*get the correct pixel color*/
      SDL_GetRGB(pixel,main_font.surface->format,&r,&g,&b);
      dsp[dx+dy*width]=SDL_MapRGB(surface->format,r,g,b);
      /*dsp[dx+dy*width]=pixel;*/
      /*dsp[dx+dy*width]=0xFFFFFF;*/
     }
     
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











/*
 The scaled version of my font drawing function that uses direct pixel access
 For the sake of efficiency, it does not check to see if the source(main_font.surface) and destination(screen)
 are of the same type. My font library has been updated to make sure they are when loading the font from the file.
 This makes SDL_GetRGB and SDL_MapRGB useless and they have been removed to speed up things by removing function calls.
*/

void chaste_font_draw_string_pixels_scaled(char *s,int cx,int cy,int scale,int color)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 SDL_LockSurface(main_font.surface);
 SDL_LockSurface(surface);
 
 ssp=(Uint32*)main_font.surface->pixels;
 dsp=(Uint32*)surface->pixels;
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   /*set up destination rectangle where this character will be drawn to*/
   rect_dest.x=cx;
   rect_dest.y=cy;
   
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   
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
     pixel=ssp[sx+sy*source_surface_width];
 
     if(pixel!=0)
     {
      int tx,ty,tx2,ty2; /*temp variables only for the rectangle*/
      
      /*don't just draw one pixel but rather an entire rectangle*/
      
      ty2=dy+scale;
      
      /*beginning of rectangle*/      
      ty=dy;
      while(ty<ty2)
      {
       tx=dx;
       tx2=dx+scale;
       while(tx<tx2)
       {
        dsp[tx+ty*width]=color;
        tx++;
       }
       ty++;
      }
      /*end of rectangle*/
      
      
     }
     
     
     sx++;
     dx+=scale;
     
    }
    
    sy++;
    dy+=scale;
    

   }


   /*End of really complicated section*/

   cx+=main_font.char_width*scale;
  }
  i++;
 }

 SDL_UnlockSurface(main_font.surface);
 SDL_UnlockSurface(surface);
 
}














/*
this is a copy of my scaled pixel access function that instead of taking a color as an argument uses the global palette
This is because I want rainbow text in my game.
*/

void chaste_font_draw_string_pixels_scaled_rainbow(char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel; /*pixel that will be read from*/
 int source_surface_width;
 SDL_Rect rect_source,rect_dest;

 source_surface_width=main_font.surface->w;

 SDL_LockSurface(main_font.surface);
 SDL_LockSurface(surface);
 
 ssp=(Uint32*)main_font.surface->pixels;
 dsp=(Uint32*)surface->pixels;
  
 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=main_font.char_height*scale;}
  else
  {
   x=(c-' ')*main_font.char_width;
   y=0*main_font.char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=main_font.char_width;
   rect_source.h=main_font.char_height;

   /*set up destination rectangle where this character will be drawn to*/
   rect_dest.x=cx;
   rect_dest.y=cy;
   
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   
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
     pixel=ssp[sx+sy*source_surface_width];
 
     if(pixel!=0)
     {
      int tx,ty,tx2,ty2; /*temp variables only for the rectangle*/
      
      /*don't just draw one pixel but rather an entire rectangle*/
      
      ty2=dy+scale;
      
      /*beginning of rectangle*/      
      ty=dy;
      while(ty<ty2)
      {
      
       tx=dx;
       tx2=dx+scale;
       while(tx<tx2)
       {
        /*dsp[tx+ty*width]=color;*/
        dsp[tx+ty*width]=chaste_palette[chaste_palette_index];
        tx++;
       }
       chaste_next_color();
      
       ty++;
      }
      /*end of rectangle*/
      
      
     }
     
     
     sx++;
     dx+=scale;
     
    }
    
    sy++;
    dy+=scale;
    

   }


   /*End of really complicated section*/

   cx+=main_font.char_width*scale;
  }
  i++;
 }

 SDL_UnlockSurface(main_font.surface);
 SDL_UnlockSurface(surface);
 
}

