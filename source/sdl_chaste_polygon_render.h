/*sdl_chaste_polygon_render.h*/

/*
this file is meant to work with an SDL_Renderer. However it depends on the functions in sdl_chaste_pixel_polygon for obtaining the points of the regular polygons.
This method of drawing is more complex but my tests reveal that it is much faster when running programs compared to the pixel methods I previously wrote.
*/

/*
These two functions are the same exact names as the functions in the pixel based polygon header.
The only difference is the 1 on the end which allows me to switch between the functions for speed tests

chaste_polygon_draw_filled1
chaste_polygon_draw_star_filled1
*/


/*SDL_Color main_polygon_rendercolor;*/


/* large array for any possible combination of vertices to make many triangles*/
SDL_Vertex vertices[0x1000];


SDL_Color temp_color;

/*this first function draws a series of triangles to make a convex regular polygon*/
void chaste_polygon_draw_filled1()
{
 int i,i1;
 chaste_polygon_points();
 
 /*
  convert integer color of polygon into an SDL_Color that is used for colors
  that are used inside an SDL_Vertex
 */
 SDL_GetRGB(main_polygon.color,main_font.surface->format,&temp_color.r,&temp_color.g,&temp_color.b);
 
 vertices[0].color=temp_color;
 vertices[1].color=temp_color;
 vertices[2].color=temp_color;
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+1)%main_polygon.sides;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=polygon_xpoints[i];
  vertices[0].position.y=polygon_ypoints[i];
  vertices[1].position.x=polygon_xpoints[i1];
  vertices[1].position.y=polygon_ypoints[i1];
  vertices[2].position.x=main_polygon.cx;
  vertices[2].position.y=main_polygon.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);
  
  i++;
 }
 
}







/*
 this first function draws a series of triangles to make any kind of regular polygon
 this includes star polygons by taking into account the step value between points.
*/
void chaste_polygon_draw_star_filled1()
{
 int i,i1;
 chaste_polygon_points();

 /*
  convert integer color of polygon into an SDL_Color that is used for colors
  that are used inside an SDL_Vertex
 */
 SDL_GetRGB(main_polygon.color,main_font.surface->format,&temp_color.r,&temp_color.g,&temp_color.b);
 
 vertices[0].color=temp_color;
 vertices[1].color=temp_color;
 vertices[2].color=temp_color;
 
 i=0;
 while(i<main_polygon.sides)
 {
  i1=(i+main_polygon.step)%main_polygon.sides;
  
  /*for each part of this loop,construct a triangle*/
  vertices[0].position.x=polygon_xpoints[i];
  vertices[0].position.y=polygon_ypoints[i];
  vertices[1].position.x=polygon_xpoints[i1];
  vertices[1].position.y=polygon_ypoints[i1];
  vertices[2].position.x=main_polygon.cx;
  vertices[2].position.y=main_polygon.cy;
  
  SDL_RenderGeometry(renderer,NULL,vertices,3,NULL,0);

  /*swap colors around to show off*/  
  temp_color=vertices[0].color;
  vertices[0].color=vertices[1].color;
  vertices[1].color=vertices[2].color;
  vertices[2].color=temp_color;
  i++;
 }
 
}


