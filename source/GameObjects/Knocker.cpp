#include "Knocker.h"

Knocker::~Knocker() {
	
}

void Knocker::load(b2World* world, GraphicsAsset* const graphicsAsset) {

	b2BodyDef knockerBodyDef;
	knockerBodyDef.type = b2_dynamicBody;
	knockerBodyDef.position.Set(-8.0f, 0.0f);
	knockerBodyDef.userData = this;
	body2b = world->CreateBody(&knockerBodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.26f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.3f;

	body2b->CreateFixture(&fixtureDef);
	body2b->SetGravityScale(0);

	GameObject::load(graphicsAsset);
	position = Vector2(body2b->GetPosition().x, body2b->GetPosition().y);

}

void Knocker::assignSlot(PlayerSlot* playerSlot) {
	slot = playerSlot;
	joystick = slot->getStick();
}

void Knocker::update(double d) {
	Vector2 dir = joystick->getDirection();
	moveBy(dir *d * 500);

	if(joystick->lButtonDown()) {
		rotateBy(d * 500);
	}
	if (joystick->rButtonDown()) {
		rotateBy(d * -500);
	}
		//if (joystick->startButtonPushed()) {


	position = Vector2(body2b->GetPosition().x, body2b->GetPosition().y);
}
