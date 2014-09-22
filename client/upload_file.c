#include "../lib/csapp.h"

#include "upload_file.h"


void upload_file(char* host){
	int clientfd, port;
	int filefd, filesize;
	char buf[MAXLINE], response[MAXLINE], filename[MAXLINE], version[MAXLINE];
	char *srcp;
	struct stat sbuf;
	rio_t rio;

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


} 