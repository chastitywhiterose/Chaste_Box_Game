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
char pixels[0x1000000];

void chaste_pixel(SDL_Surface *surface,int x,int y,int color)
{
 Uint32 *dsp; /*dsp is short for Destination Surface Pointer*/
 dsp=(Uint32*)surface->pixels; /*set pointer to the pixels of this surface*/
 dsp[x+y*width]=color;
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


