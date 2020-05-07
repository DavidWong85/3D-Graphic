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

float Light::getSS()
{
	return specularstrength;
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

void Light::setSS(float _ss)
{
	specularstrength = _ss;
}