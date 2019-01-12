#ifndef CANNON_GAME_BP
#define CANNON_GAME_BP

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Group>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <cmath>

#include "cannon.hpp"
#include "pov_handler.hpp"
#include "skybox.hpp"
#include "target.hpp"

using namespace osg;
using osgDB::readNodeFile;
using osgDB::readImageFile;
using osgViewer::Viewer;

class Game{
public:
	Game();
	void buildScene();
	ref_ptr<Node> addPrimitive();
	ref_ptr<Node> getSurface();
	ref_ptr<Node> getSky();
	ref_ptr<Group> getScene();

	void run();
private:
	ref_ptr<Group> root;
	std::vector<Target*>* targets;
	Cannon* cannon;
	ref_ptr<Viewer> viewer;
	ref_ptr<POVHandler> pov_handler;
};

#endif //CANNON_GAME_BP