#pragma once

#include "Box2D.h"

#include "../../DXTKGui/BaseGraphics/screen.h"
#include "../Engine/b2DebugDraw.h"



class LevelScreen : public Screen {
public:
	LevelScreen();
	virtual ~LevelScreen();

	virtual bool initialize(ComPtr<ID3D11Device> device) override;
	virtual void setGameManager(GameManager* game) override;

	void reloadGraphicsAssets();

	virtual void update(double deltaTime) override;
	virtual void draw(SpriteBatch * batch) override;

	virtual void pause() override;

	virtual void controllerRemoved(ControllerSocketNumber controllerSlot, PlayerSlotNumber slotNumber) override;
	virtual void newController(shared_ptr<Joystick> newStick) override;

private:
	GameManager* gameManager;

	unique_ptr<b2World> world;
	unique_ptr<b2DebugDraw> debugDraw;

	double timeSinceLastStep = 0;
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	/* Never call delete or free on a body, fixture, or joint! Use world->DestroyBody() if needed. */
	b2Body* borderWall;
	b2Body* body;
};