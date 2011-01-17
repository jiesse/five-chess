#include <stdio.h> 

#include "main.h"

#define LEN 20


void draw_circle(int x, int y, u32_t color)
{
   int x0 = 0;
   int y0 = 0;

   x0 = x - LEN;
   y0 = y - LEN;
   u32_t LEN_2;
   LEN_2 = LEN*LEN;

   while(x0 <= (x + LEN))
   {
       while(y0 <= (y + LEN))
       {
         
         if(((y0 - y)*(y0 - y)+(x0 - x)*(x0 - x)) <= LEN_2)
         {
                one_pixel(x0,y0,color); 
         }
         y0++;
       
       
       }
       y0 = y - LEN;
       x0++;
   }
   return ;

}

