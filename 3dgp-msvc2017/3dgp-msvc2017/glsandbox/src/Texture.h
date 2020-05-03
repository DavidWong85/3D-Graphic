#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include <stb_image.h>

class Texture 
{
	GLuint ID;

public:
	void LoadTexture(std::string _path);
	GLuint getID();
};