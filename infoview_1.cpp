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
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->main_Title->setPalette(pa);
    ui->submain_Title->setPalette(pa);
    ui->API_Title->setPalette(pa);
    ui->v1_mainLabel->setPalette(pa);
    ui->v2_mainLabel->setPalette(pa);
    ui->v3_mainLabel->setPalette(pa);
    QPalette pb;
    pb.setColor(QPalette::WindowText,Qt::lightGray);
    ui->v1_subLabel->setPalette(pb);
    ui->v2_subLabel->setPalette(pb);
    ui->v3_subLabel->setPalette(pb);
    ui->api_line_1->setPalette(pb);
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
    const int t = infoList[0];
    setMainType(GlobalINFO::type[t],GlobalINFO::type_info[t]);

    const int v_num = infoList[1];
    const int v_t1 = infoList[2];
    const int v_t2 = infoList[3];
    const int v_t3 = infoList[4];
    qDebug() << v_num << v_t1 << v_t2 << v_t3;
    QString imgs[3] = {GlobalINFO::v_imgs[t][v_t1],GlobalINFO::v_imgs[t][v_t2],GlobalINFO::v_imgs[t][v_t3]};
    QString main_labels[3] = {GlobalINFO::v_mainLabels[t][v_t1],GlobalINFO::v_mainLabels[t][v_t2],GlobalINFO::v_mainLabels[t][v_t3]};
    QString sub_labels[3] = {GlobalINFO::v_subLabels[t][v_t1],GlobalINFO::v_subLabels[t][v_t2],GlobalINFO::v_subLabels[t][v_t3]};
    setVirusType(v_num, imgs, main_labels, sub_labels);

    const int a_num = infoList[5];
    const int a_t1 = infoList[6];
    const int a_t2 = infoList[7];
    const int a_t3 = infoList[8];
    const int a_t4 = infoList[9];
    QString apis[4] = {GlobalINFO::APIs[t][a_t1],GlobalINFO::APIs[t][a_t2],GlobalINFO::APIs[t][a_t3],GlobalINFO::APIs[t][a_t4]};
    //setAPI(a_num,GlobalINFO::ApiString[t]);
    setAPI(a_num, apis);
}


// 改变主类型
void InfoView::setMainType(QString type, QString subTitle) {
    ui->main_Title->setText(type);
    ui->submain_Title->setText(subTitle);
}

// 改变病毒操作类型
void InfoView::setVirusType(int num, QString imgs[], QString main_labels[], QString sub_labels[]) {
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
void InfoView::resetView(int info[10], bool animate) {
    for(int i=0;i<10;i++) {
        this->infoList[i] = info[i];
    }
    if(animate) {
        disappear_animation->start();
    } else {
        changeInfo();
    }
}
