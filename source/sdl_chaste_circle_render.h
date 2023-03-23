/*
sdl_chaste_circle_render.h

This file is all about circles. The idea is to have quick functions that use
SDL_RenderGeometry but without using the polygon structure in the other headers.
Instead, I wrote a new structure that describes the circle as slices of a pie.

The code is really the same algorithm as used for the regular polygon but serves the purpose of keeping the two files independent from each other and reducing bugs.
*/


struct circle
{
 double cx,cy;
 int slices_use;
 int slices_max;
 double radius;
 double radians;
 int color;
};

struct circle main_circle,temp_circle;

/*initial values for a circle to be modified by the program in other places*/
void init_circle()
{
 main_circle.cx=width/2;
 main_circle.cy=height/2;
 main_circle.slices_use=6;
 main_circle.slices_max=12;
 main_circle.radius=height/2;
 main_circle.radians=0;
 main_circle.color=0xFFFFFF;
}

int circle_xpoints[0x1000],circle_ypoints[0x1000];

/*
function to get the points of a regular polygon and load them into the above arrays of x and y points
*/
void chaste_circle_points()
{
 double angle,x,y;
 int i=0;
 while(i<main_circle.slices_max)
 {
  angle=2*PI*i/main_circle.slices_max+main_circle.radians;
  x=main_circle.cx+sin(angle)*main_circle.radius;
  y=main_circle.cy-cos(angle)*main_circle.radius;
  circle_xpoints[i]=chaste_round(x);
  circle_ypoints[i]=chaste_round(y);
  i++;
 }
}




/*this first function draws a series of triangles to make a convex regular polygon*/
void chaste_circle_draw_filled1()
{
 int i,i1;
 chaste_circle_points();
 
 /*
  convert integer color of polygon into an SDL_Color that is used for colors
  that are used inside an SDL_Vertex
 */
 SDL_GetRGB(main_circle.color,main_font.surface->format,&temp_color.r,&temp_color.g,&temp_color.b);
 
 i=0;
 while(i<3)
 {
  vertices[i].color=temp_color;
  i++;
 }
 
 i=0;
 while(i<main_circle.slices_max)
 {
  i1=(i+1)%main_circle.slices_max;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=circle_xpoints[i];
  vertices[0].position.y=circle_ypoints[i];
  vertices[1].position.x=circle_xpoints[i1];
  vertices[1].position.y=circle_ypoints[i1];
  vertices[2].position.x=main_circle.cx;
  vertices[2].position.y=main_circle.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
  
  i++;
 }
}




/*
this first function draws a series of triangles to make an approximation of a circle
except this only draws up to "main_circle.slices_use".
*/
void chaste_circle_draw_parts_filled1()
{
 int i,i1;
 chaste_circle_points();
 
 /*
  convert integer color of polygon into an SDL_Color that is used for colors
  that are used inside an SDL_Vertex
 */
 SDL_GetRGB(main_circle.color,main_font.surface->format,&temp_color.r,&temp_color.g,&temp_color.b);
 
 i=0;
 while(i<3)
 {
  vertices[i].color=temp_color;
  i++;
 }
 
 i=0;
 while(i<main_circle.slices_use)
 {
  i1=(i+1)%main_circle.slices_max;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=circle_xpoints[i];
  vertices[0].position.y=circle_ypoints[i];
  vertices[1].position.x=circle_xpoints[i1];
  vertices[1].position.y=circle_ypoints[i1];
  vertices[2].position.x=main_circle.cx;
  vertices[2].position.y=main_circle.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
  
  i++;
 }
}





void yinyang()
{
 double radius,radians,cx,cy,cx1,cy1,cx2,cy2,angle,cr1,cr2;

/*backup important attributes to be restored later*/
 radians=main_circle.radians;
 radius=main_circle.radius;
 cx=main_circle.cx;
 cy=main_circle.cy;
 
 /*draw two halves of circle*/
 main_circle.color=0xFFFFFF;
 chaste_circle_draw_parts_filled1();
 main_circle.radians+=PI;

 main_circle.color=0x000000;
 chaste_circle_draw_parts_filled1();
 main_circle.radians=radians;
 
 /*next get points for smaller circles*/
 angle=2.0*PI+main_circle.radians;
 
 cr1=radius/2;
 cr2=cr1/4;
 
 cx1=cx+sin(angle)*cr1;
 cy1=cy-cos(angle)*cr1;
 
 main_circle.cx=cx1;
 main_circle.cy=cy1;
 main_circle.radius=cr1;
 chaste_circle_draw_filled1();
 
 main_circle.radius=cr2;
 main_circle.color=0xFFFFFF;
 chaste_circle_draw_filled1();

 
 cx1=cx-sin(angle)*cr1;
 cy1=cy+cos(angle)*cr1;
 main_circle.cx=cx1;
 main_circle.cy=cy1;
 main_circle.radius=cr1;
 main_circle.color=0xFFFFFF;
 chaste_circle_draw_filled1();

 main_circle.radius=cr2;
 main_circle.color=0x000000;
 chaste_circle_draw_filled1();


 
 /*restore values to what they were at the start*/
 main_circle.cx=cx;
 main_circle.cy=cy;
 main_circle.radius=radius;

}
