#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <string>

class VertexBuffer;

class VertexArray
{
private:
	GLuint ID;

public:
	VertexArray();
	~VertexArray();
	void setBuffer(std::string _name, std::shared_ptr<VertexBuffer> _value);
	GLuint getID();

};