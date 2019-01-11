
#ifndef CANNON_BALL_BP
#define CANNON_BALL_BP

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Group>

using namespace osg;

class CannonBall{
public:
	CannonBall(double x, double y, double z);
	ref_ptr<Geode> get();
private:
	ref_ptr<Geode> ball;
	double _x, _y, _z;
};

#endif //CANNON_BALL_BP