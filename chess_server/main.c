
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "main.h" 


#include <pthread.h>
v_info_t fb_v;


void create_scr_fb( void)
{
    int fd;
    u32_t *p;
    struct fb_var_screeninfo fb_var;
    fd = open("/dev/fb0",O_RDWR);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    if(ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) <0) 
    {
        perror("ioctl");
        exit(1);
    }

    fb_v.w = fb_var.xres;
    fb_v.h = fb_var.yres;
    fb_v.bpp = fb_var.bits_per_pixel;

    //printf("w = %d\th = %d\tbpp = %d\t\n",fb_v.w,fb_v.h,fb_v.bpp);

    p = mmap(NULL, fb_v.w*fb_v.h*fb_v.bpp/8, PROT_WRITE, MAP_SHARED, fd, 0);
    fb_v.mem = p;
    *p = 0x00ff0000;
    memset(p,0,1280*1024*4);
    close(fd);
}
void one_pixel(int x, int y, u32_t color)
{
    u32_t *p;
    p = fb_v.mem;
    p[x+y*fb_v.w] = color;
}
/***********************test**************************************/
/*
void screen(void)
{

    int i, j;
    u32_t *p;
    p = fb_v.fbmem;
    for (i = 0; i < fb_v.w; i++) 
    {
        for (j = 0; j < fb_v.h; j++) 
        {
             p[j*fb_v.w+i] = 0x00ff0000;   
        }
    }

}
void h_line(u32_t h)
{
    int i, j;
    u32_t *p;
    p = fb_v.fbmem;
    j = h;
    for (i = 0; i < fb_v.w; i++) 
    {
        one_pixel(i, j, 0x00ff0000);
    }
}
void v_line(u32_t v)
{
    int i, j;
    u32_t *p;
    p = fb_v.fbmem;
    i = v;
    for (j = 0; j < fb_v.h; j++) 
    {
        p[j*fb_v.w+i] = 0x00ff0000;   
    }
}
*/
/*****************************************************************/
int main(void)
{
    pthread_t id;
    int  ret;
/*
    fb_line(0,0,1279,1023,0x0000ff00);
    fb_line(0,1023,1279,0,0x00ff0000);

    fb_line(0,10,1279,600,0x00ff0000);

    fb_line(0,10,100,600,0x00ff0000);

    sleep(9);
*/
    create_scr_fb(); 
/*
    memset((char *)fb_v.mem,0,1280*1024);
    chess_board();
    chess_print(130,80);
    draw_circle(500,500,0x0000ff00);
    draw_circle(100,100,0x00ff0000);
    draw_circle(200,200,0x000000ff);
   
    fb_circle(500, 500, 300, 0x00ff0000);
*/
    desktop();
    chess_board();
//   chess_print(1030,800,0x0000ff00);
/*
    draw_cursor(500,500);
    sleep(1);
    restore_shape(500,500);
    draw_cursor(50,50);
    sleep(1);
    restore_shape(50,50);
    draw_cursor(1000,1000);
    sleep(1);
    restore_shape(1000,1000);

    sleep(10);
*/
   server_init() ;
   ret= pthread_create(&id,NULL,(void*)mouse_doing,NULL);
   while(1) recv_msg();

   return 0;
}







