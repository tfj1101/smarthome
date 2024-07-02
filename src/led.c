#include "led.h"
#include "touch.h"
#include <pthread.h>

void open_led(int on, int n)
{
    int fd = open("/dev/led_drv", O_RDWR);
    char cmd_on[2] = {1, 0};
    char cmd_off[2] = {0, 0};
    if (on == 1)
    {
        cmd_on[1] = n;
        write(fd, cmd_on, 2);
    }
    else
    {
        cmd_off[1] = n;
        write(fd, cmd_off, 2);
    }

    close(fd);
}

void led_display()
{

    // pthread_detach(pthread_self());
    // int x, y;
    open_led(0, 9);
    open_led(0, 8);
    int x, y;
    int on_8 = 0;
    int on_9 = 0;
    bmp_display("/home/tfj/bg/5.bmp", 0, 0);
    while (1)
    {
        get_xy(&x, &y);
        // printf("x = %d,y = %d", x, y);
        if (x >= 97 && x <= 220 && y >= 160 && y <= 300)
        {
            on_8 += 1;
            // lcd_draw_clear(0, 0, 800, 480, 0xffffff);
            bmp_display("/home/tfj/bg/5.bmp", 0, 0);
            if (on_8 % 2 != 0)
                open_led(1, 8);
            else
                open_led(0, 8);
        }
        else if (x >= 330 && x <= 460 && y >= 150 && y <= 280)
        {
            // 亮led9
            on_9 += 1;
            if (on_9 % 2 != 0)
                open_led(1, 9);
            else
                open_led(0, 9);
        }
        else if (x >= 620 && x <= 690 && y >= 179 && y <= 280)
        {
            open_led(0, 9);
            open_led(0, 8);
            open_led(0, 10);
            break;
        }

        // 关灯     flag = 0;
    }
}
