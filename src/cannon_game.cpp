/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-08 19:15:02
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-12 14:54:46
*/

#include "cannon_game.hpp"


Game::Game(){
	viewer = new Viewer();
	root = new Group();
	targets = new std::vector<Target*>();
	Target* target0 = new Target(Vec3d(0.0, 600.0, -41.0));
	Target* target1 = new Target(Vec3d(-300.0, 1000.0, -41.0));
	Target* target2 = new Target(Vec3d(600.0, 1400.0, -41.0));
	Target* target3 = new Target(Vec3d(-900.0, 1800.0, -41.0));
	Target* target4 = new Target(Vec3d(1200.0, 2200.0, -41.0));
	targets->push_back(target0);
	targets->push_back(target1);
	targets->push_back(target2);
	targets->push_back(target3);
	targets->push_back(target4);

	cannon = new Cannon(root, targets);
	pov_handler = new POVHandler(viewer, cannon);
}

void Game::buildScene(){
	root->addChild(cannon->get());
	root->addChild(getSurface());
	for(auto &it : *targets){
		root->addChild(it->get());
	}
	// root->addChild(addPrimitive());
	root->addChild(getSky());
}

ref_ptr<Node> Game::addPrimitive(){
	ref_ptr<Geode> geom_node = new Geode();
	ref_ptr<ShapeDrawable> sphere = new ShapeDrawable();
	sphere->setShape(new Sphere(Vec3(0.0, 52.0, 23.0), 5.0));
	sphere->setColor(Vec4(1.0, 0.0, 0.0, 1.0));
	geom_node->addDrawable(sphere);
	return geom_node;
}

ref_ptr<Node> Game::getSurface(){
	ref_ptr<Geode> geom_node = new Geode();
	ref_ptr<ShapeDrawable> surface = new ShapeDrawable();
	surface->setShape(new Box(Vec3d(0.0, 0.0, 0.0), 10000.0, 10000.0, 3.0));
	ref_ptr<Texture2D> texture = new Texture2D();
	texture->setWrap(Texture::WRAP_R, Texture::REPEAT);
	ref_ptr<Image> image = readImageFile("./textures/grass.jpg");
	texture->setImage(image);
	surface->getOrCreateStateSet()->setTextureAttributeAndModes(
         0, texture.get() );
	geom_node->addDrawable(surface);
	ref_ptr<MatrixTransform> translate = new MatrixTransform();
	translate->setMatrix(Matrix::translate(Vec3d(0.0, 0.0, -41.0)));
	translate->addChild(geom_node);
	return translate;
}

ref_ptr<Node> Game::getSky(){
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	   geode->addDrawable( new osg::ShapeDrawable(
		 new osg::Sphere(osg::Vec3(), root->getBound().radius())) );
	osg::ref_ptr<SkyBox> skybox = new SkyBox;
	   skybox->getOrCreateStateSet()->setTextureAttributeAndModes(
		 0, new osg::TexGen );
	   skybox->setEnvironmentMap( 0,
		 readImageFile("./skybox/hills_rt.tga"),
		   readImageFile("./skybox/hills_lf.tga"),
			 readImageFile("./skybox/hills_dn.tga"),
			   readImageFile("./skybox/hills_up.tga"),
				 readImageFile("./skybox/hills_bk.tga"),
				   readImageFile("./skybox/hills_ft.tga") );
	skybox->addChild( geode.get() );
	ref_ptr<MatrixTransform> rotate = new MatrixTransform();
	rotate->setMatrix(Matrix::rotate(-1.5708, Vec3d(1, 0, 0)));
	rotate->addChild(skybox);
	return rotate;
}

ref_ptr<Group> Game::getScene(){
	return root;
}

void Game::run(){
	viewer->setUpViewInWindow(0, 0, 900, 500);
	viewer->setSceneData(root);
	viewer->setLightingMode(View::SKY_LIGHT);
	viewer->addEventHandler(pov_handler.get());
	viewer->setRunFrameScheme(Viewer::ON_DEMAND);
	viewer->run();	
}
