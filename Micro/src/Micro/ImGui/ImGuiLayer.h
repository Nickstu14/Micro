#pragma once

#include "Micro\Layer.h"

#include "Micro\Events\KeyEvent.h"
#include "Micro\Events\MouseEvent.h"
#include "Micro\Events\ApplicationEvent.h"

namespace Micro
{
	class MICRO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}