#ifndef		__H__ENEMY__
#define		__H__ENEMY__

#include "LEAGUE/common_data_structures.h"
#include "LEAGUE/physics.h"
#include <box2d/box2d.h>
#include "player.h"

class Enemy : public Drawable, public Updateable {
	public:
		Enemy(PhysicsWorld*, Player*);
		~Enemy();
		void draw(SDL_Renderer* renderer) override;
		void update(double delta) override;
		void setBody(b2Body*);
		b2BodyDef* getBodyDef();
		b2Body* getBody();
		void startContact();
		void endContact();
	private:
		int x_vel;
		int y_vel;
		b2Body* body;
		b2BodyDef* bodyDef;
		Player* player;
};

#endif
