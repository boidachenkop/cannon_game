/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-11 22:57:07
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-12 14:59:59
*/

#include "target.hpp"

Target::Target(Vec3d pos): position(pos){
	ref_ptr<Node> obj = readNodeFile("./models/10480_Archery_target_v1_max2011_iteration-2.obj");
	target = new MatrixTransform();	
	target->setMatrix(Matrix::rotate(-1.5708, Vec3d(1, 0, 0)));
	target->setMatrix(target->getMatrix()*Matrix::translate(pos));
	ref_ptr<Texture2D> texture = new Texture2D();
	ref_ptr<Image> image = readImageFile("./textures/10480_Archery_target_v1_Diffuse.jpg");
	texture->setImage(image.get());
	target->getOrCreateStateSet()->setTextureAttributeAndModes(
     0, texture.get() );
	target->addChild(obj);
}

Vec3d Target::getPosition(){
	return position;
}

ref_ptr<MatrixTransform> Target::get(){
	return target;
}

