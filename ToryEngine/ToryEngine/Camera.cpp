#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera()
	: Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	Vector3 eyePosition = GetTransform()->GetPosition();
	Vector3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vector3 upDirection = GetTransform()->GetUp();
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	//S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
	{
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.0f, 800.0f / 600.0f, 1.0f, 100.0f);
	}
	else
	{
		S_MatProjection = XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
	}
}
