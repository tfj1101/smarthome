#include "lcd.h"
#include "bmp.h"
#include "hanzi.h"
#include "layout.h"
#include <unistd.h>
#include "music.h"
#include "led.h"
#include "touch.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include "gy39.h"
#include "beep.h"
#include "video.h"
#include "xiangce.h"
#include "serial.h"

int main()
{

	pthread_t pid1, pid2, pid3, pid4;
	lcd_init();
	lcd_draw_clear(0, 0, 800, 480, 0xffffff);
	beep_display();
	// 测试代码
	//  open_led();
	//  beep_display();
	//  Get_MQ2();

	// pthread_mutex_init(mutex,NULL);

	//创建两个线程
	pthread_create(&pid3, NULL, (void *)Get_MQ2, NULL);
	pthread_create(&pid4, NULL, (void *)gy_39, NULL);
	// pthread_create(&pid2, NULL, (void *)music_display, NULL);
	while (1)
	{
		//主界面函数
		home_display();

		int i = 0;
		char cmd[52] = {0};
		int x, y;
		//获取触摸板的坐标
		get_xy(&x, &y);
		if (x >= 40 && x <= 210 && y >= 200 && y <= 340)
		{
			music_display();
		}
		else if (x >= 350 && x <= 494 && y >= 180 && y <= 420) // led灯
		{
			// pthread_create(&pid1, NULL, (void *)led_display, NULL);
			led_display();
		}
		else if (x >= 10 && x <= 108 && y >= 10 && y <= 103) // 视频播放
		{
			video_display();
		}
		else if (x >= 130 && x <= 280 && y >= 10 && y <= 120)
		{
			xiangce_display();
		}
		// pthread_join(pid1, NULL);
		// pthread_join(pid2, NULL);
		// pthread_join(pid3, NULL);
		// pthread_join(pid4, NULL);
	}
	lcd_draw_clear(0, 0, 800, 480, 0xffffff);
	lcd_uninit();
	return 0;
}
