#pragma once

#include "Micro\Core.h"

namespace Micro
{
	class MICRO_API Input
	{
	public :
		inline static bool IsKeyPressed(int Keycode) {	return s_Instance->IsKeyPressedImp(Keycode);}

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImp(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImp(); }
		inline static std::pair<float,float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }

	protected:
		virtual bool IsKeyPressedImp(int Keycode) = 0;
		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImp() = 0;
		virtual float GetMouseXImp() = 0;
		virtual float GetMouseYImp() = 0;
	private :
		static Input* s_Instance;
	};
}


