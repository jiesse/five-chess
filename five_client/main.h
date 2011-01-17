#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>

#define X_BEGUN 100  //x direction begin pexil
#define Y_BEGUN 50  //y direction begin pexil
#define SIZE 30 
#define R 12 
#define P_NUM 24 
#define V_NUM 30 

typedef unsigned int u32_t;
typedef unsigned char u8_t;

extern void one_pixel(int x, int y, u32_t color);
int fb_line(int x1, int y1, int x2, int y2, u32_t color);
void chess_board(void);
int chess_print(int x, int y);
void draw_circle(int x, int y, u32_t color);
extern int fb_circle(int x0, int y0, int r, u32_t color);

extern int save_shape(int x,int y);
extern int restore_shape(int x, int y);
extern int draw_cursor(int x, int y);
extern int mouse_doing(void);
extern int desktop(void);
extern int choose_color(int x, int y);
extern int chess_count(int x, int y);
extern int client_init(void);
extern int server_end(void);
extern int send_msg(int x, int y);
extern int recv_msg(void);
extern int check_all(void);

typedef struct
{
    int w;
    int h;
    int bpp;
    void *mem;


}v_info_t;
typedef struct
{
    int dx;
    int dy;
    int dz;

    int button;

}m_event;


#endif
