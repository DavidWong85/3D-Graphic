#include "Light.h"

glm::vec3 Light::getLP()
{
	return lightpos;
}

glm::vec3 Light::getLC()
{
	return lightcolor;
}

float Light::getAS()
{
	return ambiantstrength;
}

void Light::setLP(glm::vec3 _lp)
{
	lightpos = _lp;
}

void Light::setLC(glm::vec3 _lc)
{
	lightcolor = _lc;
}

void Light::setAS(float _as)
{
	ambiantstrength = _as;
}