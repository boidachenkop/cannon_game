/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-09 14:27:08
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-19 14:29:24
*/

#include "pov_handler.hpp"
// #include <osg/io_utils>

using namespace osg;
using osgGA::GUIActionAdapter;
using osgGA::GUIEventAdapter;
using osgGA::GUIEventHandler;

POVHandler::POVHandler(const ref_ptr<Viewer> & viewer, Cannon* cannon)
: _viewer(viewer), _cannon(cannon){ 

	manip = new NodeTrackerManipulator();
	manip->setHomePosition(Vec3d(0, 80, 40), Vec3d(0, -200, 10), Vec3d(0,0,1));
	manip->setTrackerMode(NodeTrackerManipulator::NODE_CENTER_AND_ROTATION);
	manip->setTrackNode(cannon->get());
	_viewer->setCameraManipulator(manip);
}
bool POVHandler::handle(const GUIEventAdapter & ea,
	GUIActionAdapter & aa){
	if (ea.getEventType() != GUIEventAdapter::KEYDOWN) {
		return false;
	}
	switch(ea.getUnmodifiedKey()){
		case GUIEventAdapter::KEY_A:
			_cannon->turnLeft();
			break;
		case GUIEventAdapter::KEY_D:
			_cannon->turnRight();
			break;
		case GUIEventAdapter::KEY_W:
			_cannon->turnDown();
			break;
		case GUIEventAdapter::KEY_S:
			_cannon->turnUp();
			break;
		case GUIEventAdapter::KEY_B:
			_cannon->shoot();
			break;
		default:
			return false;
	}
	aa.requestRedraw();
	return true;
}
