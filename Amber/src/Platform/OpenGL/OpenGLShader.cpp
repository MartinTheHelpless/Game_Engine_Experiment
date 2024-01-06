#include "precHeaders.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Amber
{
	 
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) 
	{
		GLuint vertexOpenGLShader = CreateShaders(vertexSrc, 'v'); // v as in vertex 
		GLuint fragmentOpenGLShader = CreateShaders(fragmentSrc, 'f'); // f as in fragment

		if (vertexOpenGLShader == 0 || fragmentOpenGLShader == 0)
		{
			AM_CORE_ASSERT(false, "OpenGLShader compilation error");
			return;
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexOpenGLShader);
		glAttachShader(program, fragmentOpenGLShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			AM_CORE_ERROR("{0}", infoLog.data());
			AM_CORE_ASSERT(false, "OpenGLShader linking error");
			return;
		}

		glDetachShader(program, vertexOpenGLShader);
		glDetachShader(program, fragmentOpenGLShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	GLuint OpenGLShader::CreateShaders(const std::string& shaderSrc, char type)
	{
		GLuint shader = (type == 'v' ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER));

		const GLchar* source = shaderSrc.c_str();

		glShaderSource(shader, 1, &source, 0);

		glCompileShader(shader);

		GLint compileStatus = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			AM_CORE_ERROR("{0}", infoLog.data());

			glDeleteShader(shader);

			return 0;
		}
		else
			return shader;

	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, vector);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, vector);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w); 
	}

}