#include "../lib/csapp.h"

#include "find_worker.h"

void find_worker(char *ip_buf){
        char IP_ADDR[CSIZE];
        printf("please enter the server IP address!\n");
        scanf("%s",IP_ADDR);
  
        int sockfd;
        int len;
        struct sockaddr_in address;

        int result;
        char buf[CSIZE];
        memset(buf,0,sizeof(buf));

        sockfd  = socket (AF_INET, SOCK_STREAM, 0);

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(IP_ADDR);
        address.sin_port = htons(PORTCT);

        len = sizeof(address);
        result = connect (sockfd, (struct sockaddr *) & address, len);

        if (result == -1){
                perror("Connect failed!");
        }



        int sendbytes, recvbytes = 0;


        memset(buf, 0, sizeof(buf));
        strcpy(buf,"getip");

        if ((sendbytes = write(sockfd, buf, CSIZE)) == -1){
                perror("send to tracker failed!");
        }
        memset(buf, 0, sizeof(buf));

        if ((recvbytes = recv(sockfd,ip_buf,CSIZE,0)) == -1){
                perror("recv from tracker failed!");
        }

 //   strcpy(ip_buf, buf);
        printf("%s\n", ip_buf);

        close(sockfd);
}
