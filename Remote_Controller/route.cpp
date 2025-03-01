#include "route.h"

route::route(QWidget *parent): QWidget(parent) {
	setFixedSize(550, 550);
}
void route::updatePos(const QPoint& pos) {
	geometry a;
	a.x = pos.x();
	a.y = pos.y();
	geo.push_back(a);
	update();
}
const std::list<route::geometry>& route::get_geo()const {
	return geo;
}
route::~route() {
	geo.clear();
}
