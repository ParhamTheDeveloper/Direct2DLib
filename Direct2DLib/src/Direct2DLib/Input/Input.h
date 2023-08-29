#pragma once

#include "Direct2DLib/Core/Base.h"
#include "Direct2DLib/Events/Event.h"
#include "Direct2DLib/Math/Vector2.h"

namespace D2DLib
{

	class D2DLIB_API Input
	{
	public:
		class D2DLIB_API Keyboard
		{
		protected:
			virtual void OnKeyDown(Event& event) = 0;
			virtual void OnKeyUp(Event& event) = 0;
			virtual void OnKeyPress(Event& event) = 0;
		public:
			static bool IsKeyPressed(int character);
			static bool IsKeyPressedAsync(int character);
		};

		class D2DLIB_API Mouse
		{
		protected:
			virtual void OnMouseDown(Event& event) = 0;
			virtual void OnMouseUp(Event& event) = 0;
			virtual void OnMouseMove(Event& event) = 0;
		public:
			static const Vector2 GetPosition();
		};
	};

}