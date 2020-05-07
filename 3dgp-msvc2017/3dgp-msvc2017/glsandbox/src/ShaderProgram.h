#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class ShaderProgram 
{
private:
	GLuint ID;
	GLuint UI;
	GLuint modelLoc;
	GLuint projectionLoc;
	GLuint viewLoc;

	GLuint modelUILoc;
	GLuint projectionUILoc;
	GLuint viewUILoc;

	GLuint lpLoc;
	GLuint lcLoc;
	GLuint asLoc;
	GLuint ssLoc;
	
public:
	ShaderProgram();
	~ShaderProgram();

	GLuint getID();
	GLuint getUI();
	GLuint getmodelLoc();
	GLuint getprojectionLoc();
	GLuint getviewLoc();
	GLuint getmodelUILoc();
	GLuint getprojectionUILoc();
	GLuint getviewUILoc();
	GLuint getlpLoc();
	GLuint getlcLoc();
	GLuint getasLoc();
	GLuint getssLoc();
	
};