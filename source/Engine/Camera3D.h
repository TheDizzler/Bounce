#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
//using namespace DirectX::SimpleMath;


class Camera3D {
public:

	Camera3D();
	virtual ~Camera3D();

	//void initViewMatrix(D3D11_VIEWPORT cameraViewport);
	void init(D3D11_VIEWPORT cameraViewport, float fovY, float zn, float zf);

	void forward(double d);
	void strafe(double d);
	void pitch(double angle);
	void rotateY(double angle);

	/*void move(Vector3 direction);
	void rotate(Vector3 axis, float radians);*/

	void update(double deltaTime);

	Matrix getTransformMatrix() const;

	float getFovX() const;
	float getNearWindowWidth() const;
	float getNearWindowHeight() const;
	float getFarWindowWidth() const;
	float getFarWindowHeight() const;

	Matrix world;
	Matrix view;
	Matrix projection;

	D3D11_VIEWPORT viewport;
	float fieldOfViewY;
	float aspectRatio;
	float nearZ;
	float farZ;
	float nearWindowHeight;
	float farWindowHeight;

	Vector3 position, look, up, right;

	/*float camYaw = 0;
	float camPitch = 0;*/

	/*Vector3 camRight = Vector3::UnitX;
	Vector3 camForward = Vector3::UnitZ;
	*/

//	Camera3D();
//	virtual ~Camera3D();
//
//	void initProjMatrix(D3D11_VIEWPORT cameraViewport,
//		float newNearest, float newFarthest, float cameraAngle = 0.0f);
//
//	/* Get camera's up vector */
//	const XMFLOAT3 getUp() {
//		XMFLOAT3 val;
//		DirectX::XMStoreFloat3(&val, XMLoadFloat3(&up) - XMLoadFloat3(&position));
//		return val;
//	}
//	/* Change camera target position */
//	void setTarget(XMFLOAT3 newTarget);
//	/* Get camera's target position coordinates */
//	const XMFLOAT3& getTarget() const {
//		return target;
//	}
//	/* Get camera's look at target vector */
//	const XMFLOAT3 getLookAtTarget() {
//		XMFLOAT3 val;
//		DirectX::XMStoreFloat3(&val, XMLoadFloat3(&target) - XMLoadFloat3(&position));
//		return val;
//	}
//	/* Returns transposed camera's View matrix */
//	const XMFLOAT4X4 getView() {
//		XMFLOAT4X4 val;
//		XMStoreFloat4x4(&val, XMMatrixTranspose(XMLoadFloat4x4(&view)));
//		return val;
//	}
//
//	/* Returns transposed camera's Projection matrix */
//	const XMFLOAT4X4 getProj() {
//		XMFLOAT4X4 val;
//		XMStoreFloat4x4(&val, XMMatrixTranspose(XMLoadFloat4x4(&projection)));
//		return val;
//	}
//
//	/* Returns transposed orthogonal camera matrix */
//	const XMFLOAT4X4 getOrtho() {
//		XMFLOAT4X4 val;
//		XMStoreFloat4x4(&val, XMMatrixTranspose(XMLoadFloat4x4(&ortho)));
//		return val;
//	}
//
//	/* Get world coordinates of camera. */
//	const XMFLOAT3& getPosition() const;
//
//	/* Amount screen has moved since last update. RETURNS ZEROED VECTOR3! */
//	const Vector3& getDelta() const;
//
//
//	void move(XMFLOAT3 direction);
//	/* Rotate camera around `axis` by `degrees`. Camera's position is a
//		pivot point of rotation, so it doesn't change */
//	void rotate(XMFLOAT3 axis, float degrees);
//	void setPosition(XMFLOAT3& newPosition);
//	void setAngle(float angle);
//	void setNearestPlane(float nearest);
//	void setFarthestPlane(float farthest);
//
//
//	//Matrix translationMatrix();
//	Vector3 worldToScreen(Vector3 worldPosition);
//	Vector3 screenToWorld(Vector2 screenPosition);
//
//public:
//	Matrix world;
//	XMFLOAT4X4 view;
//	XMFLOAT4X4 projection, ortho;
//private:
//
//	XMFLOAT3 position, target, up;
//	float angle;
//	float nearest;
//	float farthest;
//
//	
//	//Vector3 viewportCenter;
//
//	void initViewMatrix();
//	void initOrthoMatrix();
//	void onResize(D3D11_VIEWPORT viewport);
};