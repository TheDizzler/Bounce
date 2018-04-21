#include "../pch.h"
#include "LevelScreen.h"
#include "../Engine/GameEngine.h"



LevelScreen::LevelScreen() {
}

LevelScreen::~LevelScreen() {
}

Vector2 arenaCenter = Vector2::Zero;
bool LevelScreen::initialize(ComPtr<ID3D11Device> device) {
	
	camera.centerOn(arenaCenter);
	
	/** Create Physics World */
	b2Vec2 gravity(0.0f, 0.0f); // this is a top-down perspective, therefore, no gravity as such
	world = make_unique<b2World>(gravity);
	debugDraw = make_unique<b2DebugDraw>(device, gameManager->getDeviceContext());
	world->SetDebugDraw(debugDraw.get());

	/** Create Ground Box i.e. Border Walls*/
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(-20.0, 0.0f);
	borderWall = world->CreateBody(&groundBodyDef);

	b2PolygonShape borderBox;
	borderBox.SetAsBox(5.5f, 50.0f);

	borderWall->CreateFixture(&borderBox, 0.0f);


	/* **** Create dynamic objects **** */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	return true;
}


void LevelScreen::setGameManager(GameManager* g) {
	gameManager = g;
}

void LevelScreen::reloadGraphicsAssets() {
}

void LevelScreen::update(double deltaTime) {

	int scrollDelta = mouse.scrollWheelValue();
	if (scrollDelta) {
		camera.adjustZoom(scrollDelta * deltaTime * 50);
	}

	timeSinceLastStep += deltaTime;
	if (timeSinceLastStep >= timeStep) {
		world->Step(timeStep, velocityIterations, positionIterations);
		timeSinceLastStep = 0;
	}

}

void LevelScreen::draw(SpriteBatch* batch) {

	//world->DrawDebugData();
	debugDraw->draw(world.get());
}

void LevelScreen::pause() {
}

void LevelScreen::controllerRemoved(ControllerSocketNumber controllerSlot, PlayerSlotNumber slotNumber) {
}

void LevelScreen::newController(shared_ptr<Joystick> newStick) {
}
