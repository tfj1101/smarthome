#include "gy39.h"
#include "serial.h"
#include "hanzi.h"
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



void *gy_39(void *arg)
{
	/*
	 发送的信息：
	  开发板发送给传感器的指令格式：帧头+指令+校验和(8bit)
	  帧头和校验和是用来“验证身份”的
	  指令才是用来表达此次通信的目的
	  各占一个字节，共三个字节
	  帧头：0xa5
	  指令：
		只请求光照： 10000001 -> 0x81
		只请求温湿度气压海拔：10000010 -> 0x82
		两种都请求：10000011 -> 0x83
	  检验和：
		等于帧头加上指令，只保存低8位
	   0xa5 + 0x81  -> 0x26
	*/

	pthread_detach(pthread_self());

	char led_ctrl[2];
	int fd1 = open("/dev/led_drv", O_RDWR);
	if (fd1 < 0)
	{
		printf("open led_drv failed\n");
		return (void *)-1;
	}
	int fd = serial_init(COM3, 9600);
	int m = 2;
	char w_buf[][3] = {{0xa5, 0x81, 0x26}, {0xa5, 0x82, 0x27}, {0xa5, 0x83, 0x28}};
	int Lux = 0, // 光强
		T = 0,	 // 温度
		P = 0,	 // 压强
		Hum = 0, // 湿度
		H = 0;	 // 海拔
	int t, r, ret;
	char r_buf[24];
	while (1)
	{

		t = write(fd, w_buf[m], 3);
		// printf("%d\n", t);
		usleep(1000);
		r = read(fd, r_buf, 24);

		if (r == 9 && r_buf[2] == 0x15)
		{
			Lux = (r_buf[4] << 24 | r_buf[5] << 16 | r_buf[6] << 8 | r_buf[7]) / 100;
		}
		else if (r == 15 && r_buf[2] == 0x45)
		{
			T = (r_buf[4] << 8 | r_buf[5]) / 100;
			P = (r_buf[6] << 24 | r_buf[7] << 16 | r_buf[8] << 8 | r_buf[9]) / 100;
			Hum = (r_buf[10] << 8 | r_buf[11]) / 100;
			H = (r_buf[12] << 8 | r_buf[13]) / 100;
		}
		else if (r == 24)
		{
			Lux = (r_buf[4] << 24 | r_buf[5] << 16 | r_buf[6] << 8 | r_buf[7]) / 100;
			T = (r_buf[13] << 8 | r_buf[14]) / 100;
			P = (r_buf[15] << 24 | r_buf[16] << 16 | r_buf[8] << 8 | r_buf[9]) / 100;
			Hum = (r_buf[10] << 8 | r_buf[11]) / 100;
			H = (r_buf[12] << 8 | r_buf[13]) / 100;
		}
		printf("Lux = %d, T = %d, P = %d, Hum = %d, H = %d\n", Lux, T, P, Hum, H);
		sleep(1);

		if (Lux < 6)
		{
			led_ctrl[1] = 10; // D9
			led_ctrl[0] = 1; // on
			ret = write(fd1, led_ctrl, sizeof(led_ctrl));

			if (ret != 2)
			{
				perror("write");
			}
			sleep(1);
		}
		else
		{
			led_ctrl[1] = 10; // D9
			led_ctrl[0] = 0; // off

			ret = write(fd1, led_ctrl, sizeof(led_ctrl));

			if (ret != 2)
			{

				perror("write");
			}
			sleep(1);
		}
		lcd_draw_clear(670, 200, 32, 16,0xffffff);
		lcd_draw_clear(700, 300, 32, 16,0xffffff);
		digtal_display(670, 200, T);
		int_display(700, 300, 8, 16, Hum);
		sleep(2);
	}

	close(fd);
	// return 0;
}