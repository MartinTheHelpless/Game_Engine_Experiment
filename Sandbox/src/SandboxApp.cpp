#include <Amber.h>
#include <Amber/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Amber::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController((float)(1280.0f / 720.0f))
	{

		m_VertexArray = Amber::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Amber::VertexBuffer> vertexBuffer;
		std::shared_ptr<Amber::IndexBuffer> indexBuffer;
		vertexBuffer.reset(Amber::VertexBuffer::Create(vertices, sizeof(vertices)));

		Amber::BufferLayout layout = {
			{ Amber::ShaderDataType::Float3, "a_Position" },
			{ Amber::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		indexBuffer.reset(Amber::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Amber::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Amber::VertexBuffer> squareVB;
		squareVB.reset(Amber::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Amber::BufferLayout squareLayout = {
			{ Amber::ShaderDataType::Float3, "a_Position" },
			{ Amber::ShaderDataType::Float2, "a_TextCoord" }
		};

		squareVB->SetLayout(squareLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2 ,3 ,0 };
		std::shared_ptr<Amber::IndexBuffer> squareIB;
		squareIB.reset(Amber::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB); 
		 
		m_TextureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		m_FlatShader = m_ShaderLibrary.Load("assets/shaders/Flat.glsl");
		m_Shader = m_ShaderLibrary.Load("assets/shaders/Colorful.glsl");

		m_Texture = Amber::Texture2D::Create("assets/Textures/Checkerboard.png");

		m_DropTexture = Amber::Texture2D::Create("assets/Textures/Drop.png");

		std::dynamic_pointer_cast<Amber::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Amber::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Color", 0);

	}

	void OnUpdate(Amber::Timestep ts) override
	{  
   
		m_CameraController.OnUpdate(ts);

		Amber::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1 });
		Amber::RenderCommand::Clear();

		Amber::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f)); 
		 
		std::dynamic_pointer_cast<Amber::OpenGLShader>(m_FlatShader)->Bind();
		std::dynamic_pointer_cast<Amber::OpenGLShader>(m_FlatShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int i = 0; i < 20; i++)
		{ 
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 position(m_SquarePosition.x + j * 0.09, m_SquarePosition.y + i * 0.09f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Amber::Renderer::Submit(m_FlatShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Amber::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_DropTexture->Bind();
		Amber::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));


		// Amber::Renderer::Submit(m_Shader, m_VertexArray);

		Amber::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{ 
		ImGui::Begin("Color Settings");

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();

	}

	void OnEvent(Amber::Event& e) override
	{ 

		m_CameraController.OnEvent(e);

		if (e.GetEventType() == Amber::EventType::WindowResize) 
			auto& re = (Amber::WindowResizeEvent&)e; 

	}

	bool OnKeyPresseEvent(Amber::KeyPressedEvent& event) 
	{ 
		return false;
	}

	private:

		Amber::ShaderLibrary m_ShaderLibrary;
		 
		Amber::Ref<Amber::VertexArray> m_VertexArray;

		Amber::Ref<Amber::Shader> m_FlatShader, m_TextureShader, m_Shader;
		Amber::Ref<Amber::VertexArray> m_SquareVA;

		Amber::Ref<Amber::Texture2D> m_Texture, m_DropTexture;

		Amber::OrthographicCameraController m_CameraController;
		 
		glm::vec3 m_SquarePosition = { 0.0f, 0.0f, 0.0f};

		glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	};

	class Sandbox : public Amber::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer()); 
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}

};

Amber::Application* Amber::CreateApplication()
{
	return new Sandbox();
}