#pragma once

#include "GameObject.h"

class Ball : public GameObject {
public:
	Ball();
	virtual ~Ball();

	virtual void load(b2World* world, GraphicsAsset* const graphicsAsset);

	virtual void update(double d) override;

private:


};