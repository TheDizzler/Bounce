#include "../pch.h"
#include "Camera3D.h"


Camera3D::Camera3D() {

	position = Vector3(0.0f, 0.0f, 25.0f);
	look = Vector3(0, 0, 1);
	up = Vector3(0, 1, 0);
	right = Vector3(1, 0, 0);

	world = Matrix::Identity;
}

Camera3D::~Camera3D() {
}


void Camera3D::init(D3D11_VIEWPORT cameraViewport, float fovY, float zn, float zf) {

	viewport = cameraViewport;

	fieldOfViewY = fovY;
	aspectRatio = viewport.Width / viewport.Height;
	nearZ = zn;
	farZ = zf;

	nearWindowHeight = 2.0f * nearZ * tanf(.5f * fieldOfViewY);
	farWindowHeight = 2.0f * farZ * tanf(.5f * fieldOfViewY);

	projection = Matrix::CreatePerspectiveFieldOfView(fieldOfViewY, aspectRatio, nearZ, farZ);
}

void Camera3D::forward(double d) {

	Vector3 s = XMVectorReplicate(d);
	position = XMVectorMultiplyAdd(s, look, position);
}

void Camera3D::strafe(double d) {
	Vector3 s = XMVectorReplicate(d);
	position = XMVectorMultiplyAdd(s, right, position);
}

void Camera3D::pitch(double angle) {
	Matrix r = XMMatrixRotationAxis(right, angle);
	up = XMVector3TransformNormal(up, r);
	look = XMVector3TransformNormal(look, r);
}

void Camera3D::rotateY(double angle) {
	Matrix r = XMMatrixRotationY(angle);
	right = XMVector3TransformNormal(right, r);
	up = XMVector3TransformNormal(up, r);
	look = XMVector3TransformNormal(look, r);
}

void Camera3D::update(double deltaTime) {
	look.Normalize();
	up = XMVector3Cross(look, right);
	//up.Cross(look, right);
	up.Normalize();

	right = XMVector3Cross(up, look);

	//view = Matrix::CreateLookAt(position, look, up);

	float x = -XMVectorGetX(XMVector3Dot(position, right));
	float y = -XMVectorGetX(XMVector3Dot(position, up));
	float z = -XMVectorGetX(XMVector3Dot(position, look));

	view(0, 0) = right.x;
	view(1, 0) = right.y;
	view(2, 0) = right.z;
	view(3, 0) = x;

	view(0, 1) = up.x;
	view(1, 1) = up.y;
	view(2, 1) = up.z;
	view(3, 1) = y;

	view(0, 2) = look.x;
	view(1, 2) = look.y;
	view(2, 2) = look.z;
	view(3, 2) = z;

	view(0, 3) = 0.0f;
	view(1, 3) = 0.0f;
	view(2, 3) = 0.0f;
	view(3, 3) = 1.0f;

}

Matrix Camera3D::getTransformMatrix() const {
		// casting to int prevents filtering artifacts??
	return Matrix::CreateTranslation(-(int) position.x, -(int) position.y, (int) -(int) 0)
		* Matrix::CreateScale(position.z / 100)
		* Matrix::CreateTranslation(viewport.Width *.5, viewport.Height *.5, 0);
		//* Matrix::CreateRotationZ(rotation)
	/*return
		view.Invert()
		* Matrix::CreateTranslation(viewport.Width *.5, viewport.Height *.5, 1);*/
}



float Camera3D::getFovX() const {
	float halfWidth = .5f * getNearWindowWidth();
	return 2 * atan(halfWidth / nearZ);
}

float Camera3D::getNearWindowWidth() const {
	return aspectRatio * nearWindowHeight;
}

float Camera3D::getNearWindowHeight() const {
	return nearWindowHeight;
}

float Camera3D::getFarWindowWidth() const {
	return aspectRatio * farWindowHeight;
}

float Camera3D::getFarWindowHeight() const {
	return farWindowHeight;
}



//void Camera3D::move(Vector3 direction) {
//
//	position += direction;
//	target += direction;
//}


//void Camera3D::rotate(Vector3 axis, float radians) {
//	if (axis == Vector3::Zero || radians == 0.0f)
//		return;
//
//	camYaw += radians;
//
//	Matrix camRotation = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
//	target = XMVector3Transform(Vector3::UnitZ, camRotation);
//	target = XMVector3Normalize(target);
//
//	XMMATRIX RotateYTempMatrix;
//	RotateYTempMatrix = XMMatrixRotationY(camYaw);
//
//	camRight = XMVector3TransformCoord(Vector3::UnitX, RotateYTempMatrix);
//	up = XMVector3TransformCoord(up, RotateYTempMatrix);
//	camForward = XMVector3TransformCoord(Vector3::UnitZ, RotateYTempMatrix);
//
//}


//void Camera3D::update(double deltaTime) {
//
//	/*Matrix camRotation = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
//	target = XMVector3TransformCoord(Vector3::UnitZ, camRotation);
//	target = XMVector3Normalize(target);*/
//
//	/*XMMATRIX RotateYTempMatrix;
//	RotateYTempMatrix = XMMatrixRotationY(camYaw);
//
//	camRight = XMVector3TransformCoord(Vector3::UnitX, RotateYTempMatrix);
//	up = XMVector3TransformCoord(up, RotateYTempMatrix);
//	camForward = XMVector3TransformCoord(Vector3::UnitZ, RotateYTempMatrix);*/
//
//	//position += moveLeftRight*camRight;
//	//position += moveBackForward*camForward;
//
//	//moveLeftRight = 0.0f;
//	//moveBackForward = 0.0f;
//
//	//target = position + target;
//
//	view = Matrix::CreateLookAt(position, target, up);
//}













//
//Camera3D::Camera3D() {
//
//	world = Matrix::Identity;
//
//	position = XMFLOAT3(0.0f, 0.0f, -1.0f);
//	target = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	DirectX::XMStoreFloat3(&up, XMLoadFloat3(&position) + XMLoadFloat3(&XMFLOAT3(0, 1, 0)));
//
//	// init view matrix
//	initViewMatrix();
//
//	angle = 0.0f;
//
//	XMStoreFloat4x4(&view, XMMatrixIdentity());
//	XMStoreFloat4x4(&projection, XMMatrixIdentity());
//	XMStoreFloat4x4(&ortho, XMMatrixIdentity());
//
//	//projection = Matrix::CreatePerspectiveFieldOfView(
//	//	XM_PIDIV4, Globals::WINDOW_WIDTH / Globals::WINDOW_HEIGHT, 0.01f, 100.0f);
//}
//
//

//
//
//
//void Camera3D::initProjMatrix(D3D11_VIEWPORT cameraViewport,
//	float newNearest, float newFarthest, float cameraAngle) {
//
//	viewport = cameraViewport;
//	angle = cameraAngle;
//	nearest = newNearest;
//	farthest = newFarthest;
//	XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(angle, viewport.Width / viewport.Height,
//		nearest, farthest));
//}
//
//void Camera3D::setTarget(XMFLOAT3 newTarget) {
//	if (XMVector3Equal(XMLoadFloat3(&newTarget), XMLoadFloat3(&position)) ||
//		XMVector3Equal(XMLoadFloat3(&newTarget), XMLoadFloat3(&target)))
//		return;
//	XMFLOAT3 oldLookAtTarget;
//	DirectX::XMStoreFloat3(&oldLookAtTarget, XMLoadFloat3(&target) - XMLoadFloat3(&position));
//	XMFLOAT3 newLookAtTarget;
//	DirectX::XMStoreFloat3(&newLookAtTarget, XMLoadFloat3(&newTarget) - XMLoadFloat3(&position));
//	float angle = XMConvertToDegrees(XMVectorGetX(
//		XMVector3AngleBetweenNormals(XMVector3Normalize(XMLoadFloat3(&oldLookAtTarget)),
//			XMVector3Normalize(XMLoadFloat3(&newLookAtTarget)))));
//	if (angle != 0.0f && angle != 360.0f && angle != 180.0f) {
//		XMVECTOR axis = XMVector3Cross(XMLoadFloat3(&oldLookAtTarget), XMLoadFloat3(&newLookAtTarget));
//		XMFLOAT3 val;
//		DirectX::XMStoreFloat3(&val, axis);
//		rotate(val, angle);
//	}
//	target = newTarget;
//	initViewMatrix();
//}
//
//
//
//void Camera3D::move(XMFLOAT3 direction) {
//	DirectX::XMStoreFloat3(&position, XMVector3Transform(XMLoadFloat3(&position),
//		XMMatrixTranslation(direction.x, direction.y, direction.z)));
//	DirectX::XMStoreFloat3(&target, XMVector3Transform(XMLoadFloat3(&target),
//		XMMatrixTranslation(direction.x, direction.y, direction.z)));
//	DirectX::XMStoreFloat3(&up, XMVector3Transform(XMLoadFloat3(&up),
//		XMMatrixTranslation(direction.x, direction.y, direction.z)));
//	initViewMatrix();
//}
//
//void Camera3D::rotate(XMFLOAT3 axis, float degrees) {
//	if (XMVector3Equal(XMLoadFloat3(&axis), XMVectorZero()) ||
//		degrees == 0.0f)
//		return;
//	// rotate vectors
//	XMFLOAT3 lookAtTarget;
//	DirectX::XMStoreFloat3(&lookAtTarget, XMLoadFloat3(&target) - XMLoadFloat3(&position));
//	XMFLOAT3 lookAtUp;
//	DirectX::XMStoreFloat3(&lookAtUp, XMLoadFloat3(&up) - XMLoadFloat3(&position));
//	DirectX::XMStoreFloat3(&lookAtTarget, XMVector3Transform(XMLoadFloat3(&lookAtTarget),
//		XMMatrixRotationAxis(XMLoadFloat3(&axis), XMConvertToRadians(degrees))));
//	DirectX::XMStoreFloat3(&lookAtUp, XMVector3Transform(XMLoadFloat3(&lookAtUp),
//		XMMatrixRotationAxis(XMLoadFloat3(&axis), XMConvertToRadians(degrees))));
//	// restore vectors's end points mTarget and mUp from new rotated vectors
//	DirectX::XMStoreFloat3(&target, XMLoadFloat3(&position) + XMLoadFloat3(&lookAtTarget));
//	DirectX::XMStoreFloat3(&up, XMLoadFloat3(&position) + XMLoadFloat3(&lookAtUp));
//	initViewMatrix();
//}
//
//void Camera3D::setPosition(XMFLOAT3& newPosition) {
//	XMFLOAT3 moveVector;
//	XMStoreFloat3(&moveVector, XMLoadFloat3(&newPosition) - XMLoadFloat3(&position));
//	XMFLOAT3 newtarget = target;
//	move(moveVector);
//	setTarget(newtarget);
//}
//
//void Camera3D::setAngle(float newAngle) {
//	initProjMatrix(viewport, nearest, farthest, newAngle);
//}
//
//void Camera3D::setNearestPlane(float newNearest) {
//	nearest = newNearest;
//	onResize(viewport);
//}
//
//void Camera3D::setFarthestPlane(float newFarthest) {
//	farthest = newFarthest;
//	onResize(viewport);
//}
//
//const XMFLOAT3& Camera3D::getPosition() const {
//	return position;
//}
//
//const Vector3& Camera3D::getDelta() const {
//	return Vector3::Zero;
//}
//
//
//
////Vector3 Camera3D::worldToScreen(Vector3 worldPosition) {
////	return Vector3::Transform(worldPosition, translationMatrix());
////}
////
////Vector3 Camera3D::screenToWorld(Vector2 screenPosition) {
////	return Vector3::Transform(Vector3(screenPosition), translationMatrix().Invert());
////}
//
//void Camera3D::initViewMatrix() {
//	XMStoreFloat4x4(&view, XMMatrixLookAtLH(XMLoadFloat3(&position), XMLoadFloat3(&target),
//		XMLoadFloat3(&getUp())));
//}
//
//void Camera3D::initOrthoMatrix() {
//	XMStoreFloat4x4(&ortho, XMMatrixOrthographicLH(
//		viewport.Width, viewport.Height, 0.0f, farthest));
//}
//
//void Camera3D::onResize(D3D11_VIEWPORT newViewport) {
//	viewport = newViewport;
//	initProjMatrix(viewport, nearest, farthest, angle);
//	initOrthoMatrix();
//}
