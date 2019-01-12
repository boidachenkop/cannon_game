/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-08 19:18:05
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-12 14:53:49
*/

#include "cannon.hpp"

using namespace osg;

Cannon::Cannon(ref_ptr<Group> root, std::vector<Target*>* targets):
	angle(0.02), rotx(1), roty(0), _root(root), _targets(targets){
	ref_ptr<Node> obj = readNodeFile("./models/Naval cannon.obj");
	cannon = new MatrixTransform();
	cannon->setMatrix(Matrix::rotate(3.14159, Vec3d(0, 0, 1)));
	cannon->addChild(obj);
	front_vec = Vec4d(0, 0.9145, 0.4045, 1);
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
	double norm = 80.0/front_vec.length();
	CannonBall* ball = new CannonBall(Vec3d(front_vec.x()*norm, front_vec.y()*norm, front_vec.z()*norm), _targets, _root);
	_root->addChild(ball->get());
	ball->move(Vec3d(front_vec.x(), front_vec.y(), front_vec.z()));
}



