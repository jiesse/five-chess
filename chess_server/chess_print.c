#include <stdio.h>
#include "main.h"



extern void chess_board(void);
extern char board[P_NUM*V_NUM];

extern char  who ;
extern u32_t color_choice ;
/*
int choose_color(int x, int y)
{
    if(x>15 && x<65)
    {
        if(y>35 && y<85) 
        {
            color_choice = 0x0; 
          
        }
        else if(y>125 && y<175)
        {
            color_choice = 0xffffffff; 
           
        }
    }
    return 0;

}
*/
int chess_print(int x, int y)
{
   int x0 = 0;
   int y0 = 0;
   int x1 = X_BEGUN+SIZE*29;   
   int y1 = Y_BEGUN+SIZE*23;   


   if(x<X_BEGUN||x>x1||y<Y_BEGUN||y>y1)
   {
        return 1;
   }
 
   if(chess_count(x,y) == 1)
   {
        return 1; 
   }

   int c_x = (x - X_BEGUN)%SIZE;
   int c_y = (y - Y_BEGUN)%SIZE;

   x0 = (c_x>(SIZE/2))? x+SIZE -c_x: x-c_x; 
   y0 = (c_y>(SIZE/2))? y+SIZE -c_y: y-c_y; 
    
 


   fb_circle(x0,y0,R,color_choice);
   return 0;
}
