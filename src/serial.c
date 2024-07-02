
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include "lcd.h"
#include <stdlib.h>
#include <pthread.h>
#include "beep.h"

// 初始化串口
#include "serial.h"
#include "hanzi.h"

// file:传入的串口文件(端口号)
// peed: 波特率，9600 (默认为: 9600)
int serial_init(char *file, int peed)
{

	// 打开串口文件
	int fd = open(file, O_RDWR);
	if (fd == -1)
	{
		perror("open serial error");
		return -1;
	}

	/*定义串口属性结构体*/
	struct termios myserial;
	memset(&myserial, 0, sizeof(myserial)); // 清零

	/*设置控制模式 本地连接  使能接收*/
	myserial.c_cflag |= (CLOCAL | CREAD);
	myserial.c_cflag &= ~CSIZE;	  // 清空数据位
	myserial.c_cflag &= ~CRTSCTS; // 无硬件控制流
	myserial.c_cflag |= CS8;	  // 数据位 8
	myserial.c_cflag &= ~CSTOPB;  // 停止位 1
	myserial.c_cflag &= ~PARENB;  // 不要校验

	/*设置波特率*/
	switch (peed)
	{
	case 9600:
		cfsetospeed(&myserial, B9600);
		cfsetispeed(&myserial, B9600);
		break;
	case 57600:
		cfsetospeed(&myserial, B57600);
		cfsetispeed(&myserial, B57600);
		break;
	case 115200:
		cfsetospeed(&myserial, B115200);
		cfsetispeed(&myserial, B115200);
		break;
	}

	/*刷新输出队列，清除正接收的数据*/
	tcflush(fd, TCIFLUSH);

	/*更改配置*/
	tcsetattr(fd, TCSANOW, &myserial);

	return fd;
}

// 获取烟雾浓度
void Get_MQ2(void)
{
	pthread_detach(pthread_self());
	// 初始化串口
	int fd_mq2 = serial_init(COM2, 9600);
	if (fd_mq2 == -1)
	{
		perror("get mq2 error");
		return;
	}

	// 开始通信
	while (1)
	{
		// 发送指令
		char cmd[9] = {0xFF, 0x01, 0x86, 0, 0, 0, 0, 0, 0x79};
		write(fd_mq2, cmd, 9);

		// 延时一段时间，给传感器一定反应时间
		usleep(20000);

		// 接收数据
		char buf[9] = {0};
		read(fd_mq2, buf, 9);

		// 判断数据是否无误
		short data = 0; // 保存烟雾浓度值
		if (buf[0] == 0xFF && buf[1] == 0x86)
		{
			data = buf[2] << 8 | buf[3];
		}

		// printf("MQ2 data : %d\n", data);
		lcd_draw_clear(720, 400, 32, 16, 0xffffff);
		int_display(720, 400, 8, 16, data);
		if (data > 200)
		{
			beep_display();
		}

		// 每隔3秒，更新一次烟雾值
		sleep(2);
	}

	close(fd_mq2);
}
