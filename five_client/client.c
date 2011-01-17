#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "main.h"

#define SERVER_PORD         20001
#define BUFFER_SIZE        256 


unsigned char buffer[BUFFER_SIZE] = {0,0,0,0,1,1,1,1,0,0,0,0,0};

extern char board[P_NUM*V_NUM];
  
int n, len, i;
int client_sock;
socklen_t server_len;
struct sockaddr_in server;


int client_init(void)
{
/*
    if(argc<2)
    {
    
         printf("\n");
         printf("sorry,your type is wrong\n");    
         printf("usage: %s x.x.x.x(server ip)\n",argv[0]);
         exit(EXIT_FAILURE);
    }
*/
    if((client_sock = socket(AF_INET, SOCK_DGRAM, 0))< 0)
    {
       fprintf(stderr,"%s\n",strerror(errno)) ;
       exit(EXIT_FAILURE);
    
    }
    else
    {
         printf("create socket ok !\n");
    }



    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORD);
    server.sin_addr.s_addr = inet_addr("10.1.14.30");

    server_len = sizeof(server);
    send_msg(0,0);
    return 0;

}
int send_msg(int x, int y)
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
    
    board[i+j*V_NUM]  = 1;
    memcpy((char*)&buffer[4],(char *)&i,4);
    memcpy((char*)&buffer[8],(char *)&j,4);

    sendto(client_sock,buffer,13, 0, (struct sockaddr*)&server, server_len) ;
    return 0;

}

int recv_msg(void)
{

    int i = 0,j = 0;
    server_len = sizeof(server);

    recvfrom(client_sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server, &server_len);
    memcpy((char*)&i,(char *)&buffer[4],4);
    memcpy((char*)&j,(char *)&buffer[8],4);

    printf("%d %d\n",i,j);
    fb_circle(X_BEGUN+i*SIZE, Y_BEGUN+j*SIZE, 12, 0xffffffff);
    board[i+j*V_NUM]  = 2;

    check_all();
    return 0;
}

