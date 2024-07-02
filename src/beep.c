
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include"beep.h"

int beep_display()
{
	//1.打开蜂鸣器 
	int fd = open("/dev/pwm", O_RDWR);
	if(fd == -1)
	{
		perror("open pwm error");
		return -1;
	}
	
	//2.控制蜂鸣器状态 
	int i = 5;
	while(i--)
	{
		char cmd = 1;
		//响
		write(fd, &cmd, 1); 
		sleep(1);
		cmd = 0;
		write(fd, &cmd, 1);
		sleep(1);
	}
	
	close(fd);
}









