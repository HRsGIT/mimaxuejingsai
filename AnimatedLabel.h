#ifndef ANIMATEDLABEL_H
#define ANIMATEDLABEL_H

#include <QLabel>
#include <QMouseEvent>

class AnimatedLabel: public QLabel
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor);

public:
    AnimatedLabel(QWidget *parent=0);
    void setColor (QColor color);

protected:
    void mouseReleaseEvent(QMouseEvent * ev);

signals:
    void clicked();

private:
    QColor color();
};

#endif // ANIMATEDLABEL_H
