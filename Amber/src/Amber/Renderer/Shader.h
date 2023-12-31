#pragma once

#include <string>

namespace Amber
{

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

		~Shader();

		uint32_t CreateShaders(const std::string& shaderSrc, char type);

		void Bind() const;
		void Unbind() const;
		
	private:
		uint32_t m_RendererID;

	};


}
