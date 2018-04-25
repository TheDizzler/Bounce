#include "LevelScreen.h"
#include "../Engine/GameEngine.h"


LevelScreen::LevelScreen() {
}

LevelScreen::~LevelScreen() {
}

Vector3 arenaCenter = Vector3::Zero;
bool LevelScreen::initialize(ComPtr<ID3D11Device> device) {

	//camera.centerOn(arenaCenter);

	/** Create Physics World */
	b2Vec2 gravity(0.0f, -10.0f); // this is a top-down perspective, therefore, no gravity as such
	world = make_unique<b2World>(gravity);
	debugDraw.initialize(device, gameManager->getDeviceContext());
	world->SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);

	/** Create Ground Box i.e. Border Walls*/
	b2BodyDef borderWallBodyDef;
	borderWallBodyDef.position.Set(-10.0f, 0.0f);
	borderWall = world->CreateBody(&borderWallBodyDef);
	b2PolygonShape wallShape;
	wallShape.SetAsBox(1.0f, 5.0f);
	borderWall->CreateFixture(&wallShape, 0.0f);

	borderWallBodyDef.position.Set(10.0f, 0);
	borderWall = world->CreateBody(&borderWallBodyDef);
	wallShape.SetAsBox(1.0f, 5.0f);
	borderWall->CreateFixture(&wallShape, 0.0f);

	borderWallBodyDef.position.Set(0.0f, 5.0f);
	borderWall = world->CreateBody(&borderWallBodyDef);
	wallShape.SetAsBox(10.0f, 1.0f);
	borderWall->CreateFixture(&wallShape, 0.0f);

	borderWallBodyDef.position.Set(0.0f, -5.0f);
	borderWall = world->CreateBody(&borderWallBodyDef);
	wallShape.SetAsBox(10.0f, 1.0f);
	borderWall->CreateFixture(&wallShape, 0.0f);

	///* **** Create dynamic objects **** */
	//bouncer = new Bouncer();
	ball.load(world.get(), assMan.getAsset("ball"));

	knockerL.load(world.get(), assMan.getAsset("knocker"));


	goal.reset(guiFactory.createRectangleFrame(Vector2(4, 0), Vector2(4, 4), 1, Color(Colors::Yellow)));
	
	debugDraw.goalVerts[0] = b2Vec2(4, 0);
	debugDraw.goalVerts[1] = b2Vec2(8, 0);
	debugDraw.goalVerts[2] = b2Vec2(8, 4);
	debugDraw.goalVerts[3] = b2Vec2(4, 4);

	while (sizeof(slotManager.playerSlots) / sizeof(slotManager.playerSlots[0]) < 1) {
		int x = 1;

	}

	knockerL.assignSlot(slotManager.playerSlots[0].get());

	return true;
}


void LevelScreen::setGameManager(GameManager* g) {
	gameManager = g;
}

void LevelScreen::reloadGraphicsAssets() {
}

void LevelScreen::update(double deltaTime) {

	/*int scrollDelta = mouse.scrollWheelValue();
	if (scrollDelta) {
		camera.rotate(Vector3::UnitX, scrollDelta * deltaTime * 1000);
	}*/

	if (mouse.leftButton()) {
		Vector2 mousePos = mouse.getPosition();
		Vector2 lastPos = mouse.getLastPosition();
		float dx = XMConvertToRadians(.25f * static_cast<float>(mousePos.x - lastPos.x));
		float dy = XMConvertToRadians(.25f * static_cast<float>(mousePos.y - lastPos.y));

		camera.pitch(dy);
		camera.rotateY(-dx);
	}

	if (keys.keyState.S) {
		camera.forward(10 * deltaTime);
	} else if (keys.keyState.W) {
		camera.forward(-10 * deltaTime);
	}
	if (keys.keyState.A) {
		camera.strafe(-10 * deltaTime);
	} else if (keys.keyState.D) {
		camera.strafe(10 * deltaTime);
	}
	camera.update(deltaTime);
	knockerL.update(deltaTime);
	ball.update(deltaTime);

	if (goal->contains(ball.getPosition())) {
		int x = 1;
	}

	timeSinceLastStep += deltaTime;
	if (timeSinceLastStep >= timeStep) {
		world->Step(timeStep, velocityIterations, positionIterations);
		timeSinceLastStep = 0;
		/*wostringstream ws;
		ws << "Body count: " << world->GetBodyCount() << "\n";
		OutputDebugString(ws.str().c_str());*/
	}
	debugDraw.update(deltaTime);


}

void LevelScreen::draw(SpriteBatch* batch) {
	debugDraw.draw(world.get());
	
	knockerL.draw(batch);
}

void LevelScreen::pause() {
}

void LevelScreen::controllerRemoved(ControllerSocketNumber controllerSlot, PlayerSlotNumber slotNumber) {
}

void LevelScreen::newController(shared_ptr<Joystick> newStick) {
	knockerL.assignSlot(slotManager.playerSlots[newStick->getPlayerSlotNumber()].get());
}
