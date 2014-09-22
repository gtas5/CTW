#include "../lib/csapp.h"
#include "to_client.h"


void *to_client(){

        int server_sockfd,client_sockfd;   
        int server_len,client_len;
        char tmp[CSIZE];
        struct sockaddr_in server_sockaddr,client_sockaddr;
        char buf[CSIZE];

        server_sockfd = socket(AF_INET,SOCK_STREAM, 0); // 定义套接字类型
   
        server_sockaddr.sin_family=AF_INET;
        server_sockaddr.sin_port=htons(PORTCT);
        server_sockaddr.sin_addr.s_addr=INADDR_ANY;
   
        server_len=sizeof(server_sockaddr);
        int j=1;
        setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&j,sizeof(j));
   
    //绑定端口
        if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,server_len)==-1){
                perror("bind:");
                exit(1);       
        }
   
   
        if(listen(server_sockfd,5)==-1){
                perror("listen:");
                exit(1);   
        }
        printf("Listening from client\n");
   
        client_len=sizeof(client_sockaddr);
        while(1) {  
            if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_sockaddr,&client_len))==-1) {
                        perror("accept error:");
                        exit(1);
                }
                memset(buf, 0, sizeof(buf));
                printf("%s收到请求\n",inet_ntoa(client_sockaddr.sin_addr));
                recv(client_sockfd,buf,CSIZE,0);
                printf("%s\n",buf);
                if (strcmp(buf,"getip") == 0){
                    if (num > 0){
                        int sendbytes = 0;
                        sort_mem();
                        memset(buf, 0, sizeof(buf));
                        strcpy(buf, uses[0].ipaddr);
                        printf("%s\n",buf);
                        usleep(1000000);
                        if ((sendbytes = write(client_sockfd, buf, CSIZE)) == -1){
                                perror("send to server failed!");
                            }    
                        printf("success!\n");
                        } else perror("No servers stand by!");  
                }
            usleep(100000);                   
            }
        close(client_sockfd);
}