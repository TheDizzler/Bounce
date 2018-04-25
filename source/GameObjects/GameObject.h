#pragma once

#include "Box2D.h"
#include "../../DXTKGui/BaseGraphics/GraphicsAsset.h"

/* A game object with Box2D and IElement2D properties. */
class GameObject : public IElement2D {
public:
	GameObject();
	virtual ~GameObject();

	virtual void draw(SpriteBatch* batch) override;
	virtual void update(double dt) = 0;

	virtual const Vector2& getPosition() const override;
	virtual const Vector2& getOrigin() const override;
	virtual const Vector2& getScale() const override;
	virtual const float getRotation() const override;
	virtual const Color& getTint() const override;
	virtual const float getAlpha() const override;
	virtual const int getWidth() const override;
	virtual const int getHeight() const override;
	virtual const float getLayerDepth() const override;

	virtual void moveBy(const Vector2& moveVector) override;
	virtual void rotateBy(const float rotateBy);

	virtual void setPosition(const Vector2& position) override;
	virtual void setOrigin(const Vector2& origin) override;
	virtual void setScale(const Vector2& scale) override;
	virtual void setRotation(const float rotation) override;
	virtual void setTint(const XMFLOAT4 color) override;
	virtual void setTint(const Color& color) override;
	virtual void setTint(const XMVECTORF32 color) override;
	virtual void setAlpha(const float alpha) override;
	virtual void setLayerDepth(const float depth, bool frontToBack = true) override;

	virtual bool contains(const Vector2 & point) override;

protected:
	b2Body* body2b;

	/* GraphicsAsset is not stored in Sprite.*/
	virtual void load(GraphicsAsset* const graphicsAsset);
	string assetName;
	ComPtr<ID3D11ShaderResourceView> texture;

	RECT sourceRect;

	Vector2 origin;
	Color tint;
	float rotation;
	float layerDepth;

	UINT width;
	UINT height;
	Vector2 position;
	Vector2 scale;
	SpriteEffects spriteEffect = SpriteEffects_None;
};