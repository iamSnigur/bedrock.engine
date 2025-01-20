#include "TestScene.h"
#include "Core/Application.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Events/KeyTokens.h"
#include "Core/Input.h"

#define TINYOBJLOADER_IMPLEMENTATION // make separate model loader
#include "tiny_obj_loader/tiny_obj_loader.h"

namespace Bedrock
{
#define BIND_EVENT(x) std::bind(&Bedrock::x, this, std::placeholders::_1)

	TestScene::TestScene()
		:	m_Camera{ 60.0f, 1920.0f, 1080.0f }
	{
		m_VertexArray.reset(VertexArray::Create());
				
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;
		
		const char* modelPath = "res/models/dodge-pickup/source/Dodge/dodge-model.obj";
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, modelPath);

		if (!ret) 
		{
			printf("Failed to load/parse .obj.\n");
			std::cerr << "ERR: " << err << "\n";
			return;
		}
		
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(attrib.vertices.data(), attrib.vertices.size() * sizeof(float)));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Pos" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::vector<uint32_t> indices;
		for (const auto& index : shapes[0].mesh.indices)
			indices.push_back(index.vertex_index);		

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices.data(), indices.size()));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Shader::Create("res/shaders/default.glsl"));

		m_CameraPosition = glm::vec3{ 0.0f, 0.0f, 10.0f };
		Application::Get().GetWindow().SetCursorDisabled();
		m_PreviousMousePos = Input::GetMousePosition();
	}

	TestScene::~TestScene()
	{ }

	void TestScene::OnUpdate(Time deltaTime)
	{
		const float ROTATION_SPEED = 30.0f;
		const float MOVEMENT_SPEED = 7.0f;

		glm::vec2 mousePos = Input::GetMousePosition();	

		glm::vec2 inputDir = mousePos - m_PreviousMousePos;
		inputDir.y = -inputDir.y;

		m_CameraRotation.y -= inputDir.x * ROTATION_SPEED * deltaTime.GetSeconds();
		m_CameraRotation.x += inputDir.y * ROTATION_SPEED * deltaTime.GetSeconds();
		m_CameraRotation.x = glm::clamp(m_CameraRotation.x, -90.0f, 90.0f);

		glm::quat rotation = m_Camera.GetTransform().GetRotation();
		glm::vec3 forward = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 right = rotation * glm::vec3(1.0f, 0.0f, 0.0f);	
		forward = glm::normalize(forward);
		right = glm::normalize(right);

		glm::vec3 movementInput(0.0f);
		if (Input::IsKeyPressed(GLFW_KEY_W)) movementInput += forward;
		if (Input::IsKeyPressed(GLFW_KEY_S)) movementInput -= forward;
		if (Input::IsKeyPressed(GLFW_KEY_A)) movementInput -= right;
		if (Input::IsKeyPressed(GLFW_KEY_D)) movementInput += right;

		if (glm::length(movementInput) > 0.0f) 
			movementInput = glm::normalize(movementInput);		

		float moveSpeed = MOVEMENT_SPEED;
		if (Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) moveSpeed *= 4.0f;

		m_CameraPosition += movementInput * moveSpeed * deltaTime.GetSeconds();
		
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
			Application::Get().GetWindow().SetCursorNormal();		

		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		glm::vec3 eulerAngles(
			glm::radians(m_CameraRotation.x), 
			glm::radians(m_CameraRotation.y),
			glm::radians(m_CameraRotation.z));
		m_Camera
			.GetTransform()
			.SetRotation(glm::quat(eulerAngles));
				
		m_Camera
			.GetTransform()
			.SetPosition(m_CameraPosition);

		m_Camera.UpdateViewMatrix();

		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_VertexArray, m_Shader); // submit whole mesh

		Renderer::EndScene();

		m_PreviousMousePos = mousePos;
	}

	void TestScene::OnEvent(Event& e)
	{

	}
}