#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "qevent.h"
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QEasingCurve>
#include <QPropertyAnimation>

class Joystick : public QWidget {
    Q_OBJECT
public:
    explicit Joystick(QWidget *parent = nullptr, int radius = 400)
        : QWidget(parent),
        m_center(radius/2, radius/2),
        m_handleRadius(40),
        m_pressedHandleRadius(45),
        m_maxDistance(radius/2 - m_pressedHandleRadius)
    {
        setFixedSize(radius, radius);
        setupAnimation();
        startReturnAnimation();
    }

signals:
    void positionChanged(qreal x, qreal y);

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // 绘制背景
        painter.setBrush(QColor(10, 46, 47, 48));
        painter.drawEllipse(rect());

        // 绘制摇杆手柄
        painter.setBrush(m_isPressed ? Qt::darkGray : Qt::black);
        const int radius = m_isPressed ? m_pressedHandleRadius : m_handleRadius;
        painter.drawEllipse(m_currentPos, radius, radius);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            stopAnimation();
            m_isPressed = true;
            updatePosition(event->pos());
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            updatePosition(event->pos());
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_isPressed = false;
            startReturnAnimation();
        }
    }

private:
    void setupAnimation() {
        m_returnAnimation = new QPropertyAnimation(this, "handlePosition");
        m_returnAnimation->setEasingCurve(QEasingCurve::OutCubic);
        m_returnAnimation->setDuration(400);
        m_returnAnimation->setStartValue(m_currentPos);
        m_returnAnimation->setEndValue(m_center);
        connect(m_returnAnimation, &QPropertyAnimation::valueChanged, [this]{
            update();
            emit positionChanged(normalizedX(), normalizedY());
        });
    }

    void updatePosition(const QPoint& pos) {
        QPoint vector = pos - m_center;
        qreal distance = std::hypot(vector.x(), vector.y());

        if (distance > m_maxDistance) {
            vector *= m_maxDistance / distance;
        }

        m_currentPos = m_center + vector;
        update();
        emit positionChanged(normalizedX(), normalizedY());
    }

    void startReturnAnimation() {
        m_returnAnimation->stop();
        m_returnAnimation->setStartValue(m_currentPos);
        m_returnAnimation->start();
    }

    void stopAnimation() {
        m_returnAnimation->stop();
    }

    qreal normalizedX() const {
        return static_cast<qreal>(m_currentPos.x() - m_center.x()) / m_maxDistance;
    }

    qreal normalizedY() const {
        return static_cast<qreal>(m_center.y() - m_currentPos.y()) / m_maxDistance;
    }

    // 动画属性
    Q_PROPERTY(QPoint handlePosition READ getHandlePosition WRITE setHandlePosition)
    QPoint getHandlePosition() const { return m_currentPos; }
    void setHandlePosition(QPoint pos) { m_currentPos = pos; update(); }

    // 成员变量
    QPropertyAnimation* m_returnAnimation;
    const QPoint m_center;
    QPoint m_currentPos;
    bool m_isPressed = false;

    const int m_handleRadius;
    const int m_pressedHandleRadius;
    const qreal m_maxDistance;
};

#endif // JOYSTICK_H
