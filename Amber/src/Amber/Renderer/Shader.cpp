#include "precHeaders.h" 
#include "Shader.h" 

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Amber
{
	 
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{  
		GLuint vertexShader = CreateShaders(vertexSrc, 'v'); // v as in vertex 
		GLuint fragmentShader = CreateShaders(fragmentSrc, 'f'); // f as in fragment

		 if (vertexShader == 0 || fragmentShader == 0)
		 {
				AM_CORE_ASSERT(false, "Shader compilation error");
				return;
		 }

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		 
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
			AM_CORE_ASSERT(false, "Shader linking error");
			return;
		}
		 
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	GLuint Shader::CreateShaders(const std::string& shaderSrc, char type)
	{ 
		 GLuint shader = (type == 'v' ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER));

		 const GLchar* source = shaderSrc.c_str();

		 glShaderSource(shader, 1, &source, 0);

		 glCompileShader(shader);  

		GLint compileStatus = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if(compileStatus == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]); 
			 
			AM_CORE_ERROR("{0}", infoLog.data());

			glDeleteShader(shader); 

			return 0;
		}else
			return shader;
	
	} 

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name,  const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}