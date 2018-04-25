#pragma once

#include "VertexTypes.h"
#include "Box2D.h"
//#include "GameEngine.h"
#include "PrimitiveBatch.h"
#include "CommonStates.h"
#include "Effects.h"

class b2DebugDraw : public b2Draw {
public:
	b2DebugDraw();
	virtual ~b2DebugDraw();

	void initialize(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);

	void update(double deltaTime);
	void draw(b2World* world);

	void drawGrid();

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
	virtual void DrawTransform(const b2Transform& xf) override;
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

	b2Vec2 goalVerts[4];
private:
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<ID3D11InputLayout> inputLayout;

	unique_ptr<CommonStates> states;
	unique_ptr<BasicEffect> basicEffect;
	unique_ptr<PrimitiveBatch<VertexPositionColor>> pBatch;

};