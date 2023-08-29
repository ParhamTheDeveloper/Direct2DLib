#include "pch.h"
#include "Input.h"

namespace D2DLib
{

	// Keyboard methods

	bool Input::Keyboard::IsKeyPressed(int character)
	{
		return (GetKeyState(character) & 0x8000);
	}

	bool Input::Keyboard::IsKeyPressedAsync(int character)
	{
		return (GetAsyncKeyState(character) & 0x8000);
	}

	// Mouse methods

	const Vector2 Input::Mouse::GetPosition()
	{
		POINT pos;
		GetCursorPos(&pos);
		return Vector2(Cast<float>(pos.x), Cast<float>(pos.y));
	}

}