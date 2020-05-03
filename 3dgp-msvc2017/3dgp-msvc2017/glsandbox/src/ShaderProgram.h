#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class VertexArray;
class Texture;

class ShaderProgram 
{
	GLuint ID;
	GLint modelLoc;
	GLint projectionLoc;
	GLuint viewLoc;
	GLint lpLoc;
	GLuint lcLoc;
	GLuint asLoc;
	

public:
	ShaderProgram();
	~ShaderProgram();
	void Draw(VertexArray* va);
	void setUniform(std::string _uniform, glm::vec4 _value);
	void setUniform(std::string _uniform, float _value);
	void setUniform(std::string _uniform, Texture* texture);
	
	GLuint getID();
	GLuint getmodelLoc();
	GLuint getprojectionLoc();
	GLuint getviewLoc();
	GLuint getlpLoc();
	GLuint getlcLoc();
	GLuint getasLoc();
	
};