#include "VertexContainers.h"

GLVertexBuffer::GLVertexBuffer(float* data, int count)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_DYNAMIC_DRAW));
}

GLVertexBuffer::~GLVertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void GLVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void GLVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

GLIndexBuffer::GLIndexBuffer(unsigned int* data, int count)
{
	m_Count = count;
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_DYNAMIC_DRAW));
}

GLIndexBuffer::~GLIndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void GLIndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void GLIndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline unsigned int GLIndexBuffer::GetCount() const
{
	return m_Count;
}

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_ID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::AddBuffer(const GLVertexBuffer& vb, const GLVertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset));

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_ID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

Texture::Texture(const std::string &filePath) : m_ID(0) ,m_data()
{
	GLCall(glGenTextures(1, &m_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (filePath.find(".jpg") != std::string::npos)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else if (filePath.find(".png") != std::string::npos)
		{
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
		else
		{
			conlog("Its great and all, but your file is not a jpg nor a png.");
			conlog(filePath);
		}
	}
	else
	{
		conlog("Failed to load texture.");
	}

	stbi_image_free(data);
}

void Texture::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

inline unsigned int& Texture::GetID()
{
	return m_ID;
}

void Texture::GLBind(Texture &texture, int slot)
{
	int slotCode = 33984 + slot;
	if (slotCode > 34015 || slotCode < 33984)
	{
		conlog("Slot number " << slot << " is invalid.");
	}
	else
	{
		GLCall(glActiveTexture(slotCode));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture.GetID()));
	}
}
