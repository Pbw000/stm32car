#include "route.h"

route::route(QWidget *parent): QWidget(parent) {
	setFixedSize(550, 550);
}
void route::updatePos(const QPoint& pos) {
    geo.push_back(geometry(pos.x(),pos.y()));
	update();
}
const std::list<route::geometry>& route::get_geo()const {
	return geo;
}
route::~route() {
	geo.clear();
}
