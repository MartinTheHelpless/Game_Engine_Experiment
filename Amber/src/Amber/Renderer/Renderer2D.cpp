#include "precHeaders.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h" 
#include <glm/gtc/matrix_transform.hpp>

namespace Amber
{

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray; 
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/Shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texure", 0.0f);
	}

	void Renderer2D::Shutdown()
	{
		AM_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		AM_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix()); 

	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float scale)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color, scale);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float scale)
	{
		AM_PROFILE_FUNCTION();

		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		 
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->TextureShader->SetFloat2("u_Scale", { scale ,scale });

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float scale, const glm::vec4& color)
	{

		DrawQuad({ position.x, position.y, 0.0f }, size, texture, scale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float scale, const glm::vec4& color)
	{
		AM_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(color));
		s_Data->TextureShader->SetFloat2("u_Scale", { scale ,scale });

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f }); 
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuadEx(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, float scale)
	{
		DrawQuadEx({ position.x, position.y, 0.0f }, size, rotation, color, scale);
	}

	void Renderer2D::DrawQuadEx(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, float scale)
	{
		AM_PROFILE_FUNCTION();

		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation * (-1)), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->TextureShader->SetFloat2("u_Scale", { scale ,scale });

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuadEx(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float scale, const glm::vec4& color)
	{
		DrawQuadEx({ position.x, position.y, 0.0f }, size, rotation, texture,  scale, color);
	}

	void Renderer2D::DrawQuadEx(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float scale, const glm::vec4& color)
	{
		AM_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(color));
		s_Data->TextureShader->SetFloat2("u_Scale", { scale ,scale });

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation*(-1)), {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}