#include "Mipch.h"
#include "OrthographicCameraController.h"
#include "Micro\Input.h"
#include "Micro\KeyCodes.h"

namespace Micro {
	Micro::OrthographicCameraController::OrthographicCameraController(float aspeectRation, bool roations)
		: m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void Micro::OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		if (Input::IsKeyPressed(MC_KEY_A))
			m_CamPosition.x -= m_CamTranslationsSpeed * ts;
		else if (Input::IsKeyPressed(MC_KEY_D))
			m_CamPosition.x += m_CamTranslationsSpeed * ts;
		if (Input::IsKeyPressed(MC_KEY_S))
			m_CamPosition.y -= m_CamTranslationsSpeed * ts;
		else if (Input::IsKeyPressed(MC_KEY_W))
			m_CamPosition.y += m_CamTranslationsSpeed * ts;

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(MC_KEY_Q))
				m_CamRot += m_CamRoationSpeed * ts;
			else if (Input::IsKeyPressed(MC_KEY_E))
				m_CamRot -= m_CamRoationSpeed * ts;
		}
	}

	void Micro::OrthographicCameraController::OnEvent(Event & e)
	{
	}

	bool Micro::OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		return false;
	}

	bool Micro::OrthographicCameraController::OnWindowEwsized(WindowResizeEvent & e)
	{
		return false;
	}
}