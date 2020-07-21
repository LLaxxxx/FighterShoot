#include "play.h"

int main()
{
    int error=0;
    error=game_init();
    if(error!=0)return error;

    //初始化完成后，开始进入游戏的主循环，
    error=frame_run();
    if(error!=0) return error;

    //游戏结束后，销毁所占用的资源
    error=game_distory();
    if(error!=0)
        return error;

    return 0;
}
