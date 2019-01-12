/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-09 14:27:08
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-11 13:25:26
*/

#include "pov_handler.hpp"
// #include <osg/io_utils>

using namespace osg;
using osgGA::GUIActionAdapter;
using osgGA::GUIEventAdapter;
using osgGA::GUIEventHandler;

POVHandler::POVHandler(const ref_ptr<Viewer> & viewer, Cannon* cannon)
: _viewer(viewer), _cannon(cannon){ 
	_camera = _viewer->getCamera();
	// _camera->setAllowEventFocus(false);
	// _camera->setViewMatrix( Matrix::lookAt(Vec3d(0, -140.0, 40), Vec3d(0, 100, 30), Vec3d(0,1,0))); 
	manip = new NodeTrackerManipulator();
	// manip->setHomePosition(Vec3d(40, 100.0, 60), Vec3d(40, -140, 40), Vec3d(0,0,1));
	manip->setHomePosition(Vec3d(0, 100, 40), Vec3d(0, -100, 0), Vec3d(0,0,1));
	manip->setTrackerMode(NodeTrackerManipulator::NODE_CENTER_AND_ROTATION);
	manip->setTrackNode(cannon->get());

	ref_ptr<KeySwitchMatrixManipulator> keySwitch = new
	KeySwitchMatrixManipulator;
	keySwitch->addMatrixManipulator( '1', "Trackball", new TrackballManipulator );
	keySwitch->addMatrixManipulator( '2', "NodeTracker", manip.get() );
	_viewer->setCameraManipulator(keySwitch.get());
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
