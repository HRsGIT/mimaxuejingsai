#include "exeloadview.h"
#include "ui_exeloadview.h"

#include "GlobalVariables.h"

#include <QProcess>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMimeData>
#include <QFileInfo>
#include <QDebug>

exeLoadView::exeLoadView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::exeLoadView)
{
    ui->setupUi(this);

    setUpView();
    ui->animate_view->start();
}

exeLoadView::~exeLoadView()
{
    delete ui;
}

//MARK:- 初始化界面
void exeLoadView::setUpView() {
    // 去窗口边框
    setWindowFlags(Qt::FramelessWindowHint);

    // 背景按钮
    ui->background->setPixmap(QPixmap(GlobalVs::background_2));
    ui->background->setScaledContents(true);

    // 退出按钮
    ui->quit_Btn->setStyleSheet("QWidget{background-color:red; border-radius:8px;}");
    ui->quit_Btn->installEventFilter(this);
    // 最小化按钮
    ui->minimized_Btn->setStyleSheet("QWidget{background-color:orange; border-radius:8px;}");
    ui->minimized_Btn->installEventFilter(this);

    // 界面设置
    ui->exe_recipient->setPixmap(QPixmap(GlobalVs::recipient_Icon));
    ui->exe_recipient->setScaledContents(true);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->exe_name->setPalette(pa);

    // 开始按钮
    ui->start_Btn->setPixmap(QPixmap(GlobalVs::start_btn_1));
    ui->start_Btn->setScaledContents(true);
    ui->start_Btn->installEventFilter(this);

    // 使this和file_recipient可接受拖放操作
    this->installEventFilter(this);
    this->setAcceptDrops(true);
    ui->exe_recipient->installEventFilter(this);
    ui->exe_recipient->setAcceptDrops(true);

    // 设置exe图标动画
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    effect->setOpacity(1);
    ui->exe_recipient->setGraphicsEffect(effect);


    QPropertyAnimation *ani_1 = new QPropertyAnimation(effect,"opacity");
    ani_1->setDuration(1200);
    ani_1->setStartValue(1);
    ani_1->setEndValue(0.9);

    QPropertyAnimation *ani_2 = new QPropertyAnimation(effect,"opacity");
    ani_2->setDuration(800);
    ani_2->setStartValue(0.9);
    ani_2->setEndValue(1);

    QPropertyAnimation *ani_3 = new QPropertyAnimation(effect,"opacity");
    ani_3->setDuration(600);
    ani_3->setStartValue(1);
    ani_3->setEndValue(1);

    exe_animal= new QSequentialAnimationGroup;
    exe_animal->addAnimation(ani_1);
    exe_animal->addAnimation(ani_2);
    exe_animal->addAnimation(ani_3);
    exe_animal->setLoopCount(1);
    connect(exe_animal,&QPropertyAnimation::finished, [=] {
        exe_animal_running = false;
    });
}

// 界面入场动画效果
void exeLoadView::showView(QWidget *previewCopy) {
    this->show();

    QPropertyAnimation *animal1= new QPropertyAnimation(ui->centralwidget, "pos");
    animal1->setDuration(500);
    animal1->setStartValue(QPoint(0,-650));
    animal1->setEndValue(QPoint(0,0));

    QPropertyAnimation *animal2= new QPropertyAnimation(previewCopy, "pos");
    animal2->setDuration(500);
    animal2->setStartValue(QPoint(0,0));
    animal2->setEndValue(QPoint(0,650));

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animal1);
    group->addAnimation(animal2);

    connect(group,SIGNAL(finished()), group, SLOT(deleteLater()));
    connect(group,SIGNAL(finished()), previewCopy, SLOT(deleteLater()));
    connect(animal1,SIGNAL(finished()), animal1, SLOT(deleteLater()));
    connect(animal2,SIGNAL(finished()), animal2, SLOT(deleteLater()));

    animal1->start();
    animal2->start();
}

// 闪动exe图标，提示拖入程序。
void exeLoadView::flashExeIcon() {

//    ui->animate_view->start();

    if(!exe_animal_running) {
        exe_animal->start();
        exe_animal_running=true;
    }
}

//MARK:- 鼠标经过事件（实现关闭，最小化按钮效果）
void exeLoadView::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton)
    {
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void exeLoadView::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons() & Qt::LeftButton)
    {
        move(e->globalPos() - p);
    }
}

bool exeLoadView::eventFilter(QObject *obj, QEvent *event) {

    // 接收到拖拽进入的动作
    if (event->type() == QEvent::DragEnter) {
        QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);

        // 判断拖拽的文件类型
        QString path = dee->mimeData()->urls().first().toLocalFile();
        QFileInfo fileinfo(path);
        if(fileinfo.isExecutable()) {
            dee->acceptProposedAction();
            // 如果文件刚拖拽到主界面，播放提示效果
            if(obj == this) {
                flashExeIcon();
            }
            return true;
        }
    }

    // file_recipient接收到放的操作
    if (event->type() == QEvent::Drop && obj == ui->exe_recipient) {
        QDropEvent *de = dynamic_cast<QDropEvent *>(event);
        QUrl url = de->mimeData()->urls().first();
        QString path = url.toLocalFile();
        QString name = url.fileName();
        qDebug()<<path;
        GlobalINFO::FilePath = path;
        GlobalINFO::FileName = name;

        ui->exe_name->setText(name);
        return true;
    }

    // 左上角关闭/最小化按钮
    if(obj==ui->quit_Btn || obj==ui->minimized_Btn){
        if(QEvent::Enter==event->type()){
            ui->quit_Btn->setIcon(QIcon(GlobalVs::quit_Icon));
            ui->quit_Btn->setIconSize(QSize(8,8));
            ui->minimized_Btn->setIcon(QIcon(GlobalVs::minus_Icon));
            ui->minimized_Btn->setIconSize(QSize(8,8));
        }else if(QEvent::Leave==event->type()){
            ui->quit_Btn->setIcon(QIcon());
            ui->minimized_Btn->setIcon(QIcon());
        }
    }

    // 开始按钮
    if(obj==ui->start_Btn){
        if(QEvent::Enter==event->type()){
            if(GlobalINFO::FilePath=="") {
                flashExeIcon();
                ui->start_Btn->setPixmap(QPixmap(GlobalVs::start_btn_1));
            } else {
                ui->start_Btn->setPixmap(QPixmap(GlobalVs::start_btn_2));
            }
        }else if(QEvent::Leave==event->type()){
            ui->start_Btn->setPixmap(QPixmap(GlobalVs::start_btn_1));
        }
    }
    return QObject::eventFilter(obj,event);
}


//MARK:- 槽函数

// 点击关闭/最小化按钮
void exeLoadView::on_quit_Btn_clicked() {
    close();
}

void exeLoadView::on_minimized_Btn_clicked() {
    showMinimized();
}

// 开始按钮
void exeLoadView::on_start_Btn_clicked() {
    if(GlobalINFO::FilePath=="") {
        flashExeIcon();
        return;
    }

    QProcess *proc = new QProcess;
    proc->start(GlobalINFO::exePath,QStringList(GlobalINFO::FilePath));
    GlobalINFO::exePid = int(proc->pid());

    // 进入主界面
    if(GlobalINFO::loadingView==nullptr) {
        GlobalINFO::loadingView = this;
    }
    if(GlobalINFO::mainView!=nullptr) {
        delete GlobalINFO::mainView;
    }
    GlobalINFO::mainView = new MainWindow;
    GlobalINFO::mainView->move(this->frameGeometry().topLeft());

    QLabel *viewCopy = new QLabel(GlobalINFO::mainView);
    viewCopy->resize(ui->centralwidget->size());
    viewCopy->setPixmap(ui->centralwidget->grab());

    connect(this,&exeLoadView::hideView,GlobalINFO::mainView,&MainWindow::showView);
    hideView(viewCopy);

    this->hide();
}
