#ifndef __LCD_H__
#define __LCD_H__



int lcd_init(void); //初始化LCD屏：打开和映射LCD屏幕文件
int lcd_uninit(void);//释放LCD屏：接触映射，关闭LCD屏幕文件
int lcd_draw_point(int x,int y,int color);	//画点函数，用来将坐标为(x,y)的像素点显示为color色
int lcd_draw_FourLeafClover(void);//在屏幕上显示一个四叶草（取上下左右四个圆两两的交集）
int lcd_draw_clear(int x0,int y0,int w,int h,int color);//清屏函数，用来将从(x0,y0)为起点，宽w，高h的矩形区域显示为 color色
#endif