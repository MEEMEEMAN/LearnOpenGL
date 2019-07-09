#pragma once
#include "perhapsPch.h"

struct GLVertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	GLVertexBuffer(float* data, int count);
	~GLVertexBuffer();
	void Bind() const;
	void Unbind() const;
};

struct GLIndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	GLIndexBuffer(unsigned int* data, int count);
	~GLIndexBuffer();
	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const;
};

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

struct GLVertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	GLVertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const
	{
		return m_Elements;
	}

	inline unsigned int GetStride() const
	{
		return m_Stride;
	}
};

class VertexArray
{
	unsigned int m_ID;
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const GLVertexBuffer& buffer, const GLVertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};

class Texture
{
	unsigned int m_ID;
	unsigned char* m_data;
	public:
	Texture(const std::string& filePath);
	void Bind();
	void Unbind();
	inline unsigned int &GetID();

	static void GLBind(Texture &texture, int slot);
};