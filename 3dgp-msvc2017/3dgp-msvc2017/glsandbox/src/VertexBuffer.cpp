#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &ID);
	if (!ID)
	{
		throw std::exception();
	}
	Components = 0;
	NotSynced = false;
}

VertexBuffer::~VertexBuffer()
{

}

void VertexBuffer::Add(float value)
{
	if (Components != 0 && Components != 1)
	{
		throw std::exception();
	}
	data.push_back(value);
	Components = 1;
	NotSynced = true;
}

void VertexBuffer::Add(glm::vec2 value)
{
	if (Components != 0 && Components != 2)
	{
		throw std::exception();
	}
	data.push_back(value.x);
	data.push_back(value.y);
	Components = 2;
	NotSynced = true;

}

void VertexBuffer::Add(glm::vec3 value)
{
	if (Components != 0 && Components != 3)
	{
		throw std::exception();
	}
	data.push_back(value.x);
	data.push_back(value.y);
	data.push_back(value.z);
	Components = 3;
	NotSynced = true;
}

void VertexBuffer::Add(glm::vec4 value)
{
	if (Components != 0 && Components != 4)
	{
		throw std::exception();
	}
	data.push_back(value.x);
	data.push_back(value.y);
	data.push_back(value.z);
	data.push_back(value.w);

	Components = 4;
	NotSynced = true;
}

int VertexBuffer::getComponents()
{
	return Components;
}

int VertexBuffer::getDataSize()
{
	return (data.size() / Components);
}

GLuint VertexBuffer::getID()
{
	if (NotSynced)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data.at(0)) * data.size(), &data.at(0), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		NotSynced = false;
	}
	return ID;
}