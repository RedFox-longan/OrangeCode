#ifndef SHAPEDCLOCK_H
#define SHAPEDCLOCK_H

// #include <QWidget>
#include <QDialog>

// QDialog QWidget
class OC_Start : public QDialog {
Q_OBJECT
public:
    OC_Start(QDialog *parent = nullptr);
    QSize sizeHint() const override;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QPoint dragPosition;
};

#endif
