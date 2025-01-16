#include "TestScene.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Events/KeyTokens.h"
#include "Core/Input.h"

namespace Bedrock
{
#define BIND_EVENT(x) std::bind(&Bedrock::x, this, std::placeholders::_1)

	TestScene::TestScene()
		:	m_Camera{ 60.0f, 1920.0f, 1080.0f }
	{
		m_VertexArray.reset(VertexArray::Create());

		/*float vertices[3 * 4] =
		{
			-0.5, -0.5,  0.5,
			 0.5, -0.5,  0.5,
			-0.5,  0.5,  0.5,
			 0.5,  0.5,  0.5,
		};*/

		float vertices[3 * 4] =
		{
			-5.0, -5.0,  -25.5,
			 5.0, -5.0,  -25.5,
			-5.0,  5.0,  -25.5,
			 5.0,  5.0,  -25.5,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Pos" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3 * 2] =
		{
			0, 1, 2,
			1, 2, 3,
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, 3 * 2));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Shader::Create("res/shaders/default.glsl"));

		m_Camera
			.GetTransform()
			.SetPosition({ 0.0f, 0.0f, 20.0f });
	}

	TestScene::~TestScene()
	{

	}

	void TestScene::OnUpdate(Time deltaTime)
	{
		const float ROTATION_SPEED = 40.0f;

		if (Input::IsKeyPressed(GLFW_KEY_A))
			m_RotationAngle += ROTATION_SPEED * deltaTime.GetSeconds();
		else if (Input::IsKeyPressed(GLFW_KEY_D))
			m_RotationAngle -= ROTATION_SPEED * deltaTime.GetSeconds();

		RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		RenderCommand::Clear();

		glm::vec3 eulerAngles(glm::radians(0.0f), glm::radians(m_RotationAngle), glm::radians(0.0f));
		m_Camera
			.GetTransform()
			.SetRotation(glm::quat(eulerAngles));

		m_Camera.UpdateViewMatrix();

		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_VertexArray, m_Shader); // submit whole mesh

		Renderer::EndScene();
	}

	void TestScene::OnEvent(Event& e)
	{

	}
}