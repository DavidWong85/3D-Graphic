#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

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

	GLuint getID();
	GLuint getmodelLoc();
	GLuint getprojectionLoc();
	GLuint getviewLoc();
	GLuint getlpLoc();
	GLuint getlcLoc();
	GLuint getasLoc();
	
};