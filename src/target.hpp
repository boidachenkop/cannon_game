#ifndef TARGET_BP
#define TARGET_BP

#include <osg/Group>
#include <osgDB/ReadFile>
#include <osg/Vec3d>
#include <osg/MatrixTransform>
#include <osg/Texture2D>

using namespace osg;
using osgDB::readNodeFile;
using osgDB::readImageFile;

class Target{
public:
	Target(Vec3d pos);
	ref_ptr<MatrixTransform> get();	
	Vec3d getPosition();
private:
	ref_ptr<MatrixTransform> target;
	Vec3d position;
};

#endif //TARGET_BP
