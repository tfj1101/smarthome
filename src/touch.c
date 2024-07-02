#include"touch.h"

void get_xy(int* x,int* y)
{
    int fd_ev = open("/dev/input/event0",O_RDONLY);
    if (fd_ev == -1)
    {
        perror("open error");
        exit(1);
    }

    struct input_event ev;

    while (1)
    {
        int ret = read(fd_ev,&ev,sizeof(ev));
        if (ret<0)
        {
            perror("read event0 error");
            exit(1);
        }

        if (ev.type == EV_ABS && ev.code == ABS_X )
        {
            *x = ev.value*800/1024;
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y )
        {
            *y = ev.value*480/600;
        }
        if (ev.type == EV_KEY && ev.code == BIN_TOUCH && ev.value == 0)
        {
            break;
        }
        
        
    }
    //关闭触摸屏
    close(fd_ev);
}


/*
    获取手指在触摸屏上的滑动方向
        返回滑动的方向(上下左右)1234
*/
int get_direction()
{
    //打开触摸屏
    int fd_ev = open("/dev/input/event0",O_RDONLY);
    if(fd_ev == -1)
    {
        perror("open event0 error");
        exit(1);
    }

    //定义一个触摸事件结构体
    struct input_event ev;
    
    int x0 = -1,y0 = -1;//存储第一个触摸点的坐标
    int x = -1,y = -1;//存储后续的触摸点坐标 

    while(1)
    {
        //获取触摸事件的信息
        int ret = read(fd_ev,&ev,sizeof(ev));

        if(ret == -1)
        {
            perror("read event0 error");
            exit(1);
        }

        //触摸屏事件，code为获取触摸屏横坐标
        if(ev.type == EV_ABS && ev.code == ABS_X)
        {
            if(x0 == -1)//获取第一个触摸点的坐标
                x0 = ev.value;
            else //获取的是后续的触摸点坐标   
                x = ev.value;
        }

        //触摸屏事件，code为获取触摸屏纵坐标
        if(ev.type == EV_ABS && ev.code == ABS_Y)
        {
            if(y0 == -1)//获取第一个触摸点的坐标
                y0 = ev.value;
            else //获取的是后续的触摸点坐标   
                y = ev.value;
        }

        //当手抬起的时候，返回滑动方向
        if(ev.type == EV_KEY && ev.code == BIN_TOUCH && ev.value == 0)
        {
            int x_d = x - x0;//最后一个坐标与第一个坐标之间的距离
            int y_d = y - y0;

            //用距离的绝对值来判断是上下滑动还是左右滑动
            if(abs(x_d) > abs(y_d))//左右滑动
            {
                if(x_d > 100)//滑动距离过短则不进行识别
                {
                    close(fd_ev);
                    return RIGHT;
                }
                else if(x_d < -100)
                {
                    close(fd_ev);
                    return LEFT;
                }
            }
            else//上下滑动
            {
                if(y_d > 100)//滑动距离过短则不进行识别
                {
                    // bmp_display("./light_on.bmp", 0,0);   
                    close(fd_ev);
                    return DOWN;
                }
                else if(y_d < -100)
                {
                    // bmp_display("./music.bmp", 0,0);  
                    close(fd_ev);
                    return UP;
                }
            }

        }
    }

}