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
    class geometry{
        public:int x;
                int y;
          geometry(int x_,int y_):x(x_),y(y_){
//              assert(x_<1000&&y_<1000);
          }
          geometry(const geometry& geometryobj){
              x=geometryobj.x;
              y=geometryobj.y;
          }
          void operator=(const geometry& geometryobj){
              x=geometryobj.x;
              y=geometryobj.y;
          }
            int operator-(const geometry& geometryobj){
                return std::sqrt((x-geometryobj.x)*(x-geometryobj.x)+(y-geometryobj.y)*(y-geometryobj.y));
            }

    };

    const std::list<route::geometry>& get_geo()const;
    ~route();
private:
    void updatePos(const QPoint&);
    std::list<geometry> geo;
    bool enable=true;

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
        if (event->button() == Qt::LeftButton&&enable) {
            updatePos(event->pos());
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {

        if (event->buttons() & Qt::LeftButton&&enable) {
            updatePos(event->pos());
        }
    }

};

#endif // ROUTE_H
