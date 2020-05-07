#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class MovementSystem
{
private:
	float rotation = 0;
	float speed = 5.0f;
	glm::vec4 Dir;

public:
	glm::vec3 Move(float _deltaTime,float _rotation, glm::vec3 _position, glm::vec3 _direction);
	glm::vec3 MoveForward(float _deltaTime, float _rotation, glm::vec3 _position);
	glm::vec3 MoveBackward(float _deltaTime, float _rotation, glm::vec3 _position);
	glm::vec3 MoveLeft(float _deltaTime, float _rotation, glm::vec3 _position);
	glm::vec3 MoveRight(float _deltaTime, float _rotation, glm::vec3 _position);
};