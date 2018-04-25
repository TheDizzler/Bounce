#pragma once

#include "GameObject.h"
#include "../Engine/PlayerSlot.h"

/* The player object. Knocks things. */
class Knocker : public GameObject {
public:
	
	virtual ~Knocker();

	virtual void load(b2World* world, GraphicsAsset* const graphicsAsset);

	void assignSlot(PlayerSlot* playerSlot);

	virtual void update(double d) override;
private:
	
	PlayerSlot* slot;
	Joystick* joystick;

	
};