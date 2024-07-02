
#include <stdio.h>
#include <stdlib.h>
#include "touch.h"
#include "lcd.h"
#include "music.h"
#include <pthread.h>

char *music[3] = {"music1.mp3", "Magnum.mp3", "night-sky-wave.mp3"};
int flag_music = 0; // 0 - 暂停  1 - 播放
void music_display(void)
{
	// pthread_detach(pthread_self());
	lcd_draw_clear(0, 0, 800, 480, 0xffffff);
	bmp_display("/home/tfj/bg/m2.bmp", 0, 0);
	bmp_display("/home/tfj/bg/pause1.bmp", 247, 70);
	bmp_display("/home/tfj/bg/exit.bmp", 0, 360);
	int i = 0;
	int x, y;
	char cmd[52] = {0};
	sprintf(cmd, "madplay -Q /home/tfj/music/%s &", music[i]);

	flag_music = 0;
	while (1)
	{

		get_xy(&x, &y);
		// printf("get x,y	\n");
		if (x >= 20 && x < 200 && y > 100 && y < 340)
		{
			// 播放上一首
			// 干掉当前播放的音乐
			system("killall -9 madplay");
			// 导入上一首
			i--;
			if (i < 0)
			{
				i = 2;
			}
			printf("shang yi shou\n");
			sprintf(cmd, "madplay -Q /home/tfj/music/%s &", music[i]);
			system(cmd);
		}
		if (x >= 600 && x < 800 && y > 100 && y < 370)
		{
			// 播放下一曲
			// 干掉当前播放的音乐
			system("killall -9 madplay");
			// 导入上一首
			i++;
			if (i > 2)
			{
				i = 0;
			}
			printf("xia yi shou\n");
			sprintf(cmd, "madplay -Q /home/tfj/music/%s &", music[i]);
			system(cmd);
		}
		// 点击播放按钮
		if (x >= 300 && x <= 500 && y >= 150 && y <= 300)
		{
			// 播放
			if (flag_music == 0)
			{
				flag_music = 1;
				// 播放
				system(cmd);
				// printf("music open\n");
				printf("music bofang\n");
				bmp_display("/home/tfj/bg/play1.bmp", 247, 67);
				// system("killall -CONT madplay");
			}
			else // 暂停
			{
				flag_music = 0;

				// 暂停
				printf("music zanting\n");
				bmp_display("/home/tfj/bg/pause1.bmp", 247, 70);
				system("killall -STOP madplay");
			}
		}
		if (x >= 0 && x <= 100 && y >= 360 && y <= 460)
			break;
	}
}
