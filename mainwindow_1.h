#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "type_line.h"

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject *obj, QEvent *event);
    void showView(QWidget *previewCopy);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent * e);

signals:
    void hideView(QWidget *viewCopy);

private slots:
    void on_quit_Btn_clicked();
    void on_minimized_Btn_clicked();
    void on_file_line_clicked();
    void on_memory_line_clicked();
    void on_heap_line_clicked();
    void on_net_line_clicked();
    void on_register_line_clicked();
    void on_back_Btn_clicked();

    // 网络链接和监听
    void acceptConnection();
    void readClient();

private:
    Ui::MainWindow *ui;
    // 拖动界面
    bool canMove=false;
    QPoint p;
    // 类型选择
    QString selected_Type = "";
    Type_Line *type_List[5];
    // 网络链接
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    void setUpSocket();
    // 解析json
    void parsing_Json(QString str);

    // 界面相关
    void setUpView();
    void setUpType_List();
    void changeColor();
    void changeBigIcon(QString icon_name);
};
#endif // MAINWINDOW_H
