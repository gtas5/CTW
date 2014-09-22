#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
	int		n;
	int		nSocket;
	char	buf[1024];
	struct	sockaddr_in	sin;
	struct	iovec	iov[1];
	struct	msghdr	mh;
	if ((nSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "socket error:%s", strerror(errno));
		exit(0);
	}

	bzero(&sin, sizeof(struct sockaddr_in));
	if (inet_pton(AF_INET, "127.0.0.1", &(sin.sin_addr)) != 1)
	{
		fprintf(stderr, "inet_pton error:%s\n", strerror(errno));
		exit(0);
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(13);

	if (connect(nSocket, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0)
	{
		fprintf(stderr, "connect error:%s\n", strerror(errno));
		close(nSocket);
		exit(0);
	}
	
	bzero(&mh, sizeof(struct msghdr));
	mh.msg_name = NULL;
	mh.msg_namelen = 0;
	mh.msg_iov = iov;
	mh.msg_iovlen = 1;
	iov[0].iov_base = (char *)buf;
	iov[0].iov_len = 1024;
	memset(buf,0x00,sizeof(buf));
	recvmsg(nSocket, &mh, 0);
	printf("%s\n",buf);
	close(nSocket);
	return 0;
}
