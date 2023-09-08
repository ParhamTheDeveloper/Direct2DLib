#include "Direct2DLibpch.h"
#include "Camera.h"

namespace D2DLib
{
	Camera* Camera::s_Instance = nullptr;

	Camera::Camera(Graphics* gfx) :
		Position(),
		Scale({ 1.0f, 1.0f }),
		Rotation(0.0f),
		m_RenderTarget(gfx ? gfx->GetRenderTarget() : GetMainGraphics()->GetRenderTarget())
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
		Update();
	}

	Camera::Camera(
		const Vector2& position,
		const Vector2& scale,
		float rotation,
		Graphics* gfx
	) :
		Position(position),
		Scale(scale),
		Rotation(rotation),
		m_RenderTarget(gfx ? gfx->GetRenderTarget() : GetMainGraphics()->GetRenderTarget())
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
		Update();
	}

	Camera::Camera(
		const Vector2& position,
		float scale,
		float rotation,
		Graphics* gfx
	) :
		Position(position),
		Scale({ scale, scale }),
		Rotation(rotation),
		m_RenderTarget(gfx ? gfx->GetRenderTarget() : GetMainGraphics()->GetRenderTarget())
	{
		if (!s_Instance)
		{
			s_Instance = this;
		}
		Update();
	}

	void Camera::SetPosition(const Vector2& position)
	{
		Position = position;
		Update();
	}

	void Camera::SetScale(const Vector2& scale)
	{
		Scale = scale;
		Update();
	}

	void Camera::SetScale(float scale)
	{
		Scale = { scale, scale };
		Update();
	}

	void Camera::SetRotation(float rotation)
	{
		Rotation = rotation;
		Update();
	}

	D2D1::Matrix3x2F Camera::GetViewMatrix() const
	{
		return D2D1::Matrix3x2F::Translation(-Position.X, -Position.Y) *
			D2D1::Matrix3x2F::Scale(Scale.X, Scale.Y) *
			D2D1::Matrix3x2F::Rotation(-Rotation, D2D1::Point2F(
				m_RenderTarget->GetSize().width / 2,
				m_RenderTarget->GetSize().height / 2
			));
	}

	void Camera::Update()
	{
		m_RenderTarget->SetTransform(GetViewMatrix());
	}

	Camera* GetMainCamera()
	{
		return Camera::s_Instance;
	}

}