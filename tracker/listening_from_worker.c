#include "../lib/csapp.h"
#include "listening_from_worker.h"

void listening_from_worker(){
        int server_sockfd,client_sockfd;   
        int server_len,client_len;
   
        struct sockaddr_in server_sockaddr,client_sockaddr;
   
   
      server_sockfd = socket(AF_INET,SOCK_STREAM, 0); // 定义套接字类型
   
      server_sockaddr.sin_family=AF_INET;
      server_sockaddr.sin_port=htons(PORTTW);
      server_sockaddr.sin_addr.s_addr=INADDR_ANY;
   
      server_len=sizeof(server_sockaddr);
   
    //允许重复使用本地地址和套接字绑定
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
      printf("Listening from worker\n");
   
      client_len=sizeof(client_sockaddr);

      pthread_t thread[CSIZE];
      int i,ret;

      while(1) {  
        if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_sockaddr,&client_len))==-1) {
                  perror("accept error:");
                  exit(1);
            }
                            printf("%s登录服务器\n",inet_ntoa(client_sockaddr.sin_addr));
                            strcpy(uses[num].ipaddr, inet_ntoa(client_sockaddr.sin_addr));

                            struct mypara mp;
                            mp.num=num++;
                            mp.data=client_sockfd;

                            ret = pthread_create(&thread[num],NULL,recv_mem,&(mp));
                            usleep(10000);        
      }
        close(client_sockfd);
}
