#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QGraphicsOpacityEffect>

namespace Ui {
class animationView;
}

class animationView : public QWidget
{
    Q_OBJECT

public:
    explicit animationView(QWidget *parent = nullptr);
    ~animationView();

    void start();

private:
    Ui::animationView *ui;
    QLabel *circle;
    QGraphicsOpacityEffect *circle_effect;
    QTimer *timer;
    int t=0;
    void updateView();
    void setUpCircle();
    void showCircle();
    void hideCircle();
};

#endif // ANIMATIONVIEW_H
