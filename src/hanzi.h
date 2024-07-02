#ifndef __HANZI_H__
#define __HANZI_H__

// unsigned char hanzi_2[];

unsigned char dot[16];
unsigned char digtal[10][16];

unsigned char hanzi_zhi[72] ;

unsigned char hanzi_neng[72];

unsigned char hanzi_jia[72];


unsigned char hanzi_ju[72];
unsigned char hanzi_kong[72];

unsigned char hanzi_zi[72];

unsigned char hanzi_xi[72];

unsigned char hanzi_tong[72];

unsigned char hanzi_shi[32];
unsigned char hanzi_ping[32];
unsigned char hanzi_yin[32];
unsigned char hanzi_yue[32];
unsigned char hanzi_xiang[32];
unsigned char hanzi_ce[32];


void hanzi_display(int x0, int y0,int w,  int h,unsigned char data[]);




//在屏幕坐标位置(x0,y0)显示一个整数 num
/*
    int_display: 在屏幕上显示一个整数
    @x0: 屏幕显示区域左上顶点的x轴坐标
    @y0: 屏幕显示区域左上顶点的y轴坐标
    @w:  单个数字(如: 0, 1)的宽度
    @h:  单个数字(如: 0, 1)的高度
    @num: 要显示的整数(如: 235)
    返回值：
        最终显示了多少位数字
*/
int  int_display(int x0, int y0,int w, int h,int num);

//在屏幕坐标位置(x0,y0)显示一个 小数
void digtal_display(int x0, int y0, double num);


#endif


