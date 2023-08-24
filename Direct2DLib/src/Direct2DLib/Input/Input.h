#pragma once

#include "Direct2DLib/Core/Base.h"

namespace D2DLib
{

	class Input
	{
	public:
		class Keyboard
		{
		protected:
			virtual void OnKeyDown(Event& event) = 0;
			virtual void OnKeyUp(Event& event) = 0;
			virtual void OnKeyPress(Event& event) = 0;
		public:
			static bool IsKeyPressed(int character)
			{
				return (GetKeyState(character) & 0x8000);
			}

			static bool IsKeyPressedAsync(int character)
			{
				return (GetAsyncKeyState(character) & 0x8000);
			}
		};

		class Mouse
		{
		protected:
			virtual void OnMouseDown(Event& event) = 0;
			virtual void OnMouseUp(Event& event) = 0;
			virtual void OnMouseMove(Event& event) = 0;
		public:
			static const Vector2 GetPosition()
			{
				POINT pos;
				GetCursorPos(&pos);
				return Vector2(Cast<float>(pos.x), Cast<float>(pos.y));
			}
		};
	};

}