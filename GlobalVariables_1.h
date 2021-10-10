#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#endif // GLOBALVARIABLES_H

#include <QString>
#include "mainwindow.h"
#include "exeloadview.h"


// 背景渐变色
namespace GlobalVs  {
const QString background_left = ":/png/background_left.png";
const QString background_right = ":/png/background_right.png";

const QString background_1 = ":/png/background_1.png";
const QString background_2 = ":/png/background_2.png";
const QString background_3 = ":/png/background_3.png";
const QString background_4 = ":/png/background_4.png";


// 删除最小化图标
const QString quit_Icon = ":/png/close.png";
const QString minus_Icon = ":/png/minus.png";


// 左侧状态栏小图标
const QString net_Icon = ":/png/world-wide-web.png";
const QString heap_Icon = ":/png/database-2.png";
const QString file_Icon = ":/png/folder-2.png";
const QString memory_Icon = ":/png/hardware-4.png";
const QString register_Icon = ":/png/registry.png";


// 右侧大图标
const QString big_net_Icon = ":/png/net_big.png";
const QString big_heap_Icon = ":/png/heap_big.png";
const QString big_file_Icon = ":/png/file_big.png";
const QString big_memory_Icon = ":/png/memory_big.png";
const QString big_register_Icon = ":/png/register_big.png";

// 加载界面动画图片
const QString circle_red_png = ":/png/circle_red.png";
const QString circle_blue_png = ":/png/circle_blue.png";

// 程序运行gif
const QString process_1_png = ":/png/process.png";
const QString process_1_gif = ":/gif/process_1.gif";
const QString process_2_gif = ":/gif/process_2.gif";

// 状态提醒gif
const QString warning_1_gif = ":/gif/wanring_1.gif";
const QString warning_2_gif = ":/gif/wanring_2.gif";

// 加载界面图标
const QString recipient_Icon = ":/png/recipient_1.png";

// 开始/结束按钮图标
const QString start_btn_1 = ":/png/start_btn_1.png";
const QString start_btn_2 = ":/png/start_btn_2.png";
const QString end_btn_1 = ":/png/end_btn_1.png";
const QString end_btn_2 = ":/png/end_btn_2.png";

// info界面小图标
const QString v_img1 = ":/png/v_img1.png";
const QString v_img2 = ":/png/v_img2.png";
const QString v_img3 = ":/png/v_img3.png";
const QString v_img4 = ":/png/v_img4.png";
const QString v_img5 = ":/png/v_img5.png";
const QString v_img6 = ":/png/v_img6.png";
const QString v_img7 = ":/png/v_img7.png";
const QString v_img8 = ":/png/v_img8.png";
const QString v_img9 = ":/png/v_img9.png";
const QString v_img10 = ":/png/v_img10.png";
const QString v_img11 = ":/png/v_img11.png";
const QString v_img12 = ":/png/v_img12.png";
}


namespace GlobalINFO  {

// 变量
extern QString FilePath;
extern QString FileName;
extern int exePid;

extern exeLoadView *loadingView;
extern MainWindow *mainView;

extern int info[5][10];

extern QString ApiString[5][4];

// 常量
const QString exePath = "../InjectDll/Debug/TestConsole.exe";

const QString type[5] = {"堆","网络","文件","弹窗","注册表"};
const QString type_info[5] = {"堆异常情况监测与关联分析","网络异常情况监测与关联分析","文件异常情况监测与关联分析","弹窗异常情况监测与关联分析","注册表异常情况监测与关联分析"};

const QString v_imgs[5][10] = {{GlobalVs::v_img1,GlobalVs::v_img2,GlobalVs::v_img3,GlobalVs::v_img4,GlobalVs::v_img5,
                               GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img4,GlobalVs::v_img5,GlobalVs::v_img6,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img10,GlobalVs::v_img11,GlobalVs::v_img12,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img5,GlobalVs::v_img2,GlobalVs::v_img11,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                              };
const QString v_mainLabels[5][10] = {{"无异常","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作"},
                                    {"无异常","操作","操作","操作","操作","操作","操作","操作","操作","操作"},
                                    {"无异常","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作"},
                                    {"无异常","操作","操作","操作","操作","操作","操作","操作","操作","操作"},
                                    {"无异常","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作","异常操作"}
                                    };
const QString v_subLabels[5][10] = {{"无","可能出现了堆的重复释放问题。","","","","","","","",""},
                                   {"无","创建了一个socket，可能存在网络操作。","对服务器进行连接。","通过socket发送数据包。","通过socket接收数据包。","socket接收到http协议数据包。","","","",""},
                                   {"无","文件操作涉及到多个文件夹。","文件存在自我复制。","可能修改了可执行代码。","文件信息可能泄露。","可能是有传播性的病毒在感染其它文件。","文件可能被恶意篡改。","","",""},
                                   {"无","出现了一个弹窗操作","","","","","","","",""},
                                   {"无","发生新增注册表且为自启动执行文件。","可能强制隐藏exe文件扩展名。","可能发生了禁用应用的编辑。","可能发生了禁止系统操作的编辑。","","","","",""}
                                   };

const QString APIs[5][20] = {{"","HeapCreate","HeapDestroy","HeapAlloc","HeapFree","","","","","","","","","","","","","","",""},
                            {"","socket","connect","send","recv","","","","","","","","","","","","","","",""},
                            {"","CreateFile","CloseHandle","ReadFile","WriteFile","DeleteFile","CopyFile","findfirstfile","findnextfile","CreateFileMappingA","MapViewOfFile","LoadLibraryA","SetFilePointer","CreateFileA","CreateFileW","","","","",""},
                            {"","MessageBoxA","MessageBoxW","","","","","","","","","","","","","","","","",""},
                            {"","RegCreateKeyEx","RegOpenKeyEx","RegSetValueExW","RegCloseKey","RegQueryValueEx","","","","","","","","","","","","","",""}
                            };

}
