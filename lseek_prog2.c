#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

typedef struct parts{
	int start, num;
}parts;

int main(int argc, char *argv[]){
	int fd, size, fdcopy;
	int lastnum = 0, start = 0, num = 0, i = 0, tempnum = 0;
	int order[10] = {4, 3, 0, 9, 1, 5, 6, 2, 8, 7};
	char *temp;
	char name[128] = "copy";
	int readchars, written;
	
	
	fd = open(argv[1], O_RDONLY);
	fdcopy = open(name, O_CREATE|O_RDWR);
	
	
	if(fd < 0 || fdcopy < 0){
		printf(2, "open failed\n");
		exit();
	}
	
	size = lseek(fd, 0, SEEK_END);
	
	
	num = size / 10; //number of charachters to be copied
	lastnum = num + (size % 10);
	temp = (char *)malloc(lastnum * sizeof(char));
	
	
	
	if(temp == 0){
		printf(2, "Malloc failed\n");
		exit();
	}
	
	memset(temp, '1', lastnum);
	
	for(i = 0; i < 9; i++){
		write(fdcopy, temp, num);
	}
	write(fdcopy, temp, lastnum);
	
	
	//for last piece, copy lastnum number of chars, else copy num number of charachters.
	
	for(i = 0; i < 10; i++){
		
		start = order[i] * num;
		if(order[i] == 9)
			tempnum = lastnum;
		else
			tempnum = num;
			
			
		
		lseek(fd, start, SEEK_SET);
		readchars = read(fd, temp, tempnum);
		
		if(readchars != tempnum){
			printf(2, "Error in read.\n");
			exit();
		}
		
		lseek(fdcopy, start, SEEK_SET);
		written = write(fdcopy, temp, tempnum);
		
		if(written != tempnum){
			printf(2, "Error in write.\n");
			exit();
		}
	}
	
	close(fd);
	close(fdcopy);
	exit();
	
	
}
