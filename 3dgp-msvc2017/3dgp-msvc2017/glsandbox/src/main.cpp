#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <exception>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

  bool quit = false;

  const GLfloat positions[] =
  {
	  0.0f, 0.5f, 0.0f,
	  -0.5f, -0.5f, 0.0f,
	  0.5f, -0.5f, 0.0f
  };

  const GLfloat colors[] = {
  1.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 1.0f,
  };

  GLuint positionsVboId = 0;

  glGenBuffers(1, &positionsVboId);

  if (!positionsVboId)
  {
	  throw std::exception();
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
  glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  GLuint vaoId = 0;

  glGenVertexArrays(1, &vaoId);

  if (!vaoId)
  {
	  throw std::exception();
  }

  glBindVertexArray(vaoId);
  glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

  glEnableVertexAttribArray(0); //For streaming VBO (Positions)

  GLuint colorsVboId = 0;

  glGenBuffers(1, &colorsVboId);

  if (!colorsVboId)
  {
	  throw std::exception();
  }

  glBindBuffer(GL_ARRAY_BUFFER, colorsVboId);

  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);

  glEnableVertexAttribArray(1);
  

  //Reset The State
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);


  const GLchar *vertexShaderSrc =
	  "attribute vec3 a_Position;                                     " \
	  "attribute vec4 a_Color;                                        " \
	  "uniform mat4 u_Projection;                                     " \
	  "uniform mat4 u_Model;                                          " \
	  "                                                               " \
	  "varying vec4 v_Color;                                          " \
	  "                                                               " \
	  "void main()                                                    " \
	  "{                                                              " \
	  " gl_Position = u_Projection * u_Model * vec4(a_Position, 1.0); " \
	  " v_Color = a_Color;                                            " \
	  "}                                                              ";

  GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShaderId);
  GLint success = 0;
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  const GLchar *fragmentShaderSrc =
	  "varying vec4 v_Color;                 " \
	  "uniform vec4 u_Color;                 " \
	  "void main()                           " \
	  "{                                     " \
	  " gl_FragColor = v_Color + u_Color;    " \
	  "}                                     ";

  GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  GLuint programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);

  glBindAttribLocation(programId, 0, "a_Position");
  glBindAttribLocation(programId, 1, "a_Color");

  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &success);

  if (!success)
  {
	  throw std::exception();
  }

  glDetachShader(programId, vertexShaderId);
  glDeleteShader(vertexShaderId);
  glDetachShader(programId, fragmentShaderId);
  glDeleteShader(fragmentShaderId);

  GLint modelLoc = glGetUniformLocation(programId, "u_Model");
  GLint projectionLoc = glGetUniformLocation(programId, "u_Projection");


  GLint colorUniformId = glGetUniformLocation(programId, "u_Color");

  if (colorUniformId == -1)
  {
	  throw std::exception();
  }

  float angle = 0;

  while (!quit)
  {
	  SDL_Event event = { 0 };

	  while (SDL_PollEvent(&event))
	  {
		  if (event.type == SDL_QUIT)
		  {
			  quit = true;
		  }
	  }

	  int width = 0;
	  int height = 0;

	  SDL_GetWindowSize(window, &width, &height);

	  glViewport(0, 0, width, height);

	  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);

	  glUseProgram(programId);

	  glUniform4f(colorUniformId, 1, 0, 0, 0); //To change color 
	  glBindVertexArray(vaoId);


	  //Prepare the perspective projection matrix
	  glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);

	  //Prepare the model matrix
	  glm::mat4 model(1.0f);
	  model = glm::translate(model, glm::vec3(0, 0, -2.5f));
	  model = glm::rotate(model, glm::radians(angle), glm::vec3(1, 0, 0)); //vec3(x, y, z) used to change rotate direction
	  model = glm::rotate(model, glm::radians(angle / 2.0f), glm::vec3(0, 0, 1));
	  model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));

	  //Increase the float angle so next frame the triangle rotates further
	  angle += 10.0f;

	  //Make sure the current program is bound

	  //Upload the model matrix
	  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	  //Upload the projection matrix
	  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	  glDrawArrays(GL_TRIANGLES, 0, 3);

	  //Prepare the orthographic projection matrix
	  projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f);

	  //Prepare model matrix for orthographic projection
	  model = glm::mat4(1.0f);
	  model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
	  model = glm::scale(model, glm::vec3(100, 100, 1));

	  //Upload the model matrix
	  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	  //Upload the projection matrix
	  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	  glDrawArrays(GL_TRIANGLES, 0, 3);

	  glBindVertexArray(0);
	  glUseProgram(0);
	  SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}