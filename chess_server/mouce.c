#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include "main.h"
#include <pthread.h>

#define BORD 0x0000ff00
#define X__ 0x0000ff00

#define aaa 0x0000ff00
#define T__ 0x00db9a4a
#define v__ 0x0000ff00

#define C_HEIGHT 33  
#define C_WIDTH 19 
#define BUFFER_SIZE 13
extern v_info_t fb_v; 
static u32_t shape_save[C_HEIGHT*C_WIDTH];
char board[P_NUM*V_NUM];

char  one = 1;
u32_t color_choice = 0x0;
/*
static u32_t cursor_pixel[C_WIDTH*C_HEIGHT] =
{
BORD,T__,T__,T__,T__,T__,T__,T__,T__,T__,
BORD,BORD,T__,T__,T__,T__,T__,T__,T__,T__,
BORD,X__,BORD,T__,T__,T__,T__,T__,T__,T__,
BORD,X__,X__,BORD,T__,T__,T__,T__,T__,T__,
BORD,X__,X__,X__,BORD,T__,T__,T__,T__,T__,
BORD,X__,X__,X__,X__,BORD,T__,T__,T__,T__,
BORD,X__,X__,X__,X__,X__,BORD,T__,T__,T__,
BORD,X__,X__,X__,X__,X__,X__,BORD,T__,T__,
BORD,X__,X__,X__,X__,X__,X__,X__,BORD,T__,
BORD,X__,X__,X__,X__,X__,X__,X__,X__,BORD,
BORD,X__,X__,X__,X__,X__,BORD,BORD,BORD,BORD,
BORD,X__,X__,BORD,X__,X__,BORD,T__,T__,T__,
BORD,X__,BORD,T__,BORD,X__,X__,BORD,T__,T__,
BORD,BORD,T__,T__,BORD,X__,X__,BORD,T__,T__,
T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__,
T__,T__,T__,T__,T__,BORD,X__,X__,BORD,T__,
T__,T__,T__,T__,T__,T__,BORD,BORD,T__,T__

};
*/
static u32_t hand_pixel[C_WIDTH*C_HEIGHT] =
{
T__,T__,T__,T__,T__,T__,T__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,T__,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,T__,T__,T__,T__,T__,T__,T__,T__,
T__,aaa,T__,T__,T__,T__,aaa,v__,aaa,T__,T__,aaa,T__,T__,T__,T__,T__,T__,T__,
aaa,v__,aaa,T__,T__,T__,aaa,v__,aaa,T__,aaa,v__,aaa,T__,aaa,T__,T__,T__,T__,
aaa,v__,aaa,aaa,T__,T__,aaa,v__,aaa,aaa,v__,v__,v__,aaa,v__,aaa,T__,T__,T__,
aaa,v__,v__,aaa,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
aaa,v__,v__,v__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,
T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,T__,
T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,T__,
/*T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,T__,
T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,T__,
T__,T__,T__,T__,T__,aaa,v__,v__,v__,v__,v__,v__,v__,v__,v__,aaa,T__,T__,T__,
*/
};
/**********************************************************************/
int chess_count(int x, int y)
{
    int i = x;
    int j = y;
    
    i = (i-X_BEGUN)/SIZE;
    j = (j-Y_BEGUN)/SIZE;

    if(((x-X_BEGUN)%SIZE) > (SIZE/2))
    {
        i++; 
    }
    if(((y-Y_BEGUN)%SIZE) > (SIZE/2))
    {
        j++; 
    }
    
   if( board[i+j*V_NUM] != 0) 
   {
            return 1;
   }
    board[i+j*V_NUM]  = one;

    return 0;

}
int check_five(int x, int y)
{ int i = 0;
    int j = 0;
    char counter = 0;
    char storage = 0;
    char nx = 0;
    char ny = 0;
     
    char  n_x[4] = {0,1,1,1};
    char  n_y[4] = {1,0,1,-1};
    
    storage = board[x+y*V_NUM];
    if(storage == 0)
    {
        return 0; 
    }

    for(j = 0; j<4; j++)
    {
        counter = 1;
        nx = x;
        ny = y;
        
        for(i =1; i<5; i++)
        {
            nx += n_x[j] ;
            ny += n_y[j] ;
            if(board[nx+ny*V_NUM] == storage) 
            {
                counter++; 
            }
            else
            break;
        
        }
        if(counter == 5)
        {
            return storage; 
        
        }
   }
    return 0;

}
int check_all(void)
{
    int i = 0;
    int j = 0;
    char storage = 0;
    for(i=0; i<P_NUM; i++)
    {
        for(j=0; j<V_NUM; j++)
       { 
            if((storage=check_five(i,j)) != 0) 
            {
                (storage == 2)? printf("white won!\n") : printf("black won!\n");
                 return 1;
            }
       }
     }
     return 0;

}



/**************************************************************************/
int save_shape(int x,int y)
 {
    int i = 0;
    int j = 0;
   
    u32_t *p = fb_v.mem;

    for(i = 0; i < C_HEIGHT; i++)
        for (j = 0; j < C_WIDTH; j++) 
        {
            shape_save[j+i*C_WIDTH] = p[x+j+(y+i)*fb_v.w];
        }
     return 0;
 
 
 }
int restore_shape(int x, int y)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < C_HEIGHT; i++)
        for (j = 0; j < C_WIDTH; j++) 
        {
            one_pixel(x+j, y+i, shape_save[j+i*C_WIDTH]);
        }
    
    return 0;

}


int draw_cursor(int x, int y)
{
    int i = 0;
    int j = 0;

   save_shape(x, y);

    for(i = 0; i < C_HEIGHT; i++)
        for (j = 0; j < C_WIDTH; j++) 
        {
           // one_pixel(x+j, y+i, cursor_pixel[j+i*C_WIDTH]);
           if(hand_pixel[j+i*C_WIDTH] == T__)
           {}

                //one_pixel(x+j, y+i, shape_save[j+i*C_WIDTH]);
           else 
                one_pixel(x+j, y+i, hand_pixel[j+i*C_WIDTH]);
        }
    
    return 0;

}


int get_m_info(int fd, m_event *event)
{

    char buf[8] = {0};
    int n;

    n = read(fd, buf, 8);
    if(n <= 0)
    {
        return 0; 
    }
    
    event->button = (buf[0]&0x07);
    event->dx = buf[1];
    event->dy = -buf[2];
    event->dz = buf[3];
    

    return n;

}
int print_choice(void)
{
    fb_circle(40,60, 25, 0x0);
    fb_circle(40,150, 25, 0xffffffff);

    return 0;
}
int process_msg(int x_msg, int y_msg)
{


    board[x_msg+y_msg*V_NUM]  = 1;
    fb_circle(X_BEGUN+SIZE*x_msg, Y_BEGUN+SIZE*y_msg,15,0xffffffff);
    printf("ok\n");

    return 0;


}
int mouse_doing(void)
{
    m_event mevent;
    int fd; int mx = 512; int my = 384;

    fd = open("/dev/input/mice",O_RDWR|O_NONBLOCK);

    if(fd < 0)
    {
        perror("open") ;
        exit(1);
    }
    
    draw_cursor(mx,my);
    print_choice();
     
     while(1)
     {

       if( get_m_info(fd,&mevent) > 0) 
       {
            restore_shape(mx, my) ;
            mx += mevent.dx;
            my += mevent.dy;

            mx =( (mx >= 0) ? mx :0 );
            my =( (my >= 0) ? my :0 );
     
            if(mx >= fb_v.w-C_WIDTH)
            {
                mx = (fb_v.w-C_WIDTH) ;
            
            }
            if(my >= fb_v.h-C_HEIGHT)
            {
                my = (fb_v.h-C_HEIGHT) ;
            
            }
            switch(mevent.button) 
            {

                case 1 :// restore_shape(mx,my);
                      //   chess_print(mx, my, 0x000000ff);
                             if(chess_print(mx, my)==0 )
                             {
                                send_msg(mx,my);
                                check_all();
                             }
                        // save_shape(mx, my);
                         break; 
                case 2 :break; 
                case 4 :break; 
                default :break; 
            
            }
    
            draw_cursor(mx,my);
          }
    
   } 
    return 0;

}





