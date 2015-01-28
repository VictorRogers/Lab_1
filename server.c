#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define SERVER_PORT 1113
#define MAX_PENDING 5

int main() {
	struct sockaddr_in sin;
	int len;
	int s, new_s;
	time_t t;
	struct tm *tm;
	FILE *timef;

	/*address data structure*/
	memset(&sin, 0, sizeof(sin));	
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(SERVER_PORT);

	/*passive open*/
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket err");
		exit(1);
	}
	
	if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
		perror("bind error");
		exit(1);
	}

	listen(s, MAX_PENDING);

	while(1) {
		len = sizeof(sin);

		if ((new_s = accept(s, (struct sockaddr *)&sin, &len)) < 0) {
			perror("accept error");
			exit(1);
		}
		
		tm = gmtime(&t);
		fprintf(timef, "%.4i-%.2i-%.2iT%.2i:%.2i:%.2iZ\n",
				tm->tm_year + 1900,
				tm->tm_mon + 1,
				tm->tm_mday,
				tm->tm_hour,
				tm->tm_min,
				tm->tm_sec);
			
		fclose(timef);
	}
}
