#include "Ball.h"

Ball::Ball() {
}

Ball::~Ball() {
}

void Ball::load(b2World* world, GraphicsAsset* const graphicsAsset) {
	b2BodyDef knockerBodyDef;
	knockerBodyDef.type = b2_dynamicBody;
	knockerBodyDef.position.Set(-8.0f, 2.0f);
	knockerBodyDef.userData = this;
	body2b = world->CreateBody(&knockerBodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.26f, .26f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.6f;
	fixtureDef.friction = 0.3f;

	body2b->CreateFixture(&fixtureDef);
	

	//GameObject::load(graphicsAsset);
	scale = Vector2(100, 100);
	position = Vector2(body2b->GetPosition().x, body2b->GetPosition().y) * scale;
}

void Ball::update(double d) {
	position = Vector2(body2b->GetPosition().x, body2b->GetPosition().y);
}
