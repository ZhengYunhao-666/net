

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <unistd.h>

#include <pthread.h>


#define BUFFER_LENGTH	128



// thread --> fd
void *routine(void *arg) {

	int clientfd = *(int *)arg;

	while (1) {
		
		unsigned char buffer[BUFFER_LENGTH] = {0};
		int ret = recv(clientfd, buffer, BUFFER_LENGTH, 0);
		if (ret == 0) {
			close(clientfd);
			break;
			
		}
		printf("buffer : %s, ret: %d\n", buffer, ret);

		ret = send(clientfd, buffer, ret, 0); // 

	}

}

// socket --> 
// bash --> execve("./server", "");
// 
// 0, 1, 2
// stdin, stdout, stderr
int main() {

// block
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);  // 
	if (listenfd == -1) return -1;
// listenfd
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);

	if (-1 == bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
		return -2;
	}

#if 0 // nonblock
	int flag = fcntl(listenfd, F_GETFL, 0);
	flag |= O_NONBLOCK;
	fcntl(listenfd, F_SETFL, flag);
#endif

	listen(listenfd, 10);

#if 0
	// int 
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	int clientfd = accept(listenfd, (struct sockaddr*)&client, &len);

	

	//printf("sendbuffer : %d\n", ret);
#else

	while (1) {

		
		struct sockaddr_in client;
		socklen_t len = sizeof(client);
		int clientfd = accept(listenfd, (struct sockaddr*)&client, &len);
		
		pthread_t threadid;
		pthread_create(&threadid, NULL, routine, &clientfd);

		//fork();

	}
	

#endif

}




