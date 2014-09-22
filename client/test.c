#include <stdio.h>

int main(void)
{
	char *bp;
	char buf[10] = "1234abc";
	bp = buf;
	*bp = 0;
	printf("%s",buf);
		
	return 0;
}
