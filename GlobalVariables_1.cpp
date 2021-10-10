#include "GlobalVariables.h"

namespace GlobalINFO {
QString FilePath = "";
QString FileName = "";

int exePid = 0;

exeLoadView *loadingView = nullptr;
MainWindow *mainView = nullptr;

int info[5][10] = {{0,0,0,1,2,0,0,1,2,3},
                   {1,0,0,1,2,0,0,1,2,3},
                   {2,0,0,1,2,0,0,1,2,3},
                   {3,0,0,1,2,0,0,1,2,3},
                   {4,0,0,1,2,0,0,1,2,3}};

QString ApiString[5][4] = {};
}
