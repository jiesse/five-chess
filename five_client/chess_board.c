#include "main.h" 


extern int fb_line(int x1, int y1, int x2, int y2, u32_t color);


void chess_board(void)
{
    int i;
    int y = 0;
    int x = 0;
    for (i = 0; i < 24; i++) 
    {
        fb_line(X_BEGUN,Y_BEGUN+y,X_BEGUN+SIZE*29,Y_BEGUN+y,0x00ff0000) ;
        y += SIZE;
    }
   for (i = 0; i < 30; i++) 
    {
        fb_line(X_BEGUN+x,Y_BEGUN,X_BEGUN+x,Y_BEGUN+SIZE*23,0x00ff0000) ;
        x += SIZE;
    }
 
    return ;

}
