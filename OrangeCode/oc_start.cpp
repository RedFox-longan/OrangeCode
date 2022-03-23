#include "oc_start.h"

#include <QAction>
#include <QCoreApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>

#include <QScreen>
#include <QGuiApplication>
#include <QPropertyAnimation>

#include <QDialog>


QImage image(":/images/images/startpage_001.png");

OC_Start::OC_Start(QDialog *parent) : QDialog(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect mm = screen->availableGeometry();
    int screen_width = mm.width();
    int screen_height = mm.height();

    // 启动页逐渐消失并关闭
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(5000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));

    setWindowTitle("Orange Code");
    move((screen_width - sizeHint().width()) / 2, (screen_height - sizeHint().height()) / 2);
}



// 绘画事件
void OC_Start::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect target(0, 0, sizeHint().width(), sizeHint().height());
    painter.drawImage(target, image);
}


// 尺寸提示 const
QSize OC_Start::sizeHint() const
{
    return QSize(image.width() / 1, image.height() / 1);
}

