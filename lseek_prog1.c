#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

#define MAXLEN 512

int
main(int argc, char *argv[]){
	
	//printf(1, "argc is %d\n", argc);
	int len = atoi(argv[3]), readchars = 0;
	char buf[MAXLEN];	
	int fd = open(argv[1], O_RDONLY);
	
	if(len > MAXLEN - 1){
		printf(2, "Len is too large. This program can handle upto %d charachters\n", MAXLEN - 1);
		exit();
	}
	
	if (fd < 0) {
		printf(2, "open failed\n");
		exit();
	}
	
	if(lseek(fd, atoi(argv[2]), SEEK_SET) == -1){
		printf(2, "lseek failed\n");
		exit();
	}
	
	readchars = read(fd, buf, atoi(argv[3]));
	buf[readchars] = '\0';
	argv[4][len] = '\0';
	
	
	if(strcmp(buf, argv[4]) == 0)
		printf(1, "The strings are the same\n");
	else
		printf(1, "The strings are different\n");
	
	close(fd);
	exit();
	
	
}
