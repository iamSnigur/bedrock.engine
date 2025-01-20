#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Bedrock
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Bedrock::ShaderDataType::None:		return 0;
			case Bedrock::ShaderDataType::Float:	return 4;
			case Bedrock::ShaderDataType::Float2:   return 4 * 2;
			case Bedrock::ShaderDataType::Float3:	return 4 * 3;
			case Bedrock::ShaderDataType::Float4:	return 4 * 4;
			case Bedrock::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case Bedrock::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case Bedrock::ShaderDataType::Bool:		return 1;
		}
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name{ name }, Type{ type }, Size{ ShaderDataTypeSize(type) }, Offset{ 0 }, Normalized{ normalized }
		{ }

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case Bedrock::ShaderDataType::None:		return 0;
				case Bedrock::ShaderDataType::Float:	return 1;
				case Bedrock::ShaderDataType::Float2:	return 2;
				case Bedrock::ShaderDataType::Float3:	return 3;
				case Bedrock::ShaderDataType::Float4:	return 4;
				case Bedrock::ShaderDataType::Mat3:		return 3 * 3;
				case Bedrock::ShaderDataType::Mat4:		return 4 * 4;
				case Bedrock::ShaderDataType::Bool:		return 1;
			}
		}		
	};

	class BufferLayout
	{
	public:
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }
		
		BufferLayout() {}
		
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements{elements} 
		{
			CalculateOffsetsAndStride();
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		void CalculateOffsetsAndStride()
		{
			uint32_t offset{ 0 };
			m_Stride = 0;

			for (BufferElement& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}				
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}