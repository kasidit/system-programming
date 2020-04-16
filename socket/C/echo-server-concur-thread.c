/*
 A simple echo server program 
 Kasidit Chanchio (kasiditchanchio@gmail.com)
*/
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <sys/wait.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP		"127.0.0.1"
#define SERV_PORT 	18800

#define MAXLINE	100
#define MAX_CONNECTIONS	100
#define MAX_PROCESSES	50

#include <pthread.h>

int lis_fd;
//int pid_array[MAX_PROCESSES];
int conn_fd;
pthread_t tid;
//int global_fd[MAX_CONNECTIONS];
int numtid = 0;
struct sockaddr_in serv_addr;

void process_request(void *t);

main(int argc, char *argv[]){

        int n;
	lis_fd = socket(AF_INET, SOCK_STREAM, 0); 

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	bind(lis_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)); 

	listen(lis_fd, 5);

        while(1){

	  if((conn_fd = accept(lis_fd, NULL, NULL)) < 0){
		printf("Accept: Error occured\n");
		exit(1);
	  }
       
          numtid++;
          if((n = pthread_create(&tid, NULL, (void *) &process_request, (void *) &conn_fd)) != 0){
		printf("Pthread create error\n");
		exit(1);

          }

        }

	close(lis_fd);

}

void process_request(void *t){
    int mytid = numtid;
    int n, m;
    int param =  *((int *)t); 
    int tmp_fd = conn_fd;
    char line[MAXLINE];

    printf("t[%d]:  param = %d tmp_fd = %d\n", mytid, param, tmp_fd);

    while ((n = read(tmp_fd, line, MAXLINE)) != 0){
        printf("line = %s with n = %d characters\n", line, n);
        fflush(stdout);
        m = write(tmp_fd, line, n);
        printf("write line = %s for m = %d characters\n", line, m);
        fflush(stdout);
    }

    close(tmp_fd);
}

// -----Basic Communication Utilities-----
int accept_cr(int fd, struct sockaddr *addr, socklen_t *len){
	int ret;
repeat_accept:
        ret = accept(fd, addr, len);
        if (ret < 0) {
            if (errno == EINTR){
                goto repeat_accept;
	    }
	    printf("accept error errno=%d fd=%d\n", errno, fd);
        }
	return ret;
}

int write_full(int fd, const void *buf, size_t count){
    ssize_t ret = 0;
    ssize_t total = 0;

    while (count) {
        ret = write(fd, buf, count);
        if (ret < 0) {
            if (errno == EINTR){
                continue;
	    }
	    printf("write error errno=%d fd=%d\n", errno, fd);
            return ret;
        }
        else if (ret == 0){
            return ret; 
        }

        count -= ret;
        buf += ret;
        total += ret;
    }

    return total;
}

int read_full(int fd, void *buf, size_t count){
    ssize_t ret = 0;
    ssize_t total = 0;

    while (count) {
        ret = read(fd, buf, count);
        if (ret < 0) {
            if (errno == EINTR){ 
	        printf("read INTERRUPTED! %d\n", errno);
                continue;
	    } 
	    printf("read error errno=%d fd=%d\n", errno, fd);
            return ret;
        }
        else if (ret == 0){
            return ret; 
        }

        count -= ret;
        buf += ret;
        total += ret;
    }

    return total;
}
