#include "mathfu/vector.h"
#include "bullet.h"
#include "player.h"
#include "LEAGUE/physics.h"
#include "LEAGUE/engine.h"
#include <iostream>
#include <string>
#include <box2d/box2d.h>
#include <random>

Bullet::Bullet(PhysicsWorld* physics, Player* player){
	this->player = player;

	// Generate a random number between 0 and RAND_MAX
	loadImage("./assets/tank_bullet.png");
	// Need a body definition before we can make a body
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
    	bodyDef->position.Set(-100, 0);
	// Physics engine makes the body for us and returns a pointer to it
	body = physics->addBody(bodyDef);
	// Need a shape
	b2CircleShape ballShape;
	ballShape.m_radius=0.16f;
	// Must apply a fixture.  Fixes shape and other properties to it.
	b2FixtureDef ballFixture;
	ballFixture.shape = &ballShape;
	ballFixture.density = 1.0f;
	ballFixture.friction = 0.3f;
	ballFixture.restitution = 0.3f;
	// Make the fixture.
	body->CreateFixture(&ballFixture);
}

Bullet::~Bullet(){
	delete bodyDef;
}

void Bullet::setBody(b2Body* body){
	this->body = body;
}

b2BodyDef* Bullet::getBodyDef(){
	return bodyDef;
}

void Bullet::update(double delta){
	//std::cout << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
	auto events = Engine::getEvents();
	for(auto event=events.begin(); event!=events.end(); ++event){
		if(event->button.type == SDL_MOUSEBUTTONDOWN){
			auto x = this->player->getBody()->GetPosition().x;
			auto y = this->player->getBody()->GetPosition().y;
			this->getBody()->SetTransform(b2Vec2(x, y), this->getBody()->GetAngle());
			b2Vec2 target = b2Vec2(event->button.x, event->button.y);
			//Find a vector from our projectile to the player 
			b2Vec2 path = target - body->GetPosition();
			//Apply a force to get the projectile there
			path.Normalize();
			path *= 5.0f;
			body->ApplyForceToCenter(path, true);
		}
	}	
}

void Bullet::draw(SDL_Renderer* renderer){
	SDL_Rect dest;
	b2Vec2 pos = body->GetPosition();
	dest.x = pos.x * 100;
	dest.y = pos.y * -100;
	dest.w = rect.w;
	dest.h = rect.h;
	float angle = body->GetAngle();
	//std::cout << dest.x << ", " << dest.y << std::endl;
	int result = SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
	if(result != 0){
		std::cout << SDL_GetError() << std::endl;
	}
}

b2Body* Bullet::getBody(){
	return body;
}
