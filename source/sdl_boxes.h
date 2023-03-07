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




/*
 this next function is kinda complicated
 It is an application of my font library but using direct pixel access instead of using SDL blitting functions.
 The purpose is for my learning only because it is not as fast as the official SDL way.
*/

void chaste_font_draw_string_pixels(char *s,int cx,int cy)
{
 int x,y,i,c,cx_start=cx;
 Uint32 *sp; /*sp is short for Surface Pointer in this example*/
 
 SDL_Rect rect_source,rect_dest;
 
 SDL_LockSurface(surface);
 
 sp=(Uint32*)surface->pixels;
 
 x=100;y=500;
 sp[x+y*width]=0xFFFFFF; /*test drawing a single white pixel*/
  
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

   SDL_BlitSurface(main_font.surface,&rect_source,surface,&rect_dest);
   cx+=main_font.char_width;
  }
  i++;
 }
 
 SDL_UnlockSurface(surface);
 
}

