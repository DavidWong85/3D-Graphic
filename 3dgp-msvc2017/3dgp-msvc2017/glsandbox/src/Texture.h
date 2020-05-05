#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

#include <stb_image.h>

class Texture 
{
	GLuint ID;

public:
	Texture(std::string _path);
	~Texture();
	void LoadTexture(std::string _path);
	void Apply();
	GLuint getID();
};