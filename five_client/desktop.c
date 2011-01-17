//#include <stdio.h>

#include "main.h"

extern v_info_t fb_v; 

extern const unsigned char gImage_zz[1572864];
int desktop(void)
{
   int x = 100;
   int y = 50;
   u32_t *p;
   p = fb_v.mem; 
/*
   for(y = 0; y < 768; y++)
   for(x = 0; x < 1024*4; x++)
        p[x+y*fb_v.w*4] = gImage_zz[x+y*1024*4] ;
*/
   for(y=0; y<fb_v.h; y++)
        for(x=0; x<fb_v.w; x++)
        {
            if(y>=Y_BEGUN && y<= Y_BEGUN+23*SIZE)
            {
                if(x>=X_BEGUN && x<= X_BEGUN+29*SIZE) 
                                 p[x+y*fb_v.w] = 0x00db9a4a;
                else
                                 p[x+y*fb_v.w] = 0x00a33833;

            }
            else
            {
                p[x+y*fb_v.w] = 0x00a33833;
            
            }
        
        
        }
    return 0;

}
