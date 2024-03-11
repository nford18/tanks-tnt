#include "mathfu/vector.h"
#include "enemy.h"
#include "player.h"
#include "LEAGUE/physics.h"
#include "LEAGUE/engine.h"
#include <iostream>
#include <string>
#include <box2d/box2d.h>
#include <random>

Enemy::Enemy(PhysicsWorld* physics, Player* player){
	this->player = player;
    	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> LR_distribution(0, 6);
	std::uniform_int_distribution<int> UD_distribution(1, 9);
    std::uniform_int_distribution<int> wall(0, 3);

	// Generate a random number between 0 and RAND_MAX
	loadImage("./assets/enemy_projectile.png");
	// Need a body definition before we can make a body
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
    	// pick the wall
    	int wallNumber = wall(gen);
   	switch(wallNumber){
        case 0: // top
            bodyDef->position.Set(UD_distribution(gen) , -1.5f);
        case 1: // left
            bodyDef->position.Set(1.5f, - LR_distribution(gen) - 0.8);
        case 2: // bottom
            bodyDef->position.Set(UD_distribution(gen) , -7.1f);
        case 3: // right
            bodyDef->position.Set(9.5f, - LR_distribution(gen) - 0.8);
    	} 
	//bodyDef->position.Set(distribution(gen) , - distribution(gen));
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

Enemy::~Enemy(){
	delete bodyDef;
}

void Enemy::setBody(b2Body* body){
	this->body = body;
}

b2BodyDef* Enemy::getBodyDef(){
	return bodyDef;
}

void Enemy::update(double delta){
	//std::cout << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
	auto events = Engine::getEvents();
	for(auto event=events.begin(); event!=events.end(); ++event){
		//Find the position of the player
		b2Vec2 target = this->player->getBody()->GetPosition();
		//Find a vector from our projectile to the player 
		b2Vec2 path = target - body->GetPosition();
		//Apply a force to get the projectile there
		path.Normalize();
		path *= 1.0f;
		body->ApplyForceToCenter(path, true);
	}	
}

void Enemy::draw(SDL_Renderer* renderer){
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

b2Body* Enemy::getBody(){
	return body;
}
