#include "animationview.h"
#include "ui_animationview.h"

#include "GlobalVariables.h"

#include <QTimer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>

animationView::animationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::animationView)
{
    ui->setupUi(this);

//    setUpCircle();
}

animationView::~animationView()
{
    delete ui;
}

void animationView::start() {
    if(timer!=nullptr) { return; }
//    hideCircle();

    t = 0;
    timer = new QTimer;
    timer->setInterval(800);
    connect(timer,&QTimer::timeout,this,&animationView::updateView);
    timer->start();
}

void animationView::updateView() {

    // 不会自动停止
//    t++;
//    if(t==6) {
//        timer->stop();
//        timer->deleteLater();
//        showCircle();
//        return;
//    }

    int width = this->geometry().width();

    QLabel *la = new QLabel(this);
    la->setPixmap(QPixmap(GlobalVs::circle_red_png));
    la->setScaledContents(true);
    la->setGeometry(width*0.25,width*0.25,width*0.5,width*0.5);
    la->raise();
    la->show();

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    effect->setOpacity(1);
    la->setGraphicsEffect(effect);

    QPropertyAnimation *animation1 = new QPropertyAnimation(effect,"opacity");
    animation1->setDuration(2500);
    animation1->setEasingCurve(QEasingCurve::Linear);
    animation1->setStartValue(1);
    animation1->setEndValue(0);

    QPropertyAnimation *animation2 = new QPropertyAnimation(la,"geometry");
    animation2->setDuration(2500);
    animation2->setEasingCurve(QEasingCurve::Linear);
    animation2->setStartValue(QRect(width*0.25,width*0.25,width*0.5,width*0.5));
    animation2->setEndValue(QRect(0,0,width,width));

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animation1);
    group->addAnimation(animation2);

    connect(group,&QParallelAnimationGroup::finished,[=] {
        effect->deleteLater();
        animation1->deleteLater();
        animation2->deleteLater();
        group->deleteLater();
        la->deleteLater();
    });

    group->start();
}

void animationView::setUpCircle() {
    int width = this->geometry().width();

    circle = new QLabel(this);
    circle->setGeometry(width*0.1,width*0.1,width*0.8,width*0.8);
    circle->setPixmap(QPixmap(GlobalINFO::FilePath=="" ? GlobalVs::circle_red_png : GlobalVs::circle_blue_png));
    circle->setScaledContents(true);
    circle->raise();
    circle->show();

    circle_effect = new QGraphicsOpacityEffect();
    circle_effect->setOpacity(0.5);
    circle->setGraphicsEffect(circle_effect);
}

void animationView::showCircle() {
    int width = this->geometry().width();
    circle->setGeometry(width*0.1,width*0.1,width*0.8,width*0.8);

    circle->setPixmap(QPixmap(GlobalINFO::FilePath=="" ? GlobalVs::circle_red_png : GlobalVs::circle_blue_png));

    QPropertyAnimation *animation1 = new QPropertyAnimation(circle_effect,"opacity");
    animation1->setDuration(1600);
    animation1->setEasingCurve(QEasingCurve::Linear);
    animation1->setStartValue(0);
    animation1->setEndValue(0.5);
    connect(animation1,&QParallelAnimationGroup::finished,animation1,&QParallelAnimationGroup::deleteLater);

    animation1->start();
}

void animationView::hideCircle() {
    QPropertyAnimation *animation1 = new QPropertyAnimation(circle_effect,"opacity");
    animation1->setDuration(800);
    animation1->setEasingCurve(QEasingCurve::Linear);
    animation1->setStartValue(0.5);
    animation1->setEndValue(0);
    connect(animation1,&QParallelAnimationGroup::finished,animation1,&QParallelAnimationGroup::deleteLater);

    animation1->start();
}
