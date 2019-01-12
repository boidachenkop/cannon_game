#ifndef CANNON_BP
#define CANNON_BP

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/Texture2D>

#include <vector>

#include "cannon_ball.hpp"
#include "target.hpp"

using namespace osg;
using osgDB::readNodeFile;

class Cannon{
public:
	Cannon(ref_ptr<Group> root, std::vector<Target*>* targets);
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
	Vec4d front_vec; // front cannon vector  
	double angle;
	std::vector<Target*>* _targets;	
};

#endif //CANNON_BP