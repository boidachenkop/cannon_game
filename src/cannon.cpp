/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-08 19:18:05
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-11 13:07:19
*/

#include <iostream>
#include <cmath>
#include <osg/io_utils>
#include "cannon.hpp"

using namespace osg;
using osgDB::readNodeFile;

Cannon::Cannon(ref_ptr<Group> root):
	angle(0.02), rotx(1), roty(0), _root(root){
	ref_ptr<Node> obj = readNodeFile("./models/Naval cannon.obj");
	cannon = new MatrixTransform();
	cannon->setMatrix(Matrix::rotate(3.14159, Vec3d(0, 0, 1)));
	cannon->setMatrix(cannon->getMatrix()*Matrix::translate(Vec3d(0.0, 0.0, 41.0)));
	cannon->addChild(obj);
	front_vec = Vec4d(0, 1, 0, 1);
	front_vec = Matrix::rotate(0.8846381, Vec3d(1, 0, 0)).preMult(front_vec);
}

ref_ptr<Node> Cannon::get(){
	return cannon;
}

void Cannon::turnRight(){
	double tmp = rotx;
	rotx = rotx*cos(-angle) - roty*sin(-angle);
	roty = tmp*sin(-angle) + roty*cos(-angle);
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(-angle, Vec3d(0, 0, 1)));
	front_vec = Matrix::rotate(-angle, Vec3d(0, 0, 1)).preMult(front_vec);
}

void Cannon::turnLeft(){
	double tmp = rotx;
	rotx = rotx*cos(angle) - roty*sin(angle);
	roty = tmp*sin(angle) + roty*cos(angle);
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(angle, Vec3d(0, 0, 1)));
	front_vec = Matrix::rotate(angle, Vec3d(0, 0, 1)).preMult(front_vec);
}

void Cannon::turnUp(){
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(angle, Vec3d(rotx, roty, 0)));
	front_vec = Matrix::rotate(angle, Vec3d(rotx, roty, 0)).preMult(front_vec);
}


void Cannon::turnDown(){
	cannon->setMatrix(cannon->getMatrix()*Matrix::rotate(-angle, Vec3d(rotx, roty, 0)));
	front_vec = Matrix::rotate(-angle, Vec3d(rotx, roty, 0)).preMult(front_vec);
}

void Cannon::shoot(){
	double norm = 116.00/front_vec.length();
	CannonBall* ball = new CannonBall(front_vec.x()*norm, front_vec.y()*norm, front_vec.z()*norm);
	_root->addChild(ball->get());
}



