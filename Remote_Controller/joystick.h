#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include<QTimer>
#include <QMouseEvent>
#define radius1 40
#define increasement 5

class Joystick : public QWidget {
    Q_OBJECT
public:
    explicit Joystick(QWidget *parent = nullptr,const int& radius=400) : QWidget(parent), m_x(radius/2), m_y(radius/2) {
        setFixedSize(radius, radius);
    }
bool myFlag=false;
    bool isPressed=false;
int m_x, m_y;
private slots:
void moveToCenter(){
    if(!myFlag)return;
    int centerX = width() / 2;
    int centerY = height() / 2;
    int dx = m_x - centerX;
    int dy = m_y - centerY;
    float n_x,n_y;
    if(dx>0){
        n_x=m_x-dx/6;
    }
    else if(dx<0)
    {
        n_x=static_cast<float>(m_x)-static_cast<float>(dx)/6;
    }
    else{
        n_x=centerX;
    }
    if(dy>0){
        n_y=static_cast<float>(m_y)-static_cast<float>(dy)/6;
    }
    else if(dy<0)
    {
        n_y=static_cast<float>(m_y)-static_cast<float>(dy)/6;
    }
    else{
        n_y=centerY;
    }

    updatePosition(QPoint(static_cast<int>(n_x),static_cast<int>(n_y)));
    if(!(n_x==centerX&&n_y==centerY)){
        QTimer *pTimer = new QTimer(this);
        connect(pTimer, SIGNAL(timeout()), this, SLOT(moveToCenter()));
        pTimer->setSingleShot(true);
        pTimer->start(16);
    }
    else{
        myFlag=false;
    }

}
protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);

        QColor color;
        color.setRgb(10,46,47,48);
        painter.setBrush(color);
        painter.drawEllipse(rect());

        painter.setBrush(Qt::black);
        if(isPressed)
        painter.drawEllipse(m_x - (radius1+increasement)/2, m_y - (radius1+increasement)/2, radius1+increasement, radius1+increasement);
        else painter.drawEllipse(m_x - radius1/2, m_y - radius1/2, radius1, radius1);
    }

    void mousePressEvent(QMouseEvent *event) override {

        if (event->button() == Qt::LeftButton) {     myFlag=false;
            isPressed=true;
            updatePosition(event->pos());
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {

        if (event->buttons() & Qt::LeftButton) {
            myFlag=false;
            isPressed=true;
            updatePosition(event->pos());
        }
    }

private:
    void updatePosition(const QPoint &pos) {
        int centerX = width() / 2;
        int centerY = height() / 2;
        int maxDist = width() / 2 - radius1/2-increasement/2;
        int dx = pos.x() - centerX;
        int dy = pos.y() - centerY;
        double dist = sqrt(dx * dx + dy * dy);

        if (dist > maxDist) {
            dx = dx * maxDist / dist;
            dy = dy * maxDist / dist;
        }

        m_x = centerX + dx;
        m_y = centerY + dy;
        update();
    }


    void mouseReleaseEvent(QMouseEvent *event)override {
        if (event->button() == Qt::LeftButton) {
            myFlag=true;
            isPressed=false;
            returnToCenter();
        }
    }
    void returnToCenter() {
        moveToCenter();
    }

};

#endif // JOYSTICK_H
