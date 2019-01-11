#ifndef CANNON_BP
#define CANNON_BP

#include <osg/Group>
#include <osg/Quat>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

#include "cannon_ball.hpp"

using namespace osg;
using osgDB::readNodeFile;

class Cannon{
public:
	Cannon(ref_ptr<Group> root);
	ref_ptr<Node> get();
	void turnRight();
	void turnLeft();
	void turnUp();
	void turnDown();
	void shoot();
private:
	ref_ptr<MatrixTransform> cannon;
	ref_ptr<Group> _root;
	double rotx, roty; // rotation vector
	double x, y, z; // front cannon vector  
	double angle;
	double cannon_angle;
};

#endif //CANNON_BP