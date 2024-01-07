#include "precHeaders.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Amber
{
	
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.'); 
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		std::string& name = filepath.substr(lastSlash, count);

		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				AM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				break;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, filepath);

			default:
				AM_CORE_ASSERT(false, "Unknown Renderer API!");
				return nullptr;
				break;
		}

		return nullptr;
	} 

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		AM_INFO("Shader name is: {0}", name);
		if (m_Shaders.find(name) == m_Shaders.end())
			m_Shaders[name] = shader;
		else
			AM_CORE_WARN("A shader with this name already exists in the library!");
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{ 
		if (!Exists(name))
			m_Shaders[name] = shader;
		else
			AM_CORE_WARN("A shader with this name already exists in the library!");
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(name, shader);

		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		AM_CORE_ASSERT(Exists(name), "This shader name does not exist in the library!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}