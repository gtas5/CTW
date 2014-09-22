#include "../lib/csapp.h"

void doit(int fd);
void responseToClient(int fd, char *filename);
void exeClientUploadFile(int fd, char *filename);
void sig_cld(int signo);



typedef struct PACKEDMEM         //定义一个mem occupy的结构体
{
char name[20];      //定义一个char类型的数组名name有20个元素
long long total; 
char name2[20];
long long free;                       
}MEM_OCCUPY;


void get_memoccupy (MEM_OCCUPY *mem) {
  FILE *fd;          
      int n;             
      char buff[256];   
      MEM_OCCUPY *m;
      m=mem;
                                                                                                              
      fd = fopen ("/proc/meminfo", "r"); 

      fgets (buff, sizeof(buff), fd); 
        sscanf (buff, "%s %d %s", m->name, &m->total, m->name2); 
    
      fgets (buff, sizeof(buff), fd); //从fd文件中读取长度为buff的字符串再存到起始地址为buff这个空间里 
      sscanf (buff, "%s %d", m->name2, &m->free, m->name2); 
    
      fclose(fd);     //关闭文件fd
}

void *send_meminfo(){
  char IP_ADDR[50];
  printf("please enter the server IP address!\n");
  scanf("%s",IP_ADDR);
  
  int sockfd;
  int len;
  struct sockaddr_in address;

  int result;

  sockfd  = socket (AF_INET, SOCK_STREAM, 0);

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(IP_ADDR);
  address.sin_port = htons(PORTTW);

  char buf[100];
  memset(buf, 0, sizeof(buf));

  len = sizeof(address);
  result = connect (sockfd, (struct sockaddr *) & address, len);

  if (result == -1){
    perror("Connect failed!");
    return 1;
  }
  printf("Connect succeed!");

  int sendbytes = 0;
  
  while(1){
    MEM_OCCUPY mem_stat;
    get_memoccupy ((MEM_OCCUPY *)&mem_stat);
    sprintf(buf, "%d", mem_stat.free);  
    if ((sendbytes = write(sockfd, buf, 100)) == -1){
      perror("send to server failed!");
    }
    usleep(1000000);
    memset(buf,0,sizeof(buf));
  }

  close(sockfd);
}

void p_send_meminfo(){
  pthread_t clit;
             int cl;
             cl = pthread_create(&clit,NULL, send_meminfo,NULL);
}




int main(int argc, char **argv)
{

  p_send_meminfo();



  int listenfd, connfd, port, clientlen;
  struct sockaddr_in clientaddr;



  /* signal */
  struct sigaction act;
  act.sa_handler = sig_cld;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  sigaction(SIGCLD, &act, NULL);
  
  /* Check command line args */
  
  port = PORTCW;
  
  listenfd = Open_listenfd(port);
  while (1) {
        clientlen = sizeof(clientaddr);
        if ( (connfd = accept(listenfd, (SA *)&clientaddr, &clientlen)) < 0) {  
            if (errno == EINTR)
            continue;
        else
    unix_error("accept error");
  }
    doit(connfd);
    Close(connfd);
  }
}

void doit(int fd) 
{
  int n , filefd;
  struct stat sbuf;
  char buf[MAXLINE], filename[MAXLINE], version[MAXLINE];
  rio_t rio;
  
  /* Read the upload file's name */
  Rio_readinitb(&rio, fd);
  Rio_readlineb(&rio, buf, MAXLINE);
  printf("Buf include filename is: %s",buf); 
  sscanf(buf, "%s %s", filename, version);
  //write(1,filename, strlen(filename));
  //write(1,version, strlen(version));
  //  printf("filename length:%d\n",strlen(filename));
  
  /* Create upload file */
  filefd = Open(filename, O_WRONLY|O_APPEND|O_CREAT|O_TRUNC, 0777);
  
  /* Read the file's content and write to local */
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) {
      printf("server received:%s %d bytes\n",buf, n);
      if (strcmp(buf, "\r\n") == 0) // use "\r\n" for the end mark
	 break;
      Rio_writen(filefd, buf, n);
  }

    /* exec the file client upload */
  
  exeClientUploadFile(fd, filename);
  

  
}
  
   
void responseToClient(int fd, char *filename) 
{ 
  char response[MAXLINE];
  
  sprintf(response, "%s upload success!\n", filename);
  Rio_writen(fd, response, strlen(response));
}


void exeClientUploadFile(int fd,  char *filename)
{
  pid_t pid;
  char exeFileName[MAXLINE];
  
  sprintf(exeFileName,"./%s",filename);
  printf("ExefileName: %s\n", exeFileName);  
  
  pid = Fork();
  if (pid == 0) {
      /* Response to client */
    responseToClient(fd, filename);

    Dup2(fd, STDOUT_FILENO);
    if (execlp("sh", "sh", filename, (char *)0) < 0) {
      unix_error("Execlp error");
    }
  }
}

void sig_cld(int signo)
{
  int status;
  while(waitpid(-1, &status, WNOHANG) > 0);
}