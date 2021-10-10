#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GlobalVariables.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMouseEvent>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setUpSocket();
    setUpView();
    setUpType_List();
}

MainWindow::~MainWindow() {
    delete ui;
    delete tcpServer;
    //delete tcpSocket;
}

//MARK:- 初始化界面
void MainWindow::setUpView() {
    //去窗口边框
    setWindowFlags(Qt::FramelessWindowHint);

    // 背景图片
    ui->background_left->setPixmap(QPixmap(GlobalVs::background_left));
    ui->background_left->setScaledContents(true);
    ui->background_right->setPixmap(QPixmap(GlobalVs::background_right));
    ui->background_right->setScaledContents(true);

    // 退出按钮
    ui->quit_Btn->setStyleSheet("QWidget{background-color:red; border-radius:8px;}");
    ui->quit_Btn->installEventFilter(this);
    // 最小化按钮
    ui->minimized_Btn->setStyleSheet("QWidget{background-color:orange; border-radius:8px;}");
    ui->minimized_Btn->installEventFilter(this);

    // 程序名称
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    ui->exe_name->setPalette(pa);
    ui->exe_name->setText(GlobalINFO::FileName);
    // 名称过长显示省略号
    QFontMetrics metrics(ui->exe_name->font());
    if (metrics.width(GlobalINFO::FileName) > ui->exe_name->width()) {
       QString str = QFontMetrics(ui->exe_name->font()).elidedText(GlobalINFO::FileName, Qt::ElideRight, ui->exe_name->width());
       ui->exe_name->setText(str);
    }

    // 检测gif
    QMovie *process_gif = new QMovie(GlobalVs::process_1_gif);
    process_gif->setScaledSize(QSize(80,80));
    ui->process_view->setMovie(process_gif);
    process_gif->start();

    // 左边选择栏
    ui->robustness->setUpView(GlobalVs::net_Icon,"差分鲁棒性");//这里是设置左边选择按钮的地方
    ui->delta_uniform->setUpView(GlobalVs::heap_Icon,"差分均匀度");
    ui->fixed_ans_opssite->setUpView(GlobalVs::file_Icon,"(相对)不动点");
    ui->branch_number->setUpView(GlobalVs::memory_Icon,"分支数");
    ui->transparence_order->setUpView(GlobalVs::register_Icon,"透明度");
    ui->algebraic_immunity->setUpView(GlobalVs::register_Icon, "代数免疫");
    ui->balance->setUpView(GlobalVs::net_Icon, "平衡性");
    ui->nonlinearity->setUpView(GlobalVs::file_Icon, "非线性性");
    ui->correlation_immunity->setUpView(GlobalVs::file_Icon, "相关免疫");
    ui->get_snr_dpa->setUpView(GlobalVs::file_Icon, "信噪比");
    ui->algebraic_degree->setUpView(GlobalVs::file_Icon, "代数次数");
    ui->GAC->setUpView(GlobalVs::file_Icon, "全局雪崩准则");
    ui->propagation_characteristics->setUpView(GlobalVs::file_Icon, "扩散准则");
    ui->computeKappaCPA->setUpView(GlobalVs::file_Icon, "混淆系数");
    // 右侧大图标
    ui->big_icon->setPixmap(QPixmap(GlobalVs::big_memory_Icon));
    ui->big_icon->setScaledContents(true);

    // 结束按钮
    ui->back_Btn->setPixmap(QPixmap(GlobalVs::end_btn_1));
    ui->back_Btn->setScaledContents(true);
    ui->back_Btn->installEventFilter(this);
}

void MainWindow::setUpType_List() {
    type_List[0] = ui->delta_uniform;
    type_List[1] = ui->robustness;
    type_List[2] = ui->fixed_ans_opssite;
    type_List[3] = ui->branch_number;
    type_List[4] = ui->transparence_order;
    type_List[5] = ui->algebraic_immunity;
    type_List[6] = ui->get_snr_dpa;
    type_List[7] = ui->balance;
    type_List[8] = ui->nonlinearity;
    type_List[9] = ui->correlation_immunity;
    type_List[10] = ui->algebraic_degree;
    type_List[11] = ui->GAC;
    type_List[12] = ui->propagation_characteristics;
    type_List[13] = ui->computeKappaCPA;

}

//MARK:- 窗口移动
void MainWindow::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton && !(e->pos().x() < 320 && e->pos().y() > 50)) {
        canMove = true;
        p = e->globalPos() - this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if(canMove && e->buttons() && Qt::LeftButton) {
        move(e->globalPos() - p);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * e) {
    canMove = false;
};


//MARK:- 鼠标经过事件（实现关闭，最小化按钮效果）
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
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

    // 结束按钮
    if(obj==ui->back_Btn){
        if(QEvent::Enter==event->type()){
            ui->back_Btn->setPixmap(QPixmap(GlobalVs::end_btn_2));
        }else if(QEvent::Leave==event->type()){
            ui->back_Btn->setPixmap(QPixmap(GlobalVs::end_btn_1));
        }
    }
    return QObject::eventFilter(obj,event);
}

void MainWindow::showView(QWidget *previewCopy) {
    this->show();

    QPropertyAnimation *animal1= new QPropertyAnimation(ui->centralwidget, "pos");
    animal1->setDuration(500);
    animal1->setStartValue(QPoint(0,650));
    animal1->setEndValue(QPoint(0,0));

    QPropertyAnimation *animal2= new QPropertyAnimation(previewCopy, "pos");
    animal2->setDuration(500);
    animal2->setStartValue(QPoint(0,0));
    animal2->setEndValue(QPoint(0,-650));

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

//MARK:- 右边图标移动效果
void MainWindow::changeBigIcon(QString icon_name) {
    // 创建一个动画对象
    ui->big_icon->setPixmap(icon_name);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->big_icon, "pos");
    animation->setDuration(300);  // 设置动画持续时长
    animation->setStartValue(QPoint(1050, 215));  // 设置动画开始位置
    animation->setEndValue(QPoint(800, 215));  // 设置动画结束位置
    animation->setLoopCount(1);  // 设置循环次数：-1为无限次
    animation->start();  // 开始动画
}

//MARK:- 槽函数

// 点击关闭/最小化按钮
void MainWindow::on_quit_Btn_clicked() {
    close();
}

void MainWindow::on_minimized_Btn_clicked() {
    showMinimized();
}

// 点击左侧按钮
void MainWindow::on_delta_uniform_clicked() {
    qDebug()<<"delta_uniform";

    ui->info_view->resetView(GlobalINFO::info[0]);//info是要显示的东西序列
    if(selected_Type == "delta_uniform") { return; }
    selected_Type = "delta_uniform";

    for(auto l : type_List) { l->notSelected(); }//按钮被选中和没有被选中显示不一样 这里是为了控制显示
    ui->delta_uniform->beSelected();
    changeBigIcon(GlobalVs::big_heap_Icon);
}

void MainWindow::on_robustness_clicked() {
    qDebug()<<"robustness";

    ui->info_view->resetView(GlobalINFO::info[1]);
    if(selected_Type == "robustness") { return; }
    selected_Type = "robustness";

    for(auto l : type_List) { l->notSelected(); }
    ui->robustness->beSelected();
    changeBigIcon(GlobalVs::big_net_Icon);
}

void MainWindow::on_fixed_ans_opssite_clicked() {
    qDebug()<<"fixed_ans_opssite";

    ui->info_view->resetView(GlobalINFO::info[2]);
    if(selected_Type == "fixed_ans_opssite") { return; }
    selected_Type = "fixed_ans_opssite";

    for(auto l : type_List) { l->notSelected(); }
    ui->fixed_ans_opssite->beSelected();
    changeBigIcon(GlobalVs::big_file_Icon);
}

void MainWindow::on_branch_number_clicked() {
    qDebug()<<"branch_number";

    ui->info_view->resetView(GlobalINFO::info[3]);
    if(selected_Type == "branch_number") { return; }
    selected_Type = "branch_number";

    for(auto l : type_List) { l->notSelected(); }
    ui->branch_number->beSelected();
    changeBigIcon(GlobalVs::big_memory_Icon);
}
void MainWindow::on_transparence_order_clicked() {
    qDebug()<<"transparence_order";

    ui->info_view->resetView(GlobalINFO::info[4]);
    if(selected_Type == "transparence_order") { return; }
    selected_Type = "transparence_order";

    for(auto l : type_List) { l->notSelected(); }
    ui->transparence_order->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}
void MainWindow::on_balance_clicked() {
    qDebug() << "balance";

    ui->info_view->resetView(GlobalINFO::info[7]);
    if (selected_Type == "balance") { return; }
    selected_Type = "balance";

    for (auto l : type_List) { l->notSelected(); }
    ui->balance->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_nonlinearity_clicked() {
    qDebug() << "nonlinearity";

    ui->info_view->resetView(GlobalINFO::info[8]);
    if (selected_Type == "nonlinearity") { return; }
    selected_Type = "nonlinearity";

    for (auto l : type_List) { l->notSelected(); }
    ui->nonlinearity->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_correlation_immunity_clicked() {
    qDebug() << "correlation_immunity";

    ui->info_view->resetView(GlobalINFO::info[9]);
    if (selected_Type == "correlation_immunity") { return; }
    selected_Type = "correlation_immunity";

    for (auto l : type_List) { l->notSelected(); }
    ui->correlation_immunity->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_algebraic_immunity_clicked() {
    qDebug() << "algebraic_immunity";

    ui->info_view->resetView(GlobalINFO::info[5]);
    if (selected_Type == "algebraic_immunity") { return; }
    selected_Type = "algebraic_immunity";

    for (auto l : type_List) { l->notSelected(); }
    ui->algebraic_immunity->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_get_snr_dpa_clicked() {
    qDebug() << "get_snr_dpa";

    ui->info_view->resetView(GlobalINFO::info[6]);
    if (selected_Type == "get_snr_dpa") { return; }
    selected_Type = "get_snr_dpa";

    for (auto l : type_List) { l->notSelected(); }
    ui->get_snr_dpa->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_algebraic_degree_clicked() {
    qDebug() << "algebraic_degree";

    ui->info_view->resetView(GlobalINFO::info[10]);
    if (selected_Type == "algebraic_degree") { return; }
    selected_Type = "algebraic_degree";

    for (auto l : type_List) { l->notSelected(); }
    ui->algebraic_degree->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_GAC_clicked() {
    qDebug() << "GAC";

    ui->info_view->resetView(GlobalINFO::info[11]);
    if (selected_Type == "GAC") { return; }
    selected_Type = "GAC";

    for (auto l : type_List) { l->notSelected(); }
    ui->GAC->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_propagation_characteristics_clicked() {
    qDebug() << "propagation_characteristics";

    ui->info_view->resetView(GlobalINFO::info[12]);
    if (selected_Type == "propagation_characteristics") { return; }
    selected_Type = "propagation_characteristics";

    for (auto l : type_List) { l->notSelected(); }
    ui->propagation_characteristics->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

void MainWindow::on_computeKappaCPA_clicked() {
    qDebug() << "computeKappaCPA";

    ui->info_view->resetView(GlobalINFO::info[13]);
    if (selected_Type == "computeKappaCPA") { return; }
    selected_Type = "computeKappaCPA";

    for (auto l : type_List) { l->notSelected(); }
    ui->computeKappaCPA->beSelected();
    changeBigIcon(GlobalVs::big_register_Icon);
}

//MARK:- 鼠标经过事件（实现关闭，最小化按钮效果）
void MainWindow::on_back_Btn_clicked()
{
    //TODO: -退出调用的程序


    // 回到加载界面
    //if(GlobalINFO::loadingView!=nullptr) {
    //    delete GlobalINFO::loadingView;
    //}
    if(GlobalINFO::mainView==nullptr) {
        GlobalINFO::mainView = this;
    }
    GlobalINFO::loadingView = new exeLoadView;
    GlobalINFO::loadingView->move(this->frameGeometry().topLeft());

    QLabel *viewCopy = new QLabel(GlobalINFO::loadingView);
    viewCopy->resize(ui->centralwidget->size());
    viewCopy->setPixmap(ui->centralwidget->grab());

    connect(this,&MainWindow::hideView,GlobalINFO::loadingView,&exeLoadView::showView);

    hideView(viewCopy);

    this->hide();
}


//MARK: -网络监听获取info
void MainWindow::setUpSocket() {
    tcpServer = new QTcpServer();
    tcpServer->listen(QHostAddress("127.0.0.1"), 9999);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void MainWindow::acceptConnection() {
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
    qDebug()<<"connect";
}

void MainWindow::readClient() {//接收信息
    QString str = tcpSocket->readAll();
    qDebug()<<str;
    QStringList strList = str.split(" ");
    int i = 0, j = 0;
    for (i = 0; i < 2; ++i, ++j) {
       // GlobalINFO::v_subLabels[i][0] = strList[i];
        GlobalINFO::sublabel[j][0] = strList[i];
    }
    GlobalINFO::sublabel[j][0] = strList[i++];
    GlobalINFO::sublabel[j++][1] = strList[i++];
    for (i; i < 12; ++i, ++j) {
        GlobalINFO::sublabel[j][0] = strList[i];
    }
    GlobalINFO::sublabel[j][0] = strList[i++];
    GlobalINFO::sublabel[j++][1] = strList[i++];
    for (i; i < 16; ++i, ++j) {
        GlobalINFO::sublabel[j][0] = strList[i];
    }
    //parsing_Json(str);//也许我们最后不需要json文件
}

void MainWindow::parsing_Json(QString str) {
    QJsonParseError err_rpt;
    QJsonDocument  root_Doc = QJsonDocument::fromJson(str.toUtf8(), &err_rpt); // 字符串格式化为JSON

    if(err_rpt.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON格式错误";
        return;
    }
    else    // JSON格式正确
    {
        QJsonObject reader = root_Doc.object();
        int type = reader.value("typ").toInt();
        //qDebug() << type;
        int num1 = reader.value("num1").toInt();
        int num2 = reader.value("num2").toInt();
        //qDebug() << num1 << num2;
        int u1 = reader["unu"].toObject()["u1"].toInt();//异常1
        int u2 = reader["unu"].toObject()["u2"].toInt();//异常2
        int u3 = reader["unu"].toObject()["u3"].toInt();//异常3
        //qDebug() << u1 << u2 << u3;
        //int api_1 = reader["api"].toArray().at(0)["n1"].toInt();//api1名称
        //int api_2 = reader["api"].toArray().at(1)["n2"].toInt();
        //int api_3 = reader["api"].toArray().at(2)["n3"].toInt();
        //int api_4 = reader["api"].toArray().at(3)["n4"].toInt(); 
        int api_1 = reader["api"].toObject()["n1"].toInt();//api1名称
        int api_2 = reader["api"].toObject()["n2"].toInt();
        int api_3 = reader["api"].toObject()["n3"].toInt();
        int api_4 = reader["api"].toObject()["n4"].toInt();

        //qDebug() << api_1 << api_2 << api_3 << api_4;
        //QString t1 = reader["api"].toArray().at(0)["t"].toString();//api时间
        //QString t2 = reader["api"].toArray().at(1)["t"].toString();
        //QString t3 = reader["api"].toArray().at(2)["t"].toString();
        //QString t4 = reader["api"].toArray().at(3)["t"].toString();
        //QString arg1 = reader["api"].toArray().at(0)["arg"].toString();
        //QString arg2 = reader["api"].toArray().at(1)["arg"].toString();
        //QString arg3 = reader["api"].toArray().at(2)["arg"].toString();
        //QString arg4 = reader["api"].toArray().at(3)["arg"].toString();
        //qDebug() << arg1 << arg2 << arg3 << arg4;

        GlobalINFO::info[type][1] = num1;
        GlobalINFO::info[type][2] = u1;
        GlobalINFO::info[type][3] = u2;
        GlobalINFO::info[type][4] = u3;
        
        GlobalINFO::info[type][5] = num2;
        GlobalINFO::info[type][6] = api_1;
        GlobalINFO::info[type][7] = api_2;
        GlobalINFO::info[type][8] = api_3;
        GlobalINFO::info[type][9] = api_4;

        //GlobalINFO::ApiString[type][0] = arg1;
        //GlobalINFO::ApiString[type][1] = arg2;
        //GlobalINFO::ApiString[type][2] = arg3;
        //GlobalINFO::ApiString[type][3] = arg4;
        //这里暂时注释掉
        switch (type) {
        case 0:
            ui->delta_uniform->receiveSignal();
            on_delta_uniform_clicked();
            break;
        }
       /* case 1:
            ui->net_line->receiveSignal();
            on_net_line_clicked();
            break;
        case 2:
            ui->file_line->receiveSignal();
            on_file_line_clicked();
            break;
        case 3:
            ui->memory_line->receiveSignal();
            on_memory_line_clicked();
            break;
        case 4:
            ui->register_line->receiveSignal();
            on_register_line_clicked();
            break;
        }*/
    }
    return;
}
