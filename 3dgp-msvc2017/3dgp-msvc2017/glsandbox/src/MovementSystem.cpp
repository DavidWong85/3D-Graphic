#include "MovementSystem.h"

glm::vec3 MovementSystem::Move(float _deltaTime, glm::vec3 _position, float _rotation, glm::vec3 _direction)
{
	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(_rotation), glm::vec3(0, 1, 0));
	glm::vec4 tmp = model * glm::vec4(_direction, 1);
	_position += glm::vec3(tmp * speed * _deltaTime);
	return _position;
}

glm::vec3 MovementSystem::MoveForward(float _deltaTime, float _rotation, glm::vec3 _position)
{
	return Move(_deltaTime, _position, _rotation, glm::vec3(0, 0, -1));
}

glm::vec3 MovementSystem::MoveBackward(float _deltaTime, float _rotation, glm::vec3 _position)
{
	return Move(_deltaTime, _position, _rotation, glm::vec3(0, 0, 1));
}

glm::vec3 MovementSystem::MoveLeft(float _deltaTime, float _rotation, glm::vec3 _position)
{
	return Move(_deltaTime, _position, _rotation, glm::vec3(-1, 0, 0));
}

glm::vec3 MovementSystem::MoveRight(float _deltaTime, float _rotation, glm::vec3 _position)
{
	return Move(_deltaTime, _position, _rotation, glm::vec3(1, 0, 0));
}