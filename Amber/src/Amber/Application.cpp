#include "precHeaders.h"
#include "Application.h"

#include "Amber/Events/Event.h"
#include "Amber/Log.h"
#include "Input.h"

#include <glad/glad.h>

namespace Amber
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) 
	{
		switch (type)
		{ 
		case Amber::ShaderDataType::Float:
			return GL_FLOAT;
		case Amber::ShaderDataType::Float2:
			return GL_FLOAT;
		case Amber::ShaderDataType::Float3:
			return GL_FLOAT;
		case Amber::ShaderDataType::Float4:
			return GL_FLOAT;
		case Amber::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Amber::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Amber::ShaderDataType::Int:
			return GL_INT;
		case Amber::ShaderDataType::Int2:
			return GL_INT;
		case Amber::ShaderDataType::Int3:
			return GL_INT;
		case Amber::ShaderDataType::Int4:
			return GL_INT;
		case Amber::ShaderDataType::Bool:
			return GL_BOOL;
		default:
			AM_ASSERT(false, "Unknown ShaderDataType!");
			return NULL;
		}
	}

	Application::Application()
	{
		AM_CORE_ASSERT(!s_Instance, "Application already exists! ");

		s_Instance = this;


		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		 
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);
		 
		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f, 
			 0.75f, -0.75f, 0.0f, 
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB; 
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position" } 
		};

		squareVB->SetLayout(squareLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2 ,3 ,0};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource= R"(
			#version 330 core
	
			layout(location = 0) in vec3 a_Position; 
			layout(location = 1) in vec4 a_Color; 

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
				{
					v_Position = a_Position;
					gl_Position = vec4(a_Position, 1.0); 
					v_Color = a_Color;
				} 
			)";

		std::string fragmentSource = R"(
			#version 330 core
	
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
				{ 
					color = vec4(v_Position + 0.3, 1.0); 
					color = v_Color;
				} 
			)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));


		std::string blueShaderVertexSource = R"(
			#version 330 core
	
			layout(location = 0) in vec3 a_Position; 

			out vec3 v_Position;

			void main()
				{
					v_Position = a_Position;
					gl_Position = vec4(a_Position, 1.0); 
				} 
			)";

		std::string blueShaderFragmentSource = R"(
			#version 330 core
	
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
				{ 
					color = vec4(0.2, 0.3, 0.8, 1.0); 
				} 
			)";

		m_BlueShader.reset(new Shader(blueShaderVertexSource, blueShaderFragmentSource));

	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.32f, 0.0f, 0.72f, 1);
			glClear(GL_COLOR_BUFFER_BIT); 

			m_BlueShader->Bind();
			m_SquareVA->Bind();

			glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}