
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

#define SERVER_PORT		20001
#define BUFFER_SIZE		256

extern u32_t color_choice;
extern char one;

unsigned char buffer[BUFFER_SIZE];
typedef struct {
char dest;
char source;
char type;
char len;
int x;
int y;
}msg;
msg *p = (msg *)buffer;

char board[P_NUM*V_NUM];

char c;
int i,len = 12;
int x = 3, y = 2;
int cx, cy;
int server_sock;
socklen_t client_len;
struct sockaddr_in server,client;
struct in_addr in;

void recv_msg(void)
{
  
    client_len = sizeof(client);
    len = recvfrom(server_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &client_len);
    if (len >= 0)
    {
       cx = p->x;
       cy = p->y;
       board[cx+cy*P_NUM] = 2;

       printf("%d\n",cx);
       printf("%d\n",cy);

       cx = (cx)*SIZE + X_BEGUN;    
       cy = (cy)*SIZE + Y_BEGUN;    

       color_choice = 0x01000000;  

       fb_circle(cx,cy, 12, 0xffffffff);
       check_all();
    }
    
}
int send_msg(int x, int y)
{
   len = 13;
   int dx = (x-X_BEGUN)%30;
   int dy = (y-Y_BEGUN)%30;
   x = (dx - 15 < 0)?x-dx:x+30-dx; 
   y = (dy - 15 < 0)?y-dy:y+30-dy; 
   x = (x - X_BEGUN)/SIZE;
   y = (y - Y_BEGUN)/SIZE;
   
    p->x = x;
    p->y = y;
    //printf("%d %d\n",x,y);
    sendto(server_sock, buffer, len, 0, (struct sockaddr *)&client, client_len);
    return 0;
}

int server_init(void)
{
	
	if ((server_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
        printf("create socket ok!\n");
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htons(INADDR_ANY);

	if(bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
        printf("bind addr ok!\n");
        printf("\n");
	}
  #if 1
		client_len = sizeof(client);
		len = recvfrom(server_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client, &client_len);
		if (len < 0)
		{
			close(server_sock);
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		else
		{
            //printf("recvfrom client ok!\n");
            //in.s_addr = client.sin_addr.s_addr;
            //printf("client ip  : %s\n", inet_ntoa(in));
            //printf("client port: %d\n", ntohs(client.sin_port));
            //printf("\n");
		}
  #endif
    return 0;

}

