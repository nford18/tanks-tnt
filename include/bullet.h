#ifndef		__H__BULLET__
#define		__H__BULLET__

#include "LEAGUE/common_data_structures.h"
#include "LEAGUE/physics.h"
#include <box2d/box2d.h>
#include "player.h"

class Bullet : public Drawable, public Updateable {
	public:
		Bullet(PhysicsWorld*, Player*);
		~Bullet();
		void draw(SDL_Renderer* renderer) override;
		void update(double delta) override;
		void setBody(b2Body*);
		b2BodyDef* getBodyDef();
		b2Body* getBody();
	private:
		int x_vel;
		int y_vel;
		b2Body* body;
		b2BodyDef* bodyDef;
		Player* player;
};

#endif
