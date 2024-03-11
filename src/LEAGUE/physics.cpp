#include <iostream>
#include <LEAGUE/physics.h>
#include <box2d/box2d.h>
#include "MyContactListener.h"

PhysicsWorld::PhysicsWorld(b2Vec2 gravity) : world(gravity){
	this->gravity = gravity;
	std::cout << "Gravity: " << world.GetGravity().x << ", " << world.GetGravity().y << std::endl;
	MyContactListener MyContactListenerInstance;
	world.SetContactListener(&MyContactListenerInstance);
}

b2Body* PhysicsWorld::addBody(b2BodyDef* bodyDefinition){
	return world.CreateBody(bodyDefinition);
}

void PhysicsWorld::update(double delta){
	world.Step(1.0f/60.0f, 8, 3);
}


