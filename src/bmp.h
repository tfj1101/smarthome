#ifndef __BMP_H__
#define __BMP_H__

/*
    bmp_display: 在开发板屏幕上显示一张bmp图片
    @bmp_file: 要显示的图片文件的名字
    @x0: 在屏幕上的显示位置的x轴坐标
    @y0: 在屏幕上的显示位置的y轴坐标
    返回值:
        无
*/
void bmp_display(const char* bmp_file, int x0, int y0);

#endif 