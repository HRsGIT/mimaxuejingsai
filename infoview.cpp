#include "infoview.h"
#include "ui_infoview.h"

#include "GlobalVariables.h"

#include <QDebug>

InfoView::InfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoView)
{
    ui->setupUi(this);

    setUpView();
    setUpAnimation();
}

InfoView::~InfoView()
{
    delete ui;
}

void InfoView::setUpView() {
    ui->space_line->setStyleSheet("QWidget{background-color: gray;}");

    // label字体颜色
    QPalette pa;
    QFont ft;//改变大小
    ft.setPointSize(20);
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->main_Title->setPalette(pa);
    ui->submain_Title->setPalette(pa);
    ui->API_Title->setPalette(pa);
    ui->v1_mainLabel->setPalette(pa);
    ui->v1_mainLabel->setFont(ft);
    ui->v2_mainLabel->setPalette(pa);
    ui->v2_mainLabel->setFont(ft);
    ui->v3_mainLabel->setPalette(pa);
    QPalette pb;
    pb.setColor(QPalette::WindowText,Qt::lightGray);
   
    ft.setPointSize(40);
    ui->v1_subLabel->setPalette(pb);
    ui->v2_subLabel->setPalette(pb);
    ui->v3_subLabel->setPalette(pb);
    ui->v1_subLabel->setFont(ft);
    ui->v2_subLabel->setFont(ft);
    ui->api_line_1->setPalette(pb);
   // ui->api_line_1->setWordWrap(true);
    ui->api_line_2->setPalette(pb);
    ui->api_line_3->setPalette(pb);
    ui->api_line_4->setPalette(pb);

    // 图标设置
    ui->v1_img->setScaledContents(true);
    ui->v2_img->setScaledContents(true);
    ui->v3_img->setScaledContents(true);

    // 清空界面
    ui->space_line->setHidden(true);
    ui->API_Title->setHidden(true);
    ui->v1_mainLabel->setText("");
    ui->v2_mainLabel->setText("");
    ui->v3_mainLabel->setText("");
    ui->v1_subLabel->setText("");
    ui->v2_subLabel->setText("");
    ui->v3_subLabel->setText("");
    ui->api_line_1->setText("");
    ui->api_line_2->setText("");
    ui->api_line_3->setText("");
    ui->api_line_4->setText("");

}

void InfoView::setUpAnimation() {
    if(effect == nullptr) {
        effect = new QGraphicsOpacityEffect();
        effect->setOpacity(1);
        this->setGraphicsEffect(effect);
    }

    if(appear_animation == nullptr) {
        appear_animation = new QPropertyAnimation(effect,"opacity");
        appear_animation->setEasingCurve(QEasingCurve::Linear);
        appear_animation->setDuration(200);
        appear_animation->setStartValue(0);
        appear_animation->setEndValue(1);
    }

    if(disappear_animation == nullptr) {
        disappear_animation = new QPropertyAnimation(effect,"opacity");
        disappear_animation->setEasingCurve(QEasingCurve::Linear);
        disappear_animation->setDuration(200);
        disappear_animation->setStartValue(1);
        disappear_animation->setEndValue(0);
        connect(disappear_animation, &QPropertyAnimation::finished, [=] {
            changeInfo();
            appear_animation->start();
        });
    }
}

//MARK: -改变info相关
void InfoView::changeInfo(){
    const int t = infoList[0];//infoList[0]是主题和副标题，也是对应的分析结果序号 1,2,3,4是中间那一堆操作,5,6,7,8,9是下边的API信息
    setMainType(GlobalINFO::type[t],GlobalINFO::type_info[t]);//改变主标题和副标题

    const int v_num = infoList[1];
    const int v_t1 = infoList[2];
    const int v_t2 = infoList[3];
    const int v_t3 = infoList[4];
    qDebug() << v_num << v_t1 << v_t2 << v_t3;
    if(t != 2 && t != 11){
        bool dan = 0;
        int tem = 0;//输出“测试文件***性质为”
        int sunl = 1;//sublabel的数量
        if (GlobalINFO::sublabel[t][0] == "1234567" || GlobalINFO::sublabel[t][0] == "1234567.000") {
            tem = 1;//输出不具有该性质
            dan = 1;//为单输出布尔函数
           // ui->v1_subLabel->setHidden(true);
            //sunl = 0;
        }
        if (t == 7) {//平衡性
            if (GlobalINFO::sublabel[t][0] == "0") {
                GlobalINFO::sublabel[t][0] = "不平衡";
            }
            else {
                GlobalINFO::sublabel[t][0] = "平衡";
            }
        }
    QString imgs[3] = {GlobalINFO::v_imgs[t][v_t1],GlobalINFO::v_imgs[t][v_t2],GlobalINFO::v_imgs[t][v_t3]};
    QString main_labels[3] = {GlobalINFO::v_mainLabels[t][tem],GlobalINFO::v_mainLabels[t][tem],GlobalINFO::v_mainLabels[t][tem]};
    QString sub_labels[3] = {GlobalINFO::sublabel[t][0],GlobalINFO::sublabel[t][0],GlobalINFO::sublabel[t][0] };
    setVirusType(sunl, imgs, main_labels, sub_labels,dan);//改变那一堆操作和原因分析 暂时注释掉
   // ui->v1_subLabel->setHidden(false);
    }
    else {
        bool dan = 0;
        int tem = 0;//输出“测试文件***性质为”
        int sunl = 2;//sublabel的数量
        if (GlobalINFO::sublabel[t][0] == "1234567" || GlobalINFO::sublabel[t][0] == "1234567.000") {
            tem = 2;//输出不具有该性质
            sunl = 1;
            dan = 1;//单输出布尔函数
        }
        QString imgs[3] = { GlobalINFO::v_imgs[t][v_t1],GlobalINFO::v_imgs[t][v_t2],GlobalINFO::v_imgs[t][v_t3] };
        QString main_labels[3] = { GlobalINFO::v_mainLabels[t][tem],GlobalINFO::v_mainLabels[t][tem],GlobalINFO::v_mainLabels[t][tem] };
        QString sub_labels[3] = { GlobalINFO::sublabel[t][tem],GlobalINFO::sublabel[t][tem + 1 < 2 ? tem + 1 : 2],GlobalINFO::sublabel[t][0] };
        setVirusType(sunl, imgs, main_labels, sub_labels, dan);//改变那一堆操作和原因分析 暂时注释掉
    }

    const int a_num = infoList[5];
    const int a_t1 = infoList[6];
    const int a_t2 = infoList[7];
    const int a_t3 = infoList[8];
    const int a_t4 = infoList[9];
    QString apis[4] = {GlobalINFO::APIs[t][0],GlobalINFO::APIs[t][0],GlobalINFO::APIs[t][0],GlobalINFO::APIs[t][0]};
    setAPI(a_num,GlobalINFO::ApiString[t]);
    setAPI(1, apis);//改变下边的API信息 暂时注释掉
}


// 改变主类型
void InfoView::setMainType(QString type, QString subTitle) {
    ui->main_Title->setText(type);
    ui->submain_Title->setText(subTitle);
}

// 改变病毒操作类型
void InfoView::setVirusType(int num, QString imgs[], QString main_labels[], QString sub_labels[],bool dan) {
    QLabel *v_img_list[3] = {ui->v1_img,ui->v2_img,ui->v3_img};
    QLabel *v_mainLabel_list[3] = {ui->v1_mainLabel,ui->v2_mainLabel,ui->v3_mainLabel};
    QLabel *v_subLabel_list[3] = {ui->v1_subLabel,ui->v2_subLabel,ui->v3_subLabel};
    if(num>=3) { num=3; }

    for(int i=0;i<num;i++) {
        v_img_list[i]->setPixmap(QPixmap(imgs[i]));
        v_img_list[i]->setHidden(false);
        v_mainLabel_list[i]->setText(main_labels[i]);
        v_mainLabel_list[i]->setHidden(false);
        v_subLabel_list[i]->setText(sub_labels[i]);
        v_subLabel_list[i]->setHidden(false);
    }
    for(int i=num;i<3;i++) {
        v_img_list[i]->setHidden(true);
        v_mainLabel_list[i]->setHidden(true);
        v_subLabel_list[i]->setHidden(true);
    }
    if (dan)v_subLabel_list[0]->setHidden(true);
}

// 改变API函数
void InfoView::setAPI(int num, QString apis[4]) {

    // 如果没有api，则分割线和标题不显示
    ui->space_line->setHidden(num == 0);
    ui->API_Title->setHidden(num == 0);

    QLabel *api_line_list[4] = {ui->api_line_1,ui->api_line_2,ui->api_line_3,ui->api_line_4};
    if(num>=4) { num=4; }

    for(int i=0;i<num;i++) {
        api_line_list[i]->setText(" · "+apis[i]);
        api_line_list[i]->setHidden(false);
    }
    for(int i=num;i<4;i++) {
        api_line_list[i]->setHidden(true);
    }


}


// 对外接口函数，包含淡入淡出动画
void InfoView::resetView(int info[10], bool animate) {//animate默认值为true
    for(int i=0;i<10;i++) {
        this->infoList[i] = info[i];//infoList记录的是要显示的信息   infoList[0]是主题和副标题，1,2,3,4是中间那一堆操作,5,6,7,8,9是下边的API信息
    }
    if(animate) {
        disappear_animation->start();
    } else {
        changeInfo();
    }
}
