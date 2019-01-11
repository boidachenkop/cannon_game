/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-08 19:18:05
* @Last Modified by:   pavlo
* @Last Modified time: 2019-01-11 12:32:11
*/

#include <iostream>
#include <cmath>
#include <osg/io_utils>
#include "cannon.hpp"

using namespace osg;
using osgDB::readNodeFile;

Cannon::Cannon(ref_ptr<Group> root):
	angle(0.02), x(0), y(0.6335), z(0.77368), rotx(1), roty(0), _root(root), cannon_angle(0.8846381832530518){
	ref_ptr<Node> obj = readNodeFile("./models/Naval cannon.obj");
	cannon = new MatrixTransform();
	cannon->setMatrix(Matrix::rotate(3.14159, Vec3d(0, 0, 1)));
	cannon->setMatrix(cannon->getMatrix()*Matrix::translate(Vec3d(0.0, 0.0, 41.0)));
	cannon->addChild(obj);
}

ref_ptr<Node> Cannon::get(){
	return cannon;
}

void Cannon::turnRight(){
	double tmp = rotx;
	rotx = rotx*cos(-angle) - roty*sin(-angle);
	roty = tmp*sin(-angle) + roty*cos(-angle);

	double tmpx = x;
	x = x*cos(-angle) - y*sin(-angle);
	y = tmpx*sin(-angle) + y*cos(-angle);
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(-angle, Vec3d(0, 0, 1)));

}

void Cannon::turnLeft(){
	double tmp = rotx;
	rotx = rotx*cos(angle) - roty*sin(angle);
	roty = tmp*sin(angle) + roty*cos(angle);

	double tmpx = x;
	x = x*cos(angle) - y*sin(angle);
	y = tmpx*sin(angle) + y*cos(angle);
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(angle, Vec3d(0, 0, 1)));
	std::cout<<Matrix::rotate(angle, Vec3d(0, 0, 1))<<std::endl;
}

void Cannon::turnUp(){
	double tmpx = x;
	double tmpy = y;
	// x = x*cos(angle) + y*sin(angle)*sin(angle) + z*sin(angle)*cos(angle);
	// y = y*cos(angle) - z*sin(angle);
	// z = -tmpx*sin(angle) + tmpy*cos(angle)*sin(angle) + z*cos(angle)*cos(angle);
	x = x*rotx*cos(angle) + rotx*z*sin(angle);
	y = tmpx*sin(angle)*sin(angle) + y*roty*cos(angle) - z*cos(angle)*sin(angle);
	z = -tmpx*cos(angle)*sin(angle) + tmpy*roty*sin(angle) + z*cos(angle)*cos(angle);
	// cannon_angle=cannon_angle+angle;
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(angle, Vec3d(rotx, roty, 0)));
	std::cout<<Matrix::rotate(angle, Vec3d(rotx, roty, 0))<<std::endl;
}


void Cannon::turnDown(){
	double tmpx = x;
	double tmpy = y;
	// x = x*cos(-angle) + y*sin(-angle)*sin(-angle) + z*sin(-angle)*cos(-angle);
	// y = y*cos(-angle) - z*sin(-angle);
	// z = -tmpx*sin(-angle) + tmpy*cos(-angle)*sin(-angle) + z*cos(-angle)*cos(-angle);
	x = x*rotx*cos(-angle) + rotx*z*sin(-angle);
	y = tmpx*sin(-angle)*sin(-angle) + y*roty*cos(-angle) - z*cos(-angle)*sin(-angle);
	z = -tmpx*cos(-angle)*sin(-angle) + tmpy*roty*sin(-angle) + z*cos(-angle)*cos(-angle);
	// cannon_angle=cannon_angle-angle;
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(-angle, Vec3d(rotx, roty, 0)));
}

void Cannon::shoot(){
	double norm = 82.07/sqrt(x*x+y*y+z*z);
	CannonBall* ball = new CannonBall(x*norm, y*norm, z*norm);
	_root->addChild(ball->get());
}



