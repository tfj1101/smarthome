#include "layout.h"
#include "hanzi.h"
#include "bmp.h"
#include "lcd.h"
void title_display(void)
{
	// 显示汉字
	int x = 330;
	hanzi_display(x, 100, 24, 24, hanzi_zhi);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_neng);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_jia);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_ju);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_kong);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_zi);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_xi);
	x += 24;
	sleep(0.5);
	hanzi_display(x, 100, 24, 24, hanzi_tong);
	x += 24;
}

void home_display(void)
{

	lcd_draw_clear(0, 0, 800, 480, 0xffffff);

	title_display();

	// 视频图标
	bmp_display("/home/tfj/bg/10.bmp", 10, 10);
	hanzi_display(30, 103, 16, 16, hanzi_shi);
	hanzi_display(46, 103, 16, 16, hanzi_ping);

	// 相册图标
	bmp_display("/home/tfj/bg/xiangce.bmp", 130, 10);
	hanzi_display(170, 119, 16, 16, hanzi_xiang);
	hanzi_display(186, 119, 16, 16, hanzi_ce);
	// 音乐图
	// bmp_display("/home/tfj/music.bmp", 20, 200);
	bmp_display("/home/tfj/bg/m1.bmp", 40, 200);
	hanzi_display(100, 340, 16, 16, hanzi_yin);
	hanzi_display(116, 340, 16, 16, hanzi_yue);
	// sleep(1.5);

	// 播放按钮
	// bmp_display("/home/tfj/play.bmp", 100, 280);
	// sleep(1.5);

	// 灯泡
	bmp_display("/home/tfj/light_off.bmp", 350, 180);
	// sleep(1.5);

	// 温度
	bmp_display("/home/tfj/tem.bmp", 600, 150);
	// sleep(1.5);
	// 数字
	// digtal_display(670,200,27.5);

	//
	bmp_display("/home/tfj/hum.bmp", 600, 250);
	// sleep(1.5);
	// int_display(700,300,8,16,40);

	bmp_display("/home/tfj/atmos.bmp", 600, 350);
	// sleep(1.5);
	// int_display(720,400,8,16,1200);
	// sleep(1.5);
}