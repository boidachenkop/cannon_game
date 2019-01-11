/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-10 16:47:47
* @Last Modified by:   pavlo
* @Last Modified time: 2019-01-10 19:06:44
*/

#include "cannon_ball.hpp"

CannonBall::CannonBall(double x, double y, double z):
	_x(x), _y(y), _z(z)
{
	ball = new Geode();
	ref_ptr<ShapeDrawable> sphere = new ShapeDrawable();
	sphere->setShape(new Sphere(Vec3(_x, _y, _z), 4.0));
	sphere->setColor(Vec4(0.8, 0.2, 0.2, 1.0));
	ball->addDrawable(sphere);
}

ref_ptr<Geode> CannonBall::get(){
	return ball;
}
