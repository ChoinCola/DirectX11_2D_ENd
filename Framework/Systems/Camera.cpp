#include "Framework.h"
#include "Camera.h"

void Camera::Update()
{
	Move();
}

void Camera::Render()
{
	vpb->SetVSBuffer(1);
}

void Camera::Move()
{
	float delta = Time::Get()->Delta();

	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += cameraSpeed * delta;
	else if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= cameraSpeed * delta;

	if (Keyboard::Get()->Press(VK_UP))
		position.y += cameraSpeed * delta;
	else if (Keyboard::Get()->Press(VK_DOWN))
		position.y -= cameraSpeed * delta;

	UpdateView();
}

void Camera::UpdateView()
{
	D3DXMatrixLookAtLH(&view, &position, &(position + Values::FwdVec), &Values::UpVec);
	vpb->SetView(view);
}

void Camera::UnProjection(Vector3* out, Vector3 source, Matrix world)
{
	Vector3 position = source;

	out->x = (position.x * 2.0f / WinMaxWidth) - 1.f;
	out->y = (position.y * 2.0f / WinMaxHeight) - 1.f;
	out->z = position.z;

	Matrix wvp = world * view * proj;
	D3DXMatrixInverse(&wvp, nullptr, &wvp);
	D3DXVec3TransformCoord(out, out, &wvp);
}

Camera::Camera()
{
	// Create Buffer
	{
		// view, projection 버퍼 선언
		vpb = new VPBuffer;

		// view 행렬
		D3DXMatrixLookAtLH
		(
			&view,
			&Vector3(0, 0, 0),	// 카메라 위치
			&Vector3(0, 0, 1),	// 카메라가 바라보는 방향
			&Vector3(0, 1, 0)	// 카메라 위쪽 방향
		);

		// projection 행렬
		D3DXMatrixOrthoOffCenterLH
		(
			&proj,
			0.0f,				// 왼쪽 면의 위치
			(float)WinMaxWidth,	// 오른쪽 면의 위치
			0.0f,				// 아래쪽 면의 위치
			(float)WinMaxHeight,// 위쪽 면의 위치
			0,					// 가까운 면
			1					// 멀리 있는 면
		);

		vpb->SetView(view);
		vpb->SetProj(proj);
	}
}

Camera::~Camera()
{
	SAFE_DELETE(vpb);
}