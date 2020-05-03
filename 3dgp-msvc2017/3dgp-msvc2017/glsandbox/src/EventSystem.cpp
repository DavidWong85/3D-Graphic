#include "EventSystem.h"

SDL_Event EventSystem::getEvent()
{
	return event;
}

bool EventSystem::EventLoop()
{
	while (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_QUIT) || (isKeyDown(SDLK_ESCAPE)))
		{
			quit = true;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			keys.push_back(event.key.keysym.sym);
		}
		else if (event.type == SDL_KEYUP)
		{
			for (size_t ki = 0; ki < keys.size(); ki++)
			{
				if (keys.at(ki) == event.key.keysym.sym)
				{
					keys.erase(keys.begin() + ki);
					ki--;
				}
			}
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			MousePosition.x = event.motion.x;
			MousePosition.y = event.motion.y;
		}
		return quit;
	}
}

bool EventSystem::isKeyDown(int key)
{
	for (size_t ki = 0; ki < keys.size(); ki++)
	{
		if (keys.at(ki) == key)
		{
			return true;
		}
	}
	return false;
}

int EventSystem::MouseHorizontal(float _windoww)
{
	return MousePosition.x - (_windoww / 2);
}

int EventSystem::MouseVertical(float _windowh)
{
	return MousePosition.y - (_windowh / 2);
}