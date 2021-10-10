#ifndef EXELOADVIEW_H
#define EXELOADVIEW_H

#include <QMainWindow>
#include <QSequentialAnimationGroup>

namespace Ui {
class exeLoadView;
}

class exeLoadView : public QMainWindow
{
    Q_OBJECT

public:
    explicit exeLoadView(QWidget *parent = nullptr);
    ~exeLoadView();

    bool eventFilter(QObject *obj, QEvent *event);
    void showView(QWidget *previewCopy);

protected:
    // 窗口移动
    void mouseMoveEvent(QMouseEvent *e);//鼠标移动
    void mousePressEvent(QMouseEvent *e);//鼠标按下移动

signals:
    void hideView(QWidget *viewCopy);

private slots:
    void on_quit_Btn_clicked();
    void on_minimized_Btn_clicked();
    void on_start_Btn_clicked();

private:
    Ui::exeLoadView *ui;
    QPoint p;
    QSequentialAnimationGroup *exe_animal;
    bool exe_animal_running=false;
    void setUpView();
    void flashExeIcon();
};

#endif // EXELOADVIEW_H
