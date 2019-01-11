#ifndef POV_HANDLER_BP
#define POV_HANDLER_BP

#include <osg/observer_ptr>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>

#include "cannon.hpp"

using namespace osg;
using osgGA::GUIActionAdapter;
using osgGA::GUIEventAdapter;
using osgGA::GUIEventHandler;
using osgGA::NodeTrackerManipulator;
using osgGA::KeySwitchMatrixManipulator;
using osgGA::TrackballManipulator;
using osgViewer::Viewer;

class POVHandler : public GUIEventHandler{
	observer_ptr<Viewer> _viewer;
	observer_ptr<Camera> _camera;
	Cannon* _cannon;
	ref_ptr<NodeTrackerManipulator> manip;

public:
	virtual bool handle(const GUIEventAdapter &, GUIActionAdapter &);

	POVHandler(const ref_ptr<Viewer> & viewer, Cannon* cannon);

protected:
	virtual ~POVHandler()
	{ }
};


#endif //POV_HANDLER_BP