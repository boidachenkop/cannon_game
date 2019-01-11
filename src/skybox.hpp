
#ifndef SKYBOX_BP
#define SKYBOX_BP

#include <osg/Depth>
#include <osg/TexGen>
#include <osg/TextureCubeMap>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgUtil/CullVisitor>
#include <osgViewer/Viewer>

using namespace osg;

class SkyBox : public Transform{
public:
	SkyBox();
	SkyBox( const SkyBox& copy, CopyOp copyop=CopyOp::SHALLOW_COPY )
	: Transform(copy, copyop) {}
	META_Node( osg, SkyBox );
	void setEnvironmentMap( unsigned int unit, Image* posX,
		Image* negX, Image* posY, Image* negY,
		Image* posZ, Image* negZ );
	virtual bool computeLocalToWorldMatrix( Matrix& matrix,
		NodeVisitor* nv ) const;
	virtual bool computeWorldToLocalMatrix( Matrix& matrix,
		NodeVisitor* nv ) const;
protected:
	virtual ~SkyBox() {}
};

#endif //SKYBOX_BP