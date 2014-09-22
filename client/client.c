#include "../lib/csapp.h"
#define PORTCT 8888
#define PORTTW 18888
#define PORTCW 28888
#define SIZE 10240
#define CSIZE 100


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

int main(int argc, char **argv)
{
  int clientfd, port;
  int filefd, filesize;
  char host[MAXLINE], buf[MAXLINE], response[MAXLINE], filename[MAXLINE], version[MAXLINE];
  char *srcp;
  struct stat sbuf;
  rio_t rio;
  char ip_buf[100];
  memset(ip_buf, 0, sizeof(ip_buf));
  

  find_worker(ip_buf);


  strcpy(host, ip_buf);
  printf("Connect succeed!\n");
  port = PORTCW;

  clientfd = Open_clientfd(host, port);
  
  



  /* Upload file to the server */
  fprintf(stdout, "Enter the file name you want to upload:");
  scanf("%s", filename);
  fprintf(stdout, "Enter version:");
  scanf("%s", version);
  
  if (stat(filename, &sbuf) < 0) {
    fprintf(stderr, "%s Not found", filename);
    exit(0);
  }
  
  /* Send upload file's name to server */
  sprintf(buf, "%s %s\r\n", filename,version);
  Rio_writen(clientfd, buf, strlen(buf));

  /* Send upload file's body to server */
  filefd = Open(filename, O_RDONLY, 0);
  filesize = sbuf.st_size;
  srcp = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, filefd, 0);
  Close(filefd);
  Rio_writen(clientfd, srcp, filesize);
  Rio_writen(clientfd, "\r\n", 2);
  
//  Rio_writen(1, srcp, filesize);
  Munmap(srcp, filesize);
 
  /* Read request line from Worker server */
  //Rio_readinitb(&rio, clientfd);
  //Rio_readlineb(&rio, response, MAXLINE);

  while  ( Read(clientfd, response, MAXLINE) > 0) {
          fprintf(stdout, "Response from Worker Server:\n%s", response);
          memset(response, 0, sizeof(response));
  }


  return 0;
}
