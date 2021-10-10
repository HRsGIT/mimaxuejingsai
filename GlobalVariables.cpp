#include "GlobalVariables.h"

namespace GlobalINFO {
QString FilePath = "";
QString FileName = "";
QString cur_exe = "请将待测试S盒拖至此处";
int exePid = 0;

exeLoadView *loadingView = nullptr;
MainWindow *mainView = nullptr;

int info[14][10] = {{0,0,0,1,2,0,0,1,2,3},
                   {1,0,0,1,2,0,0,1,2,3},
                   {2,0,0,1,2,0,0,1,2,3},
                   {3,0,0,1,2,0,0,1,2,3},
                   {4,0,0,1,2,0,0,1,2,3},
                   {5,0,0,1,2,0,0,1,2,3},
                   {6,0,0,1,2,0,0,1,2,3},
    {7,0,0,1,2,0,0,1,2,3},
    {8,0,0,1,2,0,0,1,2,3},
{9,0,0,1,2,0,0,1,2,3},
{10,0,0,1,2,0,0,1,2,3},
{11,0,0,1,2,0,0,1,2,3},
{12,0,0,1,2,0,0,1,2,3},
{13,0,0,1,2,0,0,1,2,3}
};
QString sublabel[14][2] = { "-1" };//有的性质可能需要两个位置
QString ApiString[5][4] = {};
}
