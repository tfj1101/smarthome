#include"lcd.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int lcdfd = 0; //保存LCD屏幕文件的文件描述符
int *plcd = 0; //保存LCD屏幕映射内存首地址
int lcd_init(void) //初始化LCD屏：打开和映射LCD屏幕文件
{
	/* 打开LCD屏驱动设备文件 */
	lcdfd = open("/dev/fb0",O_RDWR);
	if(-1 == lcdfd)
	{
		perror("open lcd error");
		return -1;
	}

	/* 将LCD屏映射到内存空间 =》Frame Buffer 帧缓冲设备*/
	plcd = (int*)mmap(NULL,800*480*4,	PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(MAP_FAILED == plcd)
	{
		perror("mmap lcd error");
		close(lcdfd);
		return -1;
	}

	return 0;
}

int lcd_uninit(void)//释放LCD屏：接触映射，关闭LCD屏幕文件
{
	/* 收尾：解除映射，关闭屏幕文件 */
	munmap(plcd,800*480*32/8);
	close(lcdfd);
	
	return 0;
}

int lcd_draw_point(int x,int y,int color)	//画点函数，用来将坐标为(x,y)的像素点显示为color色
{
	if(x<0 || x >=800 || y<0 || y>=480)
	{
		printf("指定画点的坐标超出屏幕范围\n");
		return -1;
	}
	
	*(plcd + y*800 + x) = color;

	return 0;
}

int lcd_draw_clear(int x0,int y0,int w,int h,int color)//清屏函数，用来将从(x0,y0)为起点，宽w，高h的矩形区域显示为 color色
{
	int x = 0;
	int y = 0;

	for(x=x0;x<x0+w;x++)
	{
		for(y=y0;y<y0+h;y++)
		{
			lcd_draw_point(x,y, color);
		}
	}

	return 0;
}

int lcd_draw_FourLeafClover(void)//在屏幕上显示一个四叶草（取上下左右四个圆两两的交集）
{
	//中心（400,240)
	//上：（400,40） 下：（400,440）左：（200,240） 右：（600,240）
	int x = 0;
	int y = 0;
	 (0,0,800,480,0xff0000);
	for(y=0;y<480;y++)
	{
		for(x=0;x<800;x++)
		{
			if( (x-400)*(x-400)+(y-40)*(y-40)<=200*200 && (x-200)*(x-200)+(y-240)*(y-240)<=200*200  //上左
			  ||(x-400)*(x-400)+(y-440)*(y-440)<=200*200 && (x-200)*(x-200)+(y-240)*(y-240)<=200*200  //下左
			  ||(x-400)*(x-400)+(y-440)*(y-440)<=200*200 && (x-600)*(x-600)+(y-240)*(y-240)<=200*200  //下右
			  ||(x-400)*(x-400)+(y-40)*(y-40)<=200*200 && (x-600)*(x-600)+(y-240)*(y-240)<=200*200)  //下右
			{
				lcd_draw_point(x,y,0x00ff);
			}
		}
	}
}