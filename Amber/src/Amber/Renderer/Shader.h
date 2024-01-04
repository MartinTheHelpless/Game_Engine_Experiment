#pragma once

#include <string>
#include <glm/glm.hpp>

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
		 
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;

	};


}
