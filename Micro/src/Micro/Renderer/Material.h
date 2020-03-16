#pragma once
#include "Shader.h"

namespace Micro
{
	class Material
	{
	public :
		Material(Ref<Shader> shader);



	private:
		Ref<Shader>& m_Shader;
	};
}