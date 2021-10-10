#include "type_line.h"
#include "ui_type_line.h"
#include "qpropertyanimation.h"

#include "GlobalVariables.h"

Type_Line::Type_Line(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Type_Line)
{
    ui->setupUi(this);

    setUpGifView();

    // 设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}

Type_Line::~Type_Line()
{
    delete ui;
    delete state_gif;
    delete effect;
    delete animation;
}

// 初始化界面
void Type_Line::setUpView(QString img_path, QString label_name) {
    this->setStyleSheet("QWidget{border-radius:10px;}");
    ui->background->setColor(QColor(84,72,101));
    ui->image->setPixmap(QPixmap(img_path));
    ui->image->setScaledContents(true);
    ui->label->setText(label_name);
    // label字体颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pa);
    // label字体大小
    //QFont ft;
    //ft.setPointSize(10);
    //ui->label->setFont(ft);
}

// 初始化gif播放设置
void Type_Line::setUpGifView() {
    if(state_gif == nullptr) {
        state_gif = new QMovie(GlobalVs::warning_1_gif);
        state_gif->setScaledSize(QSize(20,20));
        ui->stateView->setMovie(state_gif);
    }

    if(effect == nullptr) {
        effect = new QGraphicsOpacityEffect();
        effect->setOpacity(1);
        ui->stateView->setGraphicsEffect(effect);
    }

    if(animation == nullptr) {
        animation = new QPropertyAnimation(effect,"opacity");
        animation->setEasingCurve(QEasingCurve::Linear);
        animation->setDuration(2500);
        animation->setStartValue(1);
        animation->setEndValue(0);
        connect(animation, &QPropertyAnimation::finished, [=] {
            state_gif->stop();
        });
    }
}

// 收到信号
void Type_Line::receiveSignal() {
    effect->setOpacity(1);  // 设置stateView不透明
    state_gif->start();  // 开始播放gif
    animation->start(); // 淡出效果
}

// 被选中状态
void Type_Line::beSelected() {
    ui->background->setStyleSheet("QWidget#background{border: 2px solid black; border-radius:10px;}");
}

// 未被选中状态
void Type_Line::notSelected() {
    ui->background->setStyleSheet("");
    ui->background->setColor(QColor(84,72,101));
}

// 鼠标点击操作
void Type_Line::mousePressEvent(QMouseEvent * ev){
    emit clicked();
}
