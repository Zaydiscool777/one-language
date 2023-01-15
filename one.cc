#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]){
	int fd;
	char buffer[BUFFER_SIZE], line[MAX_LINE_LENGTH];
	ssize_t numRead;
	int lineLength;

	if(argc != 2 || strcmp(argv[1], "--help") == 0){
		printf("%s file\n", argv[0]);
		exit(EXIT_FAILURE);
	} // usage of the command so far

	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		printf("open file error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while((numRead = read(fd, buffer, BUFFER_SIZE)) > 0){
		for(int i = 0; i < numRead; i++){
			if(buffer[i] == '\n'){
				line[lineLength] = '\0';
				printf("%d\n", lineLength);
				lineLength = 0;
			}
			else{
				line[lineLength] = buffer[i];
				lineLength++;
			}
		}
	}

	if(numRead == -1){
		printf("read error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(close(fd) == -1){
		printf("close file error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}