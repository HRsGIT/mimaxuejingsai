#include "AnimatedLabel.h"


AnimatedLabel::AnimatedLabel(QWidget *parent):QLabel(parent){
};

void AnimatedLabel::setColor (QColor color){
    setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4);").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
}

QColor AnimatedLabel::color(){
    return Qt::black; // getter is not really needed for now
}

// 鼠标点击操作
void AnimatedLabel::mouseReleaseEvent(QMouseEvent * ev){
    if(ev->button() == Qt::LeftButton) {
        emit clicked();	// 发射信号
    }
}
