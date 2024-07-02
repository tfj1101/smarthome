#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<math.h>
#include <stdlib.h>
#include"bmp.h"
#include "lcd.h"

/*
    bmp_display: 在开发板屏幕上显示一张bmp图片
    @bmp_file: 要显示的图片文件的名字
    @x0: 在屏幕上的显示位置的x轴坐标
    @y0: 在屏幕上的显示位置的y轴坐标
    返回值:
        无
*/
void bmp_display(const char* bmp_file, int x0, int y0)
{

    int fd ;

    fd = open(bmp_file, O_RDONLY);
    if (fd == -1)
    {
        printf("Sorry, failed to open bmp file %s\n", bmp_file);
        return ;
    }

    int width;
    lseek(fd, 0x12, SEEK_SET);
    read(fd, &width, 4);

    int height;
    lseek(fd, 0x16, SEEK_SET);
    read(fd, &height, 4);

    short depth;
    lseek(fd, 0x1c, SEEK_SET);
    read(fd, &depth, 2);

    if ( !(depth == 24 || depth == 32))
    {
        printf("Sorry, Not Supported!!!\n");
        close(fd);
        return ;
    }

    // printf("%d X %d\n", abs(width), abs(height));


    int valid_bytes_per_line; //每一行有效数据的字节数
    int laizi = 0; //每一行末尾的“赖子”数

    valid_bytes_per_line = abs(width) * (depth / 8) ;
    if (valid_bytes_per_line % 4 != 0)
    {
        laizi = 4 - valid_bytes_per_line % 4 ;
    }

    //total_bytes_per_line一行实际的字节数
    int total_bytes_per_line = valid_bytes_per_line + laizi;

    //total_bytes表示整个像素数组的实际字节数
    int total_bytes = total_bytes_per_line * abs(height);

    unsigned char* piexl =  malloc( total_bytes );

    lseek(fd, 54, SEEK_SET);
    read(fd, piexl, total_bytes );

    // ...把读取到的像素数据 显示在屏幕

    int i = 0;
    unsigned char b, g, r, a = 0;
    int color;
    int x;
    int y;

    
    for (y = 0; y < abs(height); y++)
    {

        //这一行的 第x个像素点
        for (x = 0; x < abs(width) ; x++)
        {

            b = piexl[i++];
            g = piexl[i++];
            r = piexl[i++];
            if (depth == 32)
            {
                a = piexl[i++];
            }
            color = (a << 24) | (r << 16)  | (g << 8) | b;
            lcd_draw_point(x0 + x,  y0 + abs(height) - 1 - y, color);

            
        }
        i += laizi; //跳过“赖子”
    }


    free(piexl);
    close(fd);


    
}
