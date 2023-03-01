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

