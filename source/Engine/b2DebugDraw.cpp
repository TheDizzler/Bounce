#include "../pch.h"
#include "b2DebugDraw.h"
#include "GameEngine.h"

b2DebugDraw::b2DebugDraw(ComPtr<ID3D11Device> dev, ComPtr<ID3D11DeviceContext> devCon) {

	device = dev;
	deviceContext = devCon;
	states = make_unique<CommonStates>(device.Get());

	basicEffect = make_unique<BasicEffect>(device.Get());
	basicEffect->SetVertexColorEnabled(true);
	//basicEffect->EnableDefaultLighting();
	basicEffect->SetDiffuseColor(Colors::Red);
	//basicEffect->SetTexture();

	void const* shaderByteCode;
	size_t byteCodeLength;
	basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	GameEngine::reportError(device->CreateInputLayout(VertexPositionColor::InputElements,
		VertexPositionColor::InputElementCount, shaderByteCode, byteCodeLength,
		inputLayout.GetAddressOf()), L"Error trying to create input layout in b2DebugDraw");

	pBatch = make_unique<PrimitiveBatch<VertexPositionColor>>(deviceContext.Get());
}

b2DebugDraw::~b2DebugDraw() {
}

void b2DebugDraw::draw(b2World* world) {
	pBatch->Begin();
	world->DrawDebugData();
	pBatch->End();
}


void b2DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {

	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());

	basicEffect->Apply(deviceContext.Get());



	//vector<VertexPositionColor> vpcs;
	VertexPositionColor* vpcs;
	vpcs = new VertexPositionColor[vertexCount];
	for (int i = 0; i < vertexCount; ++i) {

		vpcs[i] = VertexPositionColor(Vector2(vertices[i].x, vertices[i].y), Colors::Fuchsia);
	}
	pBatch->Draw(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vpcs, vertexCount);


}

void b2DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	deviceContext->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	deviceContext->OMSetDepthStencilState(states->DepthNone(), 0);
	deviceContext->RSSetState(states->CullNone());

	basicEffect->Apply(deviceContext.Get());


	//vector<VertexPositionColor> vpcs;
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
