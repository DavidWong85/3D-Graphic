#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Light.h"
#include "EventSystem.h"
#include "MovementSystem.h"

#include <exception>

#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

float deltaTime;
float lastTime;
glm::vec3 position(0, 0, 0); 
float rotation = 0;
float angle = 0;
float speed = 5.0f;
float sensitivity = 0.08;

Uint32 StartTicks;
int frame = 0;

void StartTime()
{
	StartTicks = SDL_GetTicks();
}

Uint32 getTicks()
{
	Uint32 time = 0;

	time = SDL_GetTicks() - StartTicks;

	return time;
}

int main(int argc, char *argv[])
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    throw std::exception();
  }

  SDL_Window *window = SDL_CreateWindow("Triangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  if (!SDL_GL_CreateContext(window))
  {
	  throw std::exception();
  }
  if (glewInit() != GLEW_OK)
  {
	  throw std::exception();
  }

  SDL_ShowCursor(0);

  bool quit = false;

#pragma region Class
  Texture* texture = new Texture();
  ShaderProgram* SP = new ShaderProgram();
  Model* mm = new Model("resources/curuthers.obj");  //Object Location
  Model* mm2 = new Model("resources/cube.obj");
  Light* light = new Light();
  EventSystem* ES = new EventSystem();
  MovementSystem* MS = new MovementSystem();
#pragma endregion

  StartTime();

  texture->LoadTexture("resources/Whiskers_diffuse.png"); //Texture Location

  light->setLP(glm::vec3(10, 10, 0));
  light->setLC(glm::vec3(1, 1, 1));
  light->setAS(0.1);

  while (!quit)
  {
	  float avgFPS = frame / (getTicks() / 1000.0f);
	  
	  if (avgFPS > 2000000)
	  {
		  avgFPS = 0;
	  }
	  
	  std::cout << "Average Frames Per Second " << avgFPS << std::endl;

	  quit = ES->EventLoop();

	  float now = SDL_GetTicks();
	  deltaTime = (now - lastTime) / 1000.0f;
	  lastTime = now;

	  int width = 0;
	  int height = 0;

	  SDL_GetWindowSize(window, &width, &height);

	  SDL_WarpMouseInWindow(window, width / 2, height / 2);
	  
	  glViewport(0, 0, width, height);

	  glClearColor(1.0f, 1.0f, 0.5f, 1.0f);  //background color
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  glUseProgram(SP->getID());
	  glBindTexture(GL_TEXTURE_2D, texture->getID());

#pragma region Camera Movement
	  rotation -= ES->MouseHorizontal(width) * sensitivity;
	  angle -= ES->MouseVertical(height) * sensitivity;
	  if (angle >= 120.0f)
	  {
		  angle = 120;
	  }
	  if (angle <= -120.0f)
	  {
		  angle = -120;
	  }
	  
#pragma endregion

#pragma region Movement
	  if (ES->isKeyDown(SDLK_w))
	  {
		  position = MS->MoveForward(deltaTime, rotation, position);
	  }
	  if (ES->isKeyDown(SDLK_s))
	  {
		  position = MS->MoveBackward(deltaTime, rotation, position);
	  }
	  if (ES->isKeyDown(SDLK_a))
	  {
		  position = MS->MoveLeft(deltaTime, rotation, position);
	  }
	  if (ES->isKeyDown(SDLK_d))
	  {
		  position = MS->MoveRight(deltaTime, rotation, position);
	  }
#pragma endregion

#pragma region Light
	  glUniform3fv(SP->getlpLoc(), 1, glm::value_ptr(light->getLP()));
	  glUniform3fv(SP->getlcLoc(), 1, glm::value_ptr(light->getLC()));
	  glUniform1f(SP->getasLoc(), light->getAS());
	  //check light position
	  if (ES->isKeyDown(SDLK_l))
	  {
		  light->setLP(light->getLP() + glm::vec3(0, 0, 1));
	  }
#pragma endregion

#pragma region Draw 1
	  //Prepare the perspective projection matrix
	  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	  //Prepare the model matrix
	  glm::mat4 model = glm::mat4(1.0f);
	  model = glm::translate(model, glm::vec3(0, 0, -10));

	  glm::mat4 view = glm::mat4(1.0f);
	  view = glm::translate(view, position);
	  view = glm::rotate(view, glm::radians(rotation), glm::vec3(0, 1, 0));
	  view = glm::rotate(view, glm::radians(angle / 2), glm::vec3(1, 0, 0));
	  view = glm::inverse(view);

	  //Make sure the current program is bound

	  //Upload the model matrix
	  glUniformMatrix4fv(SP->getmodelLoc(), 1, GL_FALSE, glm::value_ptr(model));

	  //Upload the projection matrix
	  glUniformMatrix4fv(SP->getprojectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

	  //Upload the view matrix
	  glUniformMatrix4fv(SP->getviewLoc(), 1, GL_FALSE, glm::value_ptr(view));

	  //Alpha Blending
	  glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	  //Depth Testing
	  glEnable(GL_DEPTH_TEST);
	  //Backface Culling
	  glEnable(GL_CULL_FACE);

	  mm->Draw();
	  glDisable(GL_CULL_FACE);
	  glDisable(GL_BLEND);
#pragma endregion

#pragma region Draw 2
	  //Prepare the orthographic projection matrix
	  projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f);

	  //Prepare model matrix for orthographic projection
	  model = glm::mat4(1.0f);
	  model = glm::translate(model, glm::vec3(0, WINDOW_HEIGHT - 100, 0));
	  model = glm::scale(model, glm::vec3(100, 100, 1));

	  //Upload the model matrix
	  glUniformMatrix4fv(SP->getmodelLoc(), 1, GL_FALSE, glm::value_ptr(model));

	  glUniformMatrix4fv(SP->getviewLoc(), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0)));

	  //Upload the projection matrix
	  glUniformMatrix4fv(SP->getprojectionLoc(), 1, GL_FALSE, glm::value_ptr(projection));

	  mm2->Draw();
#pragma endregion

	  glUseProgram(0);
	  SDL_GL_SwapWindow(window);
	  frame++;
  }

  glDisable(GL_DEPTH_TEST);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

