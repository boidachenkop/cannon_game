/*
* @Author: Pavlo Boidachenko
* @Date:   2019-01-10 16:47:47
* @Last Modified by:   Pavlo Boidachenko
* @Last Modified time: 2019-01-12 16:28:05
*/

#include <iostream>
#include <osg/io_utils>
#include "cannon_ball.hpp"


CannonBall::CannonBall(Vec3d spawn_point, std::vector<Target*>* targets, 
	ref_ptr<Group> root):
	position(spawn_point), speed(200), g(0, 0, -9.8),
	m(10), b(0.3), _targets(targets), _root(root)
{
	ref_ptr<Geode> geode = new Geode();
	ref_ptr<ShapeDrawable> sphere = new ShapeDrawable();
	sphere->setShape(new Sphere(position, 4.0));
	ref_ptr<Texture2D> texture = new Texture2D();
	ref_ptr<Image> image = readImageFile("./textures/cannon_ball.png");
	texture->setImage(image);
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(
     0, texture.get() );
	geode->addDrawable(sphere);
	ball = new MatrixTransform();
	ball->addChild(geode);
}

ref_ptr<MatrixTransform> CannonBall::get(){
	return ball;
}

Vec3d CannonBall::trajectory(double t, Vec3d direction){
	Vec3d v0 = direction*speed;
	t*=6;
	// return v0*t+g*((t*t)/2);
	double beta = b/m;
	return (v0-(g/beta))*(1/beta)*(1-pow(M_E, -beta*t))+(g/beta)*t;
}

Target* CannonBall::collisionDetected(Vec3d coords){
	Vec3d target_pos;
	double sphere_radius = 100;
	for(auto it : *_targets){
		target_pos = it->getPosition();
		if(coords.x()<target_pos.x()+sphere_radius && coords.x()>target_pos.x()-sphere_radius &&
			coords.y()<target_pos.y()+sphere_radius && coords.y()>target_pos.y()-sphere_radius &&
			coords.z()<target_pos.z()+sphere_radius && coords.z()>target_pos.z()-sphere_radius){
			return it;
		}
	}
	return NULL;
}

ref_ptr<AnimationPathManipulator> CannonBall::ballPath(Vec3d direction){
	double speed = 150.0;
	ref_ptr<AnimationPath> ball_path = new AnimationPath();
	ball_path->setLoopMode(AnimationPath::NO_LOOPING);
	Vec3d traj_vec = Vec3d(0, 0, 100);
	for(double t=0.0; traj_vec.z()>-38 && !collisionDetected(traj_vec); t+=0.01){
		traj_vec = trajectory(t, direction);
		ball_path->insert(t, traj_vec);
	}
	ref_ptr<AnimationPathManipulator> apcb = new AnimationPathManipulator();
	apcb->setAnimationPath(ball_path);
	return apcb;
}

void CannonBall::move(Vec3d direction){
	ball->setUpdateCallback(ballPath(direction));
}