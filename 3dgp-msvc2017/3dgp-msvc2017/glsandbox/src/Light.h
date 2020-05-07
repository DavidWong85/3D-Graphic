#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class Light
{
private:
	glm::vec3 lightpos;     //lp
	glm::vec3 lightcolor;   //lc
	float ambiantstrength;  //as
	float specularstrength; //ss

public:
	glm::vec3 getLP();
	glm::vec3 getLC();
	float getAS();
	float getSS();

	void setLP(glm::vec3 _lp);
	void setLC(glm::vec3 _lc);
	void setAS(float _as);
	void setSS(float _ss);
};