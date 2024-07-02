
#include"video.h"
#include"touch.h"
void video_display()
{
	// 可加功能：暂停、播放、上一个、下一个
	system("mplayer ./video/mv.mp4 -framedrop &");
	while (1)
	{
		char is_exit = 0;
		switch (get_direction())
		{
		case UP: // 退出
		case DOWN:
			system("killall mplayer");
			is_exit = 1;
			break;
		case LEFT:
			break;
		case RIGHT:
			break;
		}
		if (is_exit == 1)
			break; // 返回到首页
	}
}