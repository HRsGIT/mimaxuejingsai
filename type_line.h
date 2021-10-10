#ifndef TYPE_LINE_H
#define TYPE_LINE_H

#include <QWidget>
#include <QMovie>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class Type_Line;
}

class Type_Line : public QWidget
{
    Q_OBJECT

public:
    explicit Type_Line(QWidget *parent = nullptr);
    ~Type_Line();

    void setUpView(QString img_path, QString label_name);
    void receiveSignal();
    void beSelected();
    void notSelected();

private:
    Ui::Type_Line *ui;
    QMovie *state_gif = nullptr;
    QGraphicsOpacityEffect *effect = nullptr;
    QPropertyAnimation *animation = nullptr;
    void setUpGifView();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent * ev);
};

#endif // TYPE_LINE_H
