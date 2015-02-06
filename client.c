#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
	struct sockaddr_in sin;
	int s, bytes;
	char buf[BUFSIZ + 1];
	char * host;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Error while creating socket");
		return 1;
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(1113);
	
	if (argc > 0)	host = argv[1];

	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		perror("Error while attempting to connect");
		return 2;
	}

	while ((bytes = read(s, buf, BUFSIZ)) > 0)
		write(1, buf, bytes);

	close(s);
	return 0;
}
