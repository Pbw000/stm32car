#ifndef ROUTE_H
#define ROUTE_H
#include <QObject>
#include <QWidget>
#include <QPainter>
#include<list>
#include <QMouseEvent>
class route:public QWidget {
    Q_OBJECT
     friend class MainWindow;
public:
    route(QWidget *parent = nullptr);
    struct geometry{
        int x;
        int y;
    };

    const std::list<route::geometry>& get_geo()const;
    ~route();
private:
    void updatePos(const QPoint&);
    std::list<geometry> geo;

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);

        painter.setBrush(Qt::white);
        painter.drawRect(rect());

        painter.setBrush(Qt::black);
        painter.setPen(QPen(10));
        std::list<geometry>::const_iterator pre = geo.cbegin();
        for (std::list<geometry>::const_iterator var = geo.cbegin(); var !=geo.cend();var++) {
            painter.drawLine(pre->x,pre->y,var->x,var->y);
            pre=var;
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        geo.clear();
        if (event->button() == Qt::LeftButton) {
            updatePos(event->pos());
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {

        if (event->buttons() & Qt::LeftButton) {
            updatePos(event->pos());
        }
    }

};

#endif // ROUTE_H
