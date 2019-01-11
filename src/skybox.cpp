/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-10 15:31:36
* @Last Modified by:   pavlo
* @Last Modified time: 2019-01-10 16:06:36
*/

#include "skybox.hpp"

SkyBox::SkyBox(){
	setReferenceFrame( osg::Transform::ABSOLUTE_RF );
	setCullingActive( false );
	osg::StateSet* ss = getOrCreateStateSet();
	ss->setAttributeAndModes( new osg::Depth(
	osg::Depth::LEQUAL, 1.0f, 1.0f) );
	ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
	ss->setMode( GL_CULL_FACE, osg::StateAttribute::OFF );
	ss->setRenderBinDetails( 5, "RenderBin" );
}

void SkyBox::setEnvironmentMap( unsigned int unit,
	Image* posX, osg::Image* negX,
	Image* posY, osg::Image* negY,
	Image* posZ, osg::Image* negZ )
{
	ref_ptr<TextureCubeMap> cubemap = new TextureCubeMap;
	cubemap->setImage( TextureCubeMap::POSITIVE_X, posX );
	cubemap->setImage( TextureCubeMap::NEGATIVE_X, negX );
	cubemap->setImage( TextureCubeMap::POSITIVE_Y, posY );
	cubemap->setImage( TextureCubeMap::NEGATIVE_Y, negY );
	cubemap->setImage( TextureCubeMap::POSITIVE_Z, posZ );
	cubemap->setImage( TextureCubeMap::NEGATIVE_Z, negZ );
	cubemap->setResizeNonPowerOfTwoHint( false );
	getOrCreateStateSet()->setTextureAttributeAndModes(
	unit, cubemap.get() );
}

bool SkyBox::computeLocalToWorldMatrix( Matrix& matrix,
	NodeVisitor* nv ) const{
	if ( nv && nv->getVisitorType()==NodeVisitor::CULL_VISITOR ){
		osgUtil::CullVisitor* cv = static_cast<osgUtil::CullVisitor*>( nv );
		matrix.preMult( osg::Matrix::translate(cv->getEyeLocal()) );
		return true;
	}
	else{
		return osg::Transform::computeLocalToWorldMatrix( matrix, nv );
	}
}

bool SkyBox::computeWorldToLocalMatrix( Matrix& matrix,
	NodeVisitor* nv ) const{
	if ( nv && nv->getVisitorType()==
		NodeVisitor::CULL_VISITOR ){
		osgUtil::CullVisitor* cv =static_cast<osgUtil::CullVisitor*>( nv );
		matrix.postMult( Matrix::translate(-cv->getEyeLocal()) );
		return true;
	}
	else{
		return Transform::computeWorldToLocalMatrix( matrix, nv );
	}
}
