#pragma once

#include "Micro\Renderer\OrthographicCamera.h"
#include "Micro\Core\TimeStep.h"

#include "Micro\Events\ApplicationEvent.h"
#include "Micro\Events\MouseEvent.h"

namespace Micro {

	class OrthographicCameraController
	{
	public :
		OrthographicCameraController(float aspeectRation, bool rotation = false); 
		~OrthographicCameraController();

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

	private :
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowEwsized(WindowResizeEvent& e);

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation = false;
		glm::vec3 m_CamPosition = { 0.0f,0.0f,0.0f };
		float m_CamRot = 0.0f;
		float m_CamTranslationsSpeed = 1.0f;
		float m_CamRoationSpeed = 1.0f;
	};

}
