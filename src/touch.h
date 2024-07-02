#ifndef __TOUCH_H__
#define __TOUCH_H__

#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include "lcd.h"
#include "bmp.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define BIN_TOUCH 0x14a //触摸屏按键

/*
    (x,y):保存获取到的触摸点坐标
*/

void get_xy(int *x,int *y);

/*
    获取手指在触摸屏上的滑动方向
        返回滑动的方向(上下左右)1234
*/
int get_direction();

#endif 