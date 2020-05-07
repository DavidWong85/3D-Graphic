#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class VertexBuffer
{
private:
	GLuint ID;
	int Components;
	std::vector<GLfloat> data;
	bool NotSynced;

public:
	VertexBuffer();
	~VertexBuffer();

	void Add(float value);
	void Add(glm::vec2 value);
	void Add(glm::vec3 value);
	void Add(glm::vec4 value);

	int getComponents();
	int getDataSize();

	GLuint getID();
};