#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <vector>

class EventSystem
{
	SDL_Event event = { 0 };
	std::vector<int> keys;
	glm::vec2 MousePosition;

	bool quit = false;

public:
	SDL_Event getEvent();
	bool EventLoop();
	bool isKeyDown(int key);
	int MouseHorizontal(float _windoww);
	int MouseVertical(float _windowh);
};