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
static const QString process_2_gif = ":/gif/loading_1.gif";

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
extern QString cur_exe;
extern QString FilePath;
extern QString FileName;
extern int exePid;

extern exeLoadView *loadingView;
extern MainWindow *mainView;

extern int info[14][10];//14个性质对应的结果

extern QString ApiString[5][4];

extern QString sublabel[14][2];//自己加的
// 常量
const QString exePath = "./S_BOX/Debug/S_BOX.exe";

//type是主标题
const QString type[14] = {"差分均匀度","鲁棒性","(相对)不动点","分支数","透明度","代数免疫","信噪比","平衡性","非线性性","相关免疫","代数次数","全局雪崩","扩散准则","混淆系数"};
//typr_info是副标题
const QString type_info[14] = {"get_delta_uniformity","robustness","fixed_ans_opssite","branch_number","transparence_order","algebraic_immunity","snr","balance","nonlinearit","correlation_immunity","algebraic_degree","GAC","propagation_characteristics","computeKappaCPA"};
//下边的东西暂时没有用到，仅仅改了数组大小防止崩溃
const QString v_imgs[14][10] = {{GlobalVs::v_img1,GlobalVs::v_img2,GlobalVs::v_img3,GlobalVs::v_img4,GlobalVs::v_img5,
                               GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img4,GlobalVs::v_img5,GlobalVs::v_img6,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img10,GlobalVs::v_img11,GlobalVs::v_img12,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                               {GlobalVs::v_img5,GlobalVs::v_img2,GlobalVs::v_img11,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                                {GlobalVs::v_img5,GlobalVs::v_img2,GlobalVs::v_img11,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10},
                                {GlobalVs::v_img5,GlobalVs::v_img2,GlobalVs::v_img11,GlobalVs::v_img4,GlobalVs::v_img5,
                                GlobalVs::v_img6,GlobalVs::v_img7,GlobalVs::v_img8,GlobalVs::v_img9,GlobalVs::v_img10}
                              };
//用于打印计算结果前的提示语句
const QString v_mainLabels[14][3] = {{"测试文件的差分均匀度为","测试文件为单输出布尔函数，不具有该性质"},
                                    {"测试文件的差分鲁棒性为","测试文件为单输出布尔函数，不具有该性质"},
                                    {"测试文件的不动点为","测试文件的相对不动点为","测试文件为单输出布尔函数，不具有该性质"},
                                    {"测试文件分支数为","测试文件为单输出布尔函数，不具有该性质"},
                                    {"测试文件透明度为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件代数免疫度为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件信噪比为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件平衡性为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件非线性度为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件相关免疫度为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件代数次数为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件全局雪崩准则中平方和指标为","测试文件全局雪崩准则中绝对值指标为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件扩散准则次数最高为","测试文件为单输出布尔函数，不具有该性质"},
    {"测试文件混淆系数方差为","测试文件为单输出布尔函数，不具有该性质"},
                                    };
//用于打印计算结果

const QString v_subLabels[14][10] = {{"无","可能出现了堆的重复释放问题。","","","","","","","",""},
                                   {"无","创建了一个socket，可能存在网络操作。","对服务器进行连接。","通过socket发送数据包。","通过socket接收数据包。","socket接收到http协议数据包。","","","",""},
                                   {"无","文件操作涉及到多个文件夹。","文件存在自我复制。","可能修改了可执行代码。","文件信息可能泄露。","可能是有传播性的病毒在感染其它文件。","文件可能被恶意篡改。","","",""},
                                   {"无","出现了一个弹窗操作","","","","","","","",""},
                                   {"无","发生新增注册表且为自启动执行文件。","可能强制隐藏exe文件扩展名。","可能发生了禁用应用的编辑。","可能发生了禁止系统操作的编辑。","","","","",""},
                                    {"无","出现了一个弹窗操作","","","","","","","",""},
                                    {"无","出现了一个弹窗操作","","","","","","","",""}
};
//用于打印可以抵抗什么攻击
const QString APIs[14][1] = {{"差分均匀度用于衡量抵抗差分攻击的能力"},
                            {"差分鲁棒性用于衡量抵抗差分攻击的能力"},
                            {"不动点与相对不动点是布尔函数的重要性质"},
                           {"分支数用于衡量抵抗差分与线性攻击的能力"},
                            {"透明度用于衡量抵抗测信道攻击的能力"},
                           {"代数免疫用于衡量抵抗代数攻击的能力"},
                           {"信噪比用于衡量差分攻击的成功率，以及抵抗测信道攻击的能力"},
    {"平衡性是布尔函数的重要性质"},
    {"非线性性用于衡量抵抗线性攻击的能力"},
    {"相关免疫性用于衡量抵抗相关攻击的能力"},
    {"代数次数用于衡量抵抗高阶差分攻击的能力"},
    {"平方和指标与绝对值指标是衡量布尔函数全局雪崩准则的重要指标"},
    {"扩散准则是衡量布尔函数混淆与扩散能力的重要指标"},
    {"混淆系数用于衡量抵抗测信道攻击的能力"},
                            };

}
