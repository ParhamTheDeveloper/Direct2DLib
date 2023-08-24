#pragma once

#include "Direct2DLib/Core/Graphics.h"
#include "Direct2DLib/Math/Math.h"

namespace D2DLib
{

	class Camera
	{
	public:
		Camera(Graphics* gfx = nullptr);
		Camera(
			const Vector2& position,
			const Vector2& scale,
			float rotation,
			Graphics* gfx = nullptr
		);
		Camera(
			const Vector2& position,
			float scale,
			float rotation,
			Graphics* gfx = nullptr
		);

		void SetPosition(const Vector2& position);
		void SetScale(const Vector2& scale);
		void SetScale(float scale);
		void SetRotation(float rotation);

		const Vector2& GetPosition() const { return Position; }
		const Vector2& GetScale() const { return Scale; }
		float GetRotation() const { return Rotation; }
		D2D1::Matrix3x2F GetViewMatrix() const;

		void Update();
	public:
		Vector2 Position, Scale;
		float Rotation;
	private:
		ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
		static Camera* s_Instance;
	private:
		friend Camera* GetMainCamera();
	};
	
	Camera* GetMainCamera();

}