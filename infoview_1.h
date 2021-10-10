#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

namespace Ui {
class InfoView;
}

class InfoView : public QWidget
{
    Q_OBJECT

public:
    explicit InfoView(QWidget *parent = nullptr);
    ~InfoView();
    void resetView(int info[10], bool animate=true);

private:
    Ui::InfoView *ui;
    QGraphicsOpacityEffect *effect = nullptr;
    QPropertyAnimation *disappear_animation = nullptr;
    QPropertyAnimation *appear_animation = nullptr;
    int infoList[10];
    void setUpView();
    void setUpAnimation();
    void changeInfo();
    void setMainType(QString type, QString subTitle);
    void setVirusType(int num, QString imgs[], QString main_labels[], QString sub_labels[]);
    void setAPI(int num, QString apis[]);
};

#endif // INFOVIEW_H
