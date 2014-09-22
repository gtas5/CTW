#include "../lib/csapp.h"
#include "find_worker.h"
#include "upload_file.h"
int main(int argc, char **argv)
{
	char ip_buf[100];
	memset(ip_buf, 0, sizeof(ip_buf));
	find_worker(ip_buf);
	upload_file(ip_buf);
	return 0;
}
