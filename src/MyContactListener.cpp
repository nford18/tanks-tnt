#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact){
	contact->GetFixtureA()->GetBody()->GetUserData().pointer.startContact();
	//contact->GetFixtureB()->GetBody()->GetUserData().pointer.startContact();
}

void MyContactListener::EndContact(b2Contact* contact){
	//contact->GetFixtureA()->GetBody()->GetUserData().pointer.endContact();
	//contact->GetFixtureB()->GetBody()->GetUserData().pointer.endContact();
}
