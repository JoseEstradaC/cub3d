/*#include <cmath>*/
/*#include <string>*/
/*#include <vector>*/
/*#include <iostream>*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MLX42/MLX42.h"
/*#include "quickcg.h"*/

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

typedef struct s_vars
{
	mlx_t	*mlx;
	mlx_image_t	*img;
	double	*posX;
	double	*posY;
	double	*dirX;
	double	*dirY;
	double	*planeX;
	double	*planeY;
}	t_vars;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	render(void *param)
{
	t_vars *vars = param;
	double posX = *vars->posX;
	double posY = *vars->posY;
	double dirX = *vars->dirX;
	double dirY = *vars->dirY;
	double planeX = *vars->planeX;
	double planeY = *vars->planeY;

    /*memset(vars->img->pixels, 0, vars->img->width * vars->img->height * sizeof(uint8_t));*/
	for (int x = 0; x < screenWidth; x++)
		for (int y = 0; y < screenHeight; y++)
			mlx_put_pixel(vars->img, x, y, 0);

    for(int x = 0; x < screenWidth; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }

      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(screenHeight / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + screenHeight / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + screenHeight / 2;
      if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

      int color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0xFF0000FF;    break; //red
        case 2:  color = 0x00FF00FF;  break; //green
        case 3:  color = 0x0000FFFF;   break; //blue
        case 4:  color = 0xFFFFFFFF;  break; //white
        default: color = 0xFFFF00FF; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color - 88;}

      //draw the pixels of the stripe as a vertical line
	  for (int y = drawStart; y < drawEnd; y++)
		mlx_put_pixel(vars->img, x, y, color);
    }
}

void hook(void *param)
{
	t_vars	*vars;
	double moveSpeed = 0.04;
	double rotSpeed = 0.025;

	vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
	{
      if(worldMap[(int)(*vars->posX + *vars->dirX * moveSpeed)][(int)*vars->posY] == false) *vars->posX += *vars->dirX * moveSpeed;
      if(worldMap[(int)*vars->posX][(int)(*vars->posY + *vars->dirY * moveSpeed)] == false) *vars->posY += *vars->dirY * moveSpeed;
	}
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
    {
      if(worldMap[(int)(*vars->posX - *vars->dirX * moveSpeed)][(int)*vars->posY] == false) *vars->posX -= *vars->dirX * moveSpeed;
      if(worldMap[(int)*vars->posX][(int)(*vars->posY - *vars->dirY * moveSpeed)] == false) *vars->posY -= *vars->dirY * moveSpeed;
    }
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = *vars->dirX;
      *vars->dirX = *vars->dirX * cos(-rotSpeed) - *vars->dirY * sin(-rotSpeed);
      *vars->dirY = oldDirX * sin(-rotSpeed) + *vars->dirY * cos(-rotSpeed);
      double oldPlaneX = *vars->planeX;
      *vars->planeX = *vars->planeX * cos(-rotSpeed) - *vars->planeY * sin(-rotSpeed);
      *vars->planeY = oldPlaneX * sin(-rotSpeed) + *vars->planeY * cos(-rotSpeed);
    }
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = *vars->dirX;
      *vars->dirX = *vars->dirX * cos(rotSpeed) - *vars->dirY * sin(rotSpeed);
      *vars->dirY = oldDirX * sin(rotSpeed) + *vars->dirY * cos(rotSpeed);
      double oldPlaneX = *vars->planeX;
      *vars->planeX = *vars->planeX * cos(rotSpeed) - *vars->planeY * sin(rotSpeed);
      *vars->planeY = oldPlaneX * sin(rotSpeed) + *vars->planeY * cos(rotSpeed);
    }
	render(param);
}

int main(int argc, char *argv[])
{
  double posX = 22, posY = 12;  //x and y start position
  double dirX = -1, dirY = 0; //initial direction vector
  double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

  double time = 0; //time of current frame
  double oldTime = 0; //time of previous frame

  mlx_t			*mlx;
  mlx_image_t	*img;

  mlx = mlx_init(screenWidth, screenHeight, "Raycaster", false);
  if (!mlx)
	  exit(EXIT_FAILURE);
  img = mlx_new_image(mlx, screenWidth, screenHeight);

  /*screen(screenWidth, screenHeight, 0, "Raycaster");*/
  //while(!done())
  //{
	/*
    //timing for input and FPS counter
    oldTime = time;
//TODO get time and print
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
//TODO redraw
    redraw();
    cls();

    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

//TODO events
    readKeys();
    //move forward if no wall in front of you
    if(keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }
  //}
  */

	t_vars vars = {mlx, img, &posX, &posY, &dirX, &dirY, &planeX, &planeY};
  	render(&vars);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &hook, &vars);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
