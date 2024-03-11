#include "MyContactListener.h"
#include "userData.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

void MyContactListener::BeginContact(b2Contact* contact){
	CustomUserData* dataA = reinterpret_cast<CustomUserData*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CustomUserData* dataB = reinterpret_cast<CustomUserData*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if((dataA->type == 0 && dataB->type == 1) || (dataA->type == 1 && dataB->type == 0)){
		if(dataA->type == 0){
			((Player*)dataA->obj)->damage();
		}else{
			((Player*)dataB->obj)->damage();
		}
	}else if((dataA->type == 2 && dataB->type == 1) || (dataA->type == 1 && dataB->type == 2)){
		if(dataA->type == 2){
			((Enemy*)dataA->obj)->respawn();
			((Bullet*)dataB->obj)->remove();

		}else{
			((Bullet*)dataA->obj)->remove();
			((Enemy*)dataB->obj)->respawn();
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact){
	//contact->GetFixtureA()->GetBody()->GetUserData().pointer.endContact();
	//contact->GetFixtureB()->GetBody()->GetUserData().pointer.endContact();
}
