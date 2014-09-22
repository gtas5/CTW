#include "../lib/csapp.h"
#include "recv_mem.h"

void *recv_mem(void* arg){
            struct mypara *pstru;
            pstru = (struct mypara *) arg;
            int n = pstru->num;
            int new_client_sockfd = pstru->data;
            int i=0;
            char buf[CSIZE];
            memset(buf,0,CSIZE);

            int recvbytes;  
    
            while(1) {
                    if((recvbytes=recv(new_client_sockfd,buf,CSIZE,0))==-1) {
                            perror("read client_sockfd failed:");
                    }
                    usleep(100000);
                    strcpy(uses[n].mems,buf);
            }
}