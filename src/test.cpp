#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>

#include "LEAGUE/common_data_structures.h"
#include "LEAGUE/engine.h"
#include "LEAGUE/physics.h"
#include "player.h"
#include "background.h"

int main(int argc, char** argv){
	int opt;
	while((opt = getopt(argc, argv, "h")) != -1){

	}
	Scene scene;
	Engine* engine = Engine::getInstance();
	PhysicsWorld physics(b2Vec2(0.0, 0.0f));

	b2BodyDef bottomDef;
	bottomDef.position.Set(0.0f, -7.6f);
	bottomDef.type=b2_staticBody;
	b2Body* bottom = physics.addBody(&bottomDef);
	b2PolygonShape bottomBox;
	bottomBox.SetAsBox(50.0f, 1.0f);
	bottom->CreateFixture(&bottomBox, 1.0f);

	b2BodyDef topDef;
	topDef.position.Set(0.0f, -1.0f);
	topDef.type=b2_staticBody;
	b2Body* top = physics.addBody(&topDef);
	b2PolygonShape topBox;
	topBox.SetAsBox(50.0f, 1.0f);
	top->CreateFixture(&topBox, 1.0f);

	b2BodyDef leftDef;
	leftDef.position.Set(0.0f, -7.6f);
	leftDef.type=b2_staticBody;
	b2Body* left = physics.addBody(&leftDef);
	b2PolygonShape leftBox;
	leftBox.SetAsBox(1.0f, 50.0f);
	left->CreateFixture(&leftBox, 1.0f);

	b2BodyDef rightDef;
	rightDef.position.Set(10.0f, -7.6f);
	rightDef.type=b2_staticBody;
	b2Body* right = physics.addBody(&rightDef);
	b2PolygonShape rightBox;
	rightBox.SetAsBox(1.0f, 50.0f);
	right->CreateFixture(&rightBox, 1.0f);

	// Background* b = new Background();
	// scene.addDrawable(*b);
	
	Player* p = new Player(&physics);
	scene.addUpdateable(*p);
	scene.addDrawable(*p);

	

	scene.addUpdateable(physics);
	engine->core_loop(scene);
	engine->shutdown();
}
