#include "../lib/csapp.h"

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