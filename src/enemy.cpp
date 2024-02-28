#include "mathfu/vector.h"
#include "enemy.h"
#include "LEAGUE/physics.h"
#include "LEAGUE/engine.h"
#include <iostream>
#include <string>
#include <box2d/box2d.h>
#include <random>

Enemy::Enemy(PhysicsWorld* physics, Player* player){
    std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, 10);
    std::uniform_int_distribution<int> wall(0, 3);

	// Generate a random number between 0 and RAND_MAX
	loadImage("./assets/enemy_projectile.png");
	// Need a body definition before we can make a body
	bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
    // pick the wall
    int wallNumber = wall(gen);
    switch(wallNumber){
        case 0:
            bodyDef->position.Set(distribution(gen) , -1);
        case 1:
            bodyDef->position.Set(1, - distribution(gen));
        case 2:
            bodyDef->position.Set(distribution(gen) , -8);
        case 3:
            bodyDef->position.Set(8, - distribution(gen));
    } 
	bodyDef->position.Set(distribution(gen) , - distribution(gen));
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

Player::~Player(){
	delete bodyDef;
}

void Player::setBody(b2Body* body){
	this->body = body;
}

b2BodyDef* Player::getBodyDef(){
	return bodyDef;
}

void Player::update(double delta){
	//std::cout << body->GetPosition().x << ", " << body->GetPosition().y << std::endl;
	auto events = Engine::getEvents();
	for(auto event=events.begin(); event!=events.end(); ++event){
		if(event->key.state == SDL_PRESSED){
			wDown = event->key.keysym.sym == SDLK_w;
			aDown = event->key.keysym.sym == SDLK_a;
			sDown = event->key.keysym.sym == SDLK_s;
			dDown = event->key.keysym.sym == SDLK_d;
		}
		if(event->key.state == SDL_RELEASED){
			if(event->key.keysym.sym == SDLK_w){
				wDown = false;
			}
			if(event->key.keysym.sym == SDLK_a){
				aDown = false;
			}
			if(event->key.keysym.sym == SDLK_s){
				sDown = false;
			}
			if(event->key.keysym.sym == SDLK_d){
				dDown = false;
			}
		}
		// update velocity
		std::cout << wDown << ", " << aDown << ", " << sDown << ", " << dDown << std::endl;
		b2Vec2 force;
		
		if(wDown){
			force = b2Vec2(0.0f, 0.01f);
		}else if(aDown){
			force = b2Vec2(-0.01f, 0.0f);
		}else if(sDown){
			force = b2Vec2(0.0f, -0.01f);
		}else if(dDown){
			force = b2Vec2(0.01f, 0.0f);
		}else{
			force = b2Vec2(0.0f, 0.0f);
			body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}
		
		
		// b2Vec2 pos = body->GetPosition();
		// pos.x += 0.1;
		body->ApplyLinearImpulseToCenter(force, true);
		body->SetAngularVelocity(0.0f);

	}	
}

void Player::draw(SDL_Renderer* renderer){
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

b2Body* Player::getBody(){
	return body;
}