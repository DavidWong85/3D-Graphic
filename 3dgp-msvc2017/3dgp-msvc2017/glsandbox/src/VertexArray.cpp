#include "VertexBuffer.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &ID);
	if (!&ID)
	{
		throw std::exception();
	}
}

VertexArray::~VertexArray()
{

}

void VertexArray::setBuffer(std::string _name, std::shared_ptr<VertexBuffer> _value) 
{
	glBindVertexArray(ID);
	glBindBuffer(GL_ARRAY_BUFFER, _value->getID());
	int position = 0;
	if (_name == "a_Position")
	{
		position = 0;
	}
	else if (_name == "a_TexCoord")
	{
		position = 1;
	}
	else if (_name == "a_Normal")
	{
		position = 2;
	}
	glVertexAttribPointer(position, _value->getComponents(), GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(position);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint VertexArray::getID()
{
	return ID;
}