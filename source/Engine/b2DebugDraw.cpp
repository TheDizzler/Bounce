#include "../pch.h"
#include "b2DebugDraw.h"
#include "GameEngine.h"

b2DebugDraw::b2DebugDraw() {
}


b2DebugDraw::~b2DebugDraw() {
}

void b2DebugDraw::initialize(ComPtr<ID3D11Device> dev, ComPtr<ID3D11DeviceContext> devCon) {
	device = dev;
	deviceContext = devCon;
	states = make_unique<CommonStates>(device.Get());

	basicEffect = make_unique<BasicEffect>(device.Get());
	basicEffect->SetVertexColorEnabled(true);

	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	GameEngine::reportError(device->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength,
		inputLayout.GetAddressOf()), L"Error trying to create input layout in b2DebugDraw");


	basicEffect->SetView(camera.view);
	basicEffect->SetProjection(camera.projection);
	//basicEffect->EnableDefaultLighting();
	//basicEffect->SetDiffuseColor(Colors::Red);
	//basicEffect->SetTexture();


	pBatch = make_unique<PrimitiveBatch<VertexPositionColor>>(deviceContext.Get());
}

void b2DebugDraw::update(double deltaTime) {
	basicEffect->SetView(camera.view);
}

void b2DebugDraw::draw(b2World* world) {
	pBatch->Begin();
	//drawGrid();
	world->DrawDebugData();
	DrawSolidPolygon(goalVerts, 4, b2Color(1, 1, 0, 1));
	pBatch->End();
}

void b2DebugDraw::drawGrid() {

	size_t xdivs = std::max<size_t>(1, 100);
	size_t ydivs = std::max<size_t>(1, 100);

	for (size_t i = 0; i <= xdivs; ++i) {
		float percent = float(i) / float(xdivs);
		percent = (percent * 2.f) - 1.f;
		XMVECTOR scale = XMVectorScale(Vector3(10, 0, 0), percent);
		scale = XMVectorAdd(scale, Vector3::Zero);

		VertexPositionColor v1(XMVectorSubtract(scale, Vector3(0, 1, 0)), Colors::DarkSeaGreen);
		VertexPositionColor v2(XMVectorAdd(scale, Vector3(0, 1, 0)), Colors::DarkSeaGreen);
		pBatch->DrawLine(v1, v2);
	}

	for (size_t i = 0; i <= ydivs; i++) {
		FLOAT percent = float(i) / float(ydivs);
		percent = (percent * 2.f) - 1.f;
		XMVECTOR scale = XMVectorScale(Vector3(0, 10, 0), percent);
		scale = XMVectorAdd(scale, Vector3::Zero);

		VertexPositionColor v1(XMVectorSubtract(scale, Vector3(1, 0, 0)), Colors::DarkGoldenrod);
		VertexPositionColor v2(XMVectorAdd(scale, Vector3(1, 0, 0)), Colors::DarkGoldenrod);
		pBatch->DrawLine(v1, v2);
	}
}


void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());

	basicEffect->Apply(deviceContext.Get());

	deviceContext->IASetInputLayout(inputLayout.Get());

	VertexPositionColor* vpcs = new VertexPositionColor[vertexCount + 1];

	for (int i = 0; i < vertexCount; ++i) {
		XMStoreFloat3(&vpcs[i].position, Vector3(vertices[i].x, vertices[i].y, 0));
		XMStoreFloat4(&vpcs[i].color, Color(color.r, color.g, color.b, color.a));
	}
	XMStoreFloat3(&vpcs[vertexCount].position, Vector3(vertices[0].x, vertices[0].y, 0));
	XMStoreFloat4(&vpcs[vertexCount].color, Color(color.r, color.g, color.b, color.a));
	pBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, vpcs, vertexCount + 1);


	/*VertexPositionColor verts[4];
	XMStoreFloat3(&verts[0].position, Vector3(0.f, 0.5f, 0.5f));
	XMStoreFloat3(&verts[1].position, Vector3(0.5f, -0.5f, 0.5f));
	XMStoreFloat3(&verts[2].position, Vector3(-0.5f, -0.5f, 0.5f));
	XMStoreFloat3(&verts[3].position, Vector3(0.f, 0.5f, 0.5f));

	XMStoreFloat4(&verts[0].color, Colors::Yellow);
	XMStoreFloat4(&verts[1].color, Colors::Yellow);
	XMStoreFloat4(&verts[2].color, Colors::Yellow);
	XMStoreFloat4(&verts[3].color, Colors::Yellow);

	pBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 4);*/

}

void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());

	basicEffect->Apply(deviceContext.Get());

	VertexPositionColor* vpcs;
	vpcs = new VertexPositionColor[vertexCount];
	for (int i = 0; i < vertexCount; ++i) {

		vpcs[i] = VertexPositionColor(Vector2(vertices[i].x, vertices[i].y),
			Color(color.r, color.g, color.b, color.a));
	}

	pBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vpcs, vertexCount);
}

void b2DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());

}

void b2DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());
}

void b2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());
}

void b2DebugDraw::DrawTransform(const b2Transform& xf) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());
}

void b2DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());
}
