#include "GameObject.h"


GameObject::GameObject() {
	rotation = 0.0f;
	scale = Vector2(1, 1);
	tint = DirectX::Colors::White;
	layerDepth = 0.1f;

	width = 0;
	height = 0;
}

GameObject::~GameObject() {
	if (body2b != NULL) {
		body2b->SetUserData(NULL);
		body2b = NULL;
	}
}

void GameObject::load(GraphicsAsset* const graphicsAsset) {


	assetName = graphicsAsset->assetName;
	texture = graphicsAsset->getTexture();
	width = graphicsAsset->getWidth();
	height = graphicsAsset->getHeight();

	origin = graphicsAsset->getOrigin();

	sourceRect = graphicsAsset->getSourceRect();
}

void GameObject::draw(SpriteBatch* batch) {
	/*batch->Draw(texture.Get(), position, &sourceRect, tint, rotation,
		origin, scale, spriteEffect, layerDepth);*/
}


const Vector2& GameObject::getPosition() const {
	
	return position;
}

const Vector2& GameObject::getOrigin() const {
	return origin;
}

const Vector2& GameObject::getScale() const {
	return scale;
}

const float GameObject::getRotation() const {
	return rotation;
}

const Color& GameObject::getTint() const {
	return tint;
}

const float GameObject::getAlpha() const {
	return tint.w;
}

const int GameObject::getWidth() const {
	return width;
}

const int GameObject::getHeight() const {
	return height;
}

const float GameObject::getLayerDepth() const {
	return layerDepth;
}

void GameObject::moveBy(const Vector2& moveVector) {
	//position += moveVector;
	body2b->ApplyForceToCenter(b2Vec2(moveVector.x, -moveVector.y), true);
	position = Vector2(body2b->GetPosition().x, body2b->GetPosition().y) * scale;
}

void GameObject::rotateBy(const float rotateBy) {
	body2b->ApplyTorque(rotateBy, true);
	rotation = body2b->GetAngle();
}

void GameObject::setPosition(const Vector2& pos) {
	position = pos;
}

void GameObject::setOrigin(const Vector2& org) {
	origin = org;
}

void GameObject::setScale(const Vector2& scl) {
	scale = scl;
}

void GameObject::setRotation(const float rot) {
	rotation = rot;
}

void GameObject::setTint(const XMFLOAT4 color) {
	tint = color;
}

void GameObject::setTint(const Color& color) {
	tint = color;
}

void GameObject::setTint(const XMVECTORF32 color) {
	tint = color;
}

void GameObject::setAlpha(const float alpha) {
	tint.w = alpha;
}

void GameObject::setLayerDepth(const float depth, bool frontToBack) {
	layerDepth = depth;
}

bool GameObject::contains(const Vector2& point) {
	return false;
}