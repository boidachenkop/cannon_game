
#ifndef CANNON_BALL_BP
#define CANNON_BALL_BP

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Group>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osg/AnimationPath>
#include <osgGA/AnimationPathManipulator>

#include <unistd.h>
#include <cmath>
#include <chrono> //for time mesurement
#include <vector>
#include <thread>

#include "target.hpp"

using namespace osg;
using osgDB::readImageFile;
using osgGA::AnimationPathManipulator;

class CannonBall{
public:
	CannonBall(Vec3d spawn_point, std::vector<Target*>* targets, ref_ptr<Group> root);
	ref_ptr<MatrixTransform> get();
	void move(Vec3d direction);
	Vec3d trajectory(double t, Vec3d direction);
	ref_ptr<AnimationPathCallback> ballPath(Vec3d direction);
	void removeTarget();
	bool collisionDetected(Vec3d coords, double t); //returns target thet hit or NULL if not

private:
	ref_ptr<Group> _root;
	ref_ptr<MatrixTransform> ball;
	Vec3d g;
	double m; 				// mass
	double b; 				// drag coefitient
	Vec3d position;			//position	
	double speed;			//ball speed 
	std::vector<Target*>* _targets;
	Target* target_hit;
	double time_hit;
};

#endif //CANNON_BALL_BP