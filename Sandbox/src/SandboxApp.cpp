#include <Amber.h>

#include "imgui/imgui.h"

class ExampleLayer : public Amber::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_SquarePosition(0.0f)
	{

		m_VertexArray.reset(Amber::VertexArray::Create());

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

		m_SquareVA.reset(Amber::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Amber::VertexBuffer> squareVB;
		squareVB.reset(Amber::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Amber::BufferLayout squareLayout = {
			{ Amber::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareLayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2 ,3 ,0 };
		std::shared_ptr<Amber::IndexBuffer> squareIB;
		squareIB.reset(Amber::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core
	
			layout(location = 0) in vec3 a_Position; 
			layout(location = 1) in vec4 a_Color; 

			uniform mat4 u_ViewProjectionMat;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
				{
					v_Position = a_Position;
					v_Color = a_Color;
					gl_Position = u_ViewProjectionMat * u_Transform * vec4(a_Position, 1.0); 
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

		m_Shader.reset(new Amber::Shader(vertexSource, fragmentSource));


		std::string blueShaderVertexSource = R"(
			#version 330 core
	
			layout(location = 0) in vec3 a_Position; 

			uniform mat4 u_ViewProjectionMat;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjectionMat * u_Transform * vec4(a_Position, 1.0); 
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

		m_BlueShader.reset(new Amber::Shader(blueShaderVertexSource, blueShaderFragmentSource));

	}

	void OnUpdate(Amber::Timestep ts) override
	{  

		if (Amber::Input::IsKeyPressed(AM_KEY_LEFT) || Amber::Input::IsKeyPressed(AM_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts;

		else if (Amber::Input::IsKeyPressed(AM_KEY_RIGHT) || Amber::Input::IsKeyPressed(AM_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts;
		
		if (Amber::Input::IsKeyPressed(AM_KEY_DOWN) || Amber::Input::IsKeyPressed(AM_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		else if (Amber::Input::IsKeyPressed(AM_KEY_UP) || Amber::Input::IsKeyPressed(AM_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts;
		 


		if (Amber::Input::IsKeyPressed(AM_KEY_J))
			m_SquarePosition.x -= m_SquareSpeed * ts;

		else if (Amber::Input::IsKeyPressed(AM_KEY_L))
			m_SquarePosition.x += m_SquareSpeed * ts;

		if (Amber::Input::IsKeyPressed(AM_KEY_I))
			m_SquarePosition.y += m_SquareSpeed * ts;

		else if (Amber::Input::IsKeyPressed(AM_KEY_K))
			m_SquarePosition.y -= m_SquareSpeed* ts;
		 

		if (Amber::Input::IsKeyPressed(AM_KEY_Q))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		else if (Amber::Input::IsKeyPressed(AM_KEY_E))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation); 
  
		Amber::RenderCommand::SetClearColor({ 0.12f, 0.12f, 0.12f, 1 });
		Amber::RenderCommand::Clear();

		Amber::Renderer::BeginScene(m_Camera);

		
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f));

		for (int i = 0; i < 20; i++)
		{ 
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 position(m_SquarePosition.x + j * 0.09, m_SquarePosition.y + i * 0.09f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;

				Amber::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}

		Amber::Renderer::Submit(m_Shader, m_VertexArray);

		Amber::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{ 

	}

	void OnEvent(Amber::Event& event) override
	{ 

		//Amber::EventDispatcher dispatcher(event);

		//dispatcher.Dispatch<Amber::KeyPressedEvent>(AM_BIND_EVENT_FN(ExampleLayer::OnKeyPresseEvent));

	}

	bool OnKeyPresseEvent(Amber::KeyPressedEvent& event) 
	{

		switch (event.GetKeyCode())
		{
			case AM_KEY_LEFT:
				m_CameraPosition.x -= m_CameraSpeed; 
				break;

			case AM_KEY_RIGHT:
				m_CameraPosition.x += m_CameraSpeed; 
				break;

			case AM_KEY_DOWN:
				m_CameraPosition.y -= m_CameraSpeed; 
				break;

			case AM_KEY_UP:
				m_CameraPosition.y += m_CameraSpeed;
				break;

			default:
				break;
		}
		
		return false;
	}

	private:

		std::shared_ptr<Amber::Shader> m_Shader;
		std::shared_ptr<Amber::VertexArray> m_VertexArray;

		std::shared_ptr<Amber::Shader> m_BlueShader;
		std::shared_ptr<Amber::VertexArray> m_SquareVA;

		Amber::OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition;
		float m_CameraRotation = 0.0f;

		float m_CameraSpeed = 2.0f;
		float m_CameraRotationSpeed = 60.0f;

		glm::vec3 m_SquarePosition;
		float m_SquareSpeed = 1.0f;

	};
class Sandbox : public Amber::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer()); 
	}

	~Sandbox()
	{
	}

};

Amber::Application* Amber::CreateApplication()
{
	return new Sandbox();
}