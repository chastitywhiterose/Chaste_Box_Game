/*sdl_chaste_pixel.h*/

/*
 the goal for this library is to be able to draw pixels one at a time and yet introduce a delay as the pixels are drawn to help
 create animations of things like lines being slowly drawn.
 
 Every graphics library has a pixel drawing function and in SDL is is done with direct pixel access on a locked surface!
*/


/*
 pixel array to keep track of which pixels I have drawn with my function
 It is char type because it uses only values of 0 or 1.
*/
/*char pixels[0x1000000];*/

void chaste_pixel(SDL_Surface *surface,int x,int y,int color)
{
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 dsp=(Uint32*)surface->pixels; /*set pointer to the pixels of this surface*/
 dsp[x+y*surface->w]=color;
}




/*
 The below function is my own version of this algorithm:
 https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
*/
void chaste_line(SDL_Surface *surface,int x0,int y0,int x1,int y1,int color)
{
 int dx,dy,sx,sy,err,e2;
 dx= x1-x0; if(dx<0){dx=-dx;}
 dy= y1-y0; if(dy<0){dy=-dy;}
 if(x0<x1){sx=1;}else{sx=-1;}
 if(y0<y1){sy=1;}else{sy=-1;}
 if(dx>dy){err=dx;}else{err=-dy;}err>>=1;;
 while(1)
 {
  chaste_pixel(surface,x0,y0,color); /*this is when the pixel is drawn*/
  if (x0==x1 && y0==y1) break;
  e2=err;
  if (e2 >-dx) { err -= dy; x0 += sx; }
  if (e2 < dy) { err += dx; y0 += sy; }
 }
}




/*
 function to arbitrarily draw any triangle, not just the regular ones
*/
void chaste_trigon(SDL_Surface *surface,int x0,int y0,int x1,int y1,int x2,int y2,int color)
{
 chaste_line(surface,x0,y0,x1,y1,color);
 chaste_line(surface,x1,y1,x2,y2,color);
 chaste_line(surface,x2,y2,x0,y0,color);
}



/*
 function to draw any triangle, but also draw corner to midpoint of lines
*/
void chaste_trigon_mid(SDL_Surface *surface,int x0,int y0,int x1,int y1,int x2,int y2,int color)
{
 int mx,my;
 

 chaste_line(surface,x0,y0,x1,y1,color); /*line 0*/
 
 mx=(x0+x1)/2;
 my=(y0+y1)/2;
 chaste_line(surface,mx,my,x2,y2,color); /*midpoint of line 0 to point 2*/
 
 
 chaste_line(surface,x1,y1,x2,y2,color); /*line 1*/
 
 mx=(x1+x2)/2;
 my=(y1+y2)/2;
 chaste_line(surface,mx,my,x0,y0,color); /*midpoint of line 1 to point 0*/
 
 chaste_line(surface,x2,y2,x0,y0,color); /*line 2*/
 
 mx=(x2+x0)/2;
 my=(y2+y0)/2;
 chaste_line(surface,mx,my,x1,y1,color); /*midpoint of line 2 to point 1*/
 
}















/*
 The flood fill algorithm is complex. I got the basic layout from here:
 https://rosettacode.org/wiki/Bitmap/Flood_fill#C
*/

/*
my flood fill algorithm for this project does not take a color argument because it is using assumed values of 0 and 1 just like my scan_fill function earlier in this file.
*/

int oldColor=0,newColor=0xFFFFFF;

void chaste_flood_fill(SDL_Surface *surface,int x,int y)
{
 Uint32 *dsp;
 dsp=(Uint32*)surface->pixels;
 if ( 0 <= x && x < width &&   0 <= y && y < height 
 &&   dsp[x+y*surface->w] == oldColor )
 {
  dsp[x+y*surface->w]=newColor;

  chaste_flood_fill(surface,x-1,y); 
  chaste_flood_fill(surface,x+1,y);
  chaste_flood_fill(surface,x,y-1); 
  chaste_flood_fill(surface,x,y+1);
 }
}




/*find approximate center of a triangle and then fill from that spot*/
void chaste_trigon_fill(SDL_Surface *surface,int x0,int y0,int x1,int y1,int x2,int y2,int color)
{
 int mx,my,mx1,my1;
 

 chaste_line(surface,x0,y0,x1,y1,color); /*line 0*/
 chaste_line(surface,x1,y1,x2,y2,color); /*line 1*/
 chaste_line(surface,x2,y2,x0,y0,color); /*line 2*/
 
 mx=(x0+x1)/2;
 my=(y0+y1)/2;
 mx1=(mx+x2)/2;
 my1=(my+y2)/2;
 
 newColor=color; /*set global newcolor instead of passing it as an argument to the flood fill function*/
 chaste_flood_fill(surface,mx1,my1);
}








/*
scan fill an area. Works for only certain shapes including triangles
It finds nonzero pixels and then assumes they are the edge

*/
void chaste_scan_fill(SDL_Surface *surface,int color)
{
 int x,y,x1;
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 dsp=(Uint32*)surface->pixels; /*set pointer to the pixels of this surface*/
 
 y=0;
 while(y<height)
 {
  x=0;
  while(x<width)
  {
   /*pixels[x+y*width]=0;*/
   if(dsp[x+y*surface->w]!=0) /*find left edge*/
   {
    /*printf("found left edge at x=%d,y=%d\n",x,y);*/
    
     x1=width;
     while(x1>0)
     {
      x1-=1;
      if(dsp[x1+y*surface->w]!=0){break;} /*find right edge*/
     }
     
     while(x<x1) /*fill space between the two on this line*/
     {
      dsp[x+y*surface->w]=color;
      x+=1;
     }
    
   }
   
   x+=1;
  }
 
  y+=1;
 }
 
}



