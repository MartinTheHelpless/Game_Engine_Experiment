#pragma once
#include "Amber/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Amber
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

		virtual ~OpenGLShader();

		uint32_t CreateShaders(const std::string& shaderSrc, char type);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

		void UploadUniformInt(const std::string& name, int vector);

		void UploadUniformFloat(const std::string& name, float vector);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
		 
	private:
		uint32_t m_RendererID;
	};



}