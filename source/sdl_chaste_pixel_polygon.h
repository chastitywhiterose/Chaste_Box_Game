/*sdl_chaste_pixel_polygon.h*/

/*
this file uses my customized pixel drawing routines and draws to surfaces instead of rendererers.
This means it does not use SDL_RenderGeometry or any of the newer features of SDL. It is not the same file as
sdl_chaste_polygon.h from the SDL_Chaste_Triangle project.

For more info on that project go here.
https://github.com/chastitywhiterose/SDL_Chaste_Triangle

That being said, some of the code is the same because the code used to obtain the points of the polygon is identical.
*/

struct polygon
{
 double cx,cy;
 int sides;
 double radius;
 double radians;
 int color;
 int step; /*used only in star polygons of 5 or more sides*/
};

struct polygon main_polygon,temp_polygon;

void init_polygon()
{
 main_polygon.cx=width/2;
 main_polygon.cy=height/2;
 main_polygon.sides=3;
 main_polygon.radius=height/2;
 main_polygon.radians=0;
 main_polygon.color=0xFFFFFF;
 main_polygon.step=2;
}

/*
 this function created because the standard round function did not exist in C until 1999 standard.
 I only use 1989 standard. It is sometimes helpful to round to neared integer when the data type requires it.
 Original source here: https://en.cppreference.com/w/c/numeric/math/round
*/
double chaste_round(double x)
{
 return x<0 ? ceil(x - 0.5) : floor(x + 0.5);
}

/*Define PI the same as M_PI in math.h*/
 #define PI 3.14159265358979323846f


/*these point arrays are temporary and not included in the polygon structure*/
int polygon_xpoints[0x1000],polygon_ypoints[0x1000];

/*
function to get the points of a regular polygon and load them into the above arrays of x and y points
*/
void chaste_polygon_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_polygon.sides)
 {
  angle=2*PI*i/main_polygon.sides+main_polygon.radians;
  x=main_polygon.cx+sin(angle)*main_polygon.radius;
  y=main_polygon.cy-cos(angle)*main_polygon.radius;
  polygon_xpoints[i]=chaste_round(x);
  polygon_ypoints[i]=chaste_round(y);
  i++;
 }
}

/*draw regular polygon ignoring the step variable*/
void chaste_polygon_draw()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  chaste_line(surface,polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  i++;
 }
}




/*draw regular polygon ignoring the step variable. Fill afterwards with flood fill.*/
void chaste_polygon_draw_filled()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  chaste_line(surface,polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  i++;
 }
 
 newColor=main_polygon.color; /*set global newcolor instead of passing it as an argument to the flood fill function*/
 chaste_flood_fill(surface,main_polygon.cx,main_polygon.cy);
 
}


/*draw star polygon by making use of step variable*/
void chaste_polygon_draw_star()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  chaste_line(surface,polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  i++;
 }
}






/*
 This function needs fixing.
 It is meant to draw a series of triangles and then fill them to form a perfectly filled regular polygon.
 However this means that a temporary surface would need to be drawn on and then blitted to the destination.
 It would be very slow even if I did finish it. But maybe I will figure it out somehow someday.
 
 EDIT: it works but it is really slow!
*/
void chaste_polygon_draw_star_filled_slow()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  
  SDL_FillRect(surface_temp,NULL,0x000000);/*erase temp surface*/
  
  /*draw a filled triangle to the temporary surface*/
   chaste_trigon_fill(surface_temp,
   polygon_xpoints[i],polygon_ypoints[i],
   polygon_xpoints[i1],polygon_ypoints[i1],
   main_polygon.cx,main_polygon.cy,
   main_polygon.color);
   
   /*blit temp surface to screen*/
   SDL_BlitSurface(surface_temp,NULL,surface,NULL);
 
  i++;
 }
 
 
}





/*
An attempt to fill a star polygon faster
*/
void chaste_polygon_draw_star_filled_fast()
{
 int i,i1;
 chaste_polygon_points();
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  chaste_line(surface,polygon_xpoints[i],polygon_ypoints[i],polygon_xpoints[i1],polygon_ypoints[i1], main_polygon.color);
  
  if(main_polygon.step>1)
  {
   int mx,my; /*midpoint variables*/
   mx=(polygon_xpoints[i]+polygon_xpoints[i1])/2;
   my=(polygon_ypoints[i]+polygon_ypoints[i1])/2;
   
   chaste_pixel(surface,mx,my,0xFF);
   
  }
  

  
  i++;
 }
 
  newColor=main_polygon.color; /*set global newcolor instead of passing it as an argument to the flood fill function*/
  chaste_flood_fill(surface,main_polygon.cx,main_polygon.cy);
}




/*
Draw regular star polygon at regular size. Then draw smaller but opposite color.
Then there are proper holes to flood fill the whole shape.
This is the fastest I have achieve with just regular surfaces.
*/
void chaste_polygon_draw_star_filled()
{
 chaste_polygon_draw_star();
 temp_polygon=main_polygon;
 main_polygon.color^=0xFFFFFF;
 main_polygon.radius/=2;
 chaste_polygon_draw_star(); 
 main_polygon=temp_polygon;
 
 newColor=main_polygon.color;
 chaste_flood_fill(surface,main_polygon.cx,main_polygon.cy);
}

