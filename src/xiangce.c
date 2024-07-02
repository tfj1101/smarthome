#include "bmp.h"
#include "xiangce.h"
#include "touch.h"
#include"bmp.h"



void xiangce_display(void)
{
    int i = 0;
    char *picture[] = {"2", "5", "7", "8"};
    char temp[52] = {0};
    sprintf(temp, "/home/tfj/photos/%s.bmp", picture[i]);
    bmp_display(temp, 0, 0);
    while (1)
    {

        char is_exit = 0;

        switch (get_direction())
        {
        case UP: // 退出
        case DOWN:
            is_exit = 1;
            break;
        case LEFT:
        {
            i++;
            if (i > 3)
            {
                i = 0;
            }
            sprintf(temp, "/home/tfj/photos/%s.bmp", picture[i]);
            bmp_display(temp, 0, 0);
            break;
        }
        case RIGHT:
        {
            i--;
            if (i < 0)
            {
                i = 3;
            }

            sprintf(temp, "/home/tfj/photos/%s.bmp", picture[i]);
            bmp_display(temp, 0, 0);
            break;
        }
        }
        if (is_exit == 1)
            break; // 返回到首页
    }
}