#include "ShaderProgram.h"
#include <iostream>
#include <String>

ShaderProgram::ShaderProgram()
{
	const GLchar *vertexShaderSrc =
		"attribute vec3 a_Position;                                             \n " \
		"attribute vec2 a_TexCoord;                                             \n " \
		"attribute vec3 a_Normal;                                               \n " \
		"                                                                       \n " \
		"uniform mat4 u_Projection;                                             \n " \
		"uniform mat4 u_View;                                                   \n " \
		"uniform mat4 u_Model;                                                  \n " \
		"                                                                       \n " \
		"varying vec2 v_TexCoord;                                               \n " \
		"varying vec3 v_Normal;                                                 \n " \
		"varying vec3 v_viewPos;                                                \n " \
		"                                                                       \n " \
		"void main()                                                            \n " \
		"{                                                                      \n " \
		"gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0); \n " \
		"v_viewPos = gl_Position;                                               \n " \
		"v_TexCoord = a_TexCoord;                                               \n " \
		"v_Normal = a_Normal;                                                   \n " \
		"vec3 v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));                \n " \
		"}                                                                      \n ";

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> infoLog(length);
		glGetShaderInfoLog(vertexShaderId, length, NULL, &infoLog.at(0));

		glDeleteShader(vertexShaderId);

		std::string msg = &infoLog.at(0);
		std::cout << msg << std::endl;
		throw std::exception();
	}

	const GLchar *fragmentShaderSrc =
		"uniform sampler2D u_Texture;                               \n" \
		"                                                           \n" \
		"uniform float ambientStrength;                             \n" \
		"uniform vec3 lightColor;                                   \n" \
		"uniform vec3 lightPos;                                     \n" \
		"uniform float specularStrength;                            \n" \
		"                                                           \n" \
		"varying vec2 v_TexCoord;                                   \n" \
		"varying vec3 v_Normal;                                     \n" \
		"varying vec3 v_FragPos;                                    \n" \
		"varying vec3 v_viewPos;                                    \n" \
		"                                                           \n" \
		"void main()                                                \n" \
		"{                                                          \n" \
		"vec3 ambient = ambientStrength * lightColor;               \n" \
		"                                                           \n" \
		"vec3 norm = normalize(v_Normal);                           \n" \
		"vec3 lightDir = normalize(lightPos - v_FragPos);           \n" \
		"                                                           \n" \
		"float diff = max(dot(norm, lightDir), 0.0);                \n" \
		"vec3 diffuse = diff * lightColor;                          \n" \
		"                                                           \n" \
		"vec3 viewDir = normalize(v_viewPos - v_FragPos);           \n" \
		"vec3 reflectDir = reflect(-lightDir, norm);                \n" \
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  \n" \
		"vec3 specular = specularStrength * spec * lightColor;      \n" \
		"                                                           \n" \
		"vec3 Maxv3 = (1, 1, 1);                                    \n" \
		"vec3 Minv3 = (0, 0, 0);                                    \n" \
		"vec3 light = (ambient + diffuse + specular);               \n" \
		"light = max(min(light, Maxv3), Minv3);                     \n" \
		"                                                           \n" \
		"vec4 tex = texture2D(u_Texture, v_TexCoord);               \n" \
		"                                                           \n" \
		"gl_FragColor = vec4(light, 1.0) * tex;                     \n" \
		"}                                                          \n";

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> infoLog(length);
		glGetShaderInfoLog(fragmentShaderId, length, NULL, &infoLog.at(0));

		glDeleteShader(fragmentShaderId);

		std::string msg = &infoLog.at(0);
		std::cout << msg << std::endl;
		throw std::exception();
	}

	const GLchar *vertexShaderUISrc =
		"attribute vec3 a_Position;                                             \n " \
		"attribute vec2 a_TexCoord;                                             \n " \
		"                                                                       \n " \
		"uniform mat4 u_Projection;                                             \n " \
		"uniform mat4 u_View;                                                   \n " \
		"uniform mat4 u_Model;                                                  \n " \
		"                                                                       \n " \
		"varying vec2 v_TexCoord;                                               \n " \
		"                                                                       \n " \
		"void main()                                                            \n " \
		"{                                                                      \n " \
		"gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0); \n " \
		"v_TexCoord = a_TexCoord;                                               \n " \
		"}                                                                      \n ";

	GLuint vertexShaderUIId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderUIId, 1, &vertexShaderUISrc, NULL);
	glCompileShader(vertexShaderUIId);
	glGetShaderiv(vertexShaderUIId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length = 0;
		glGetShaderiv(vertexShaderUIId, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> infoLog(length);
		glGetShaderInfoLog(vertexShaderUIId, length, NULL, &infoLog.at(0));

		glDeleteShader(vertexShaderUIId);

		std::string msg = &infoLog.at(0);
		std::cout << msg << std::endl;
		throw std::exception();
	}

	const GLchar *fragmentShaderUISrc =
		"uniform sampler2D u_Texture;                               \n" \
		"varying vec2 v_TexCoord;                                   \n" \
		"                                                           \n" \
		"void main()                                                \n" \
		"{                                                          \n" \
		"vec4 tex = texture2D(u_Texture, v_TexCoord);               \n" \
		"gl_FragColor = vec4(v_TexCoord.x, v_TexCoord.y, 0, 1);     \n" \
		"}                                                          \n";

	GLuint fragmentShaderUIId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderUIId, 1, &fragmentShaderUISrc, NULL);
	glCompileShader(fragmentShaderUIId);
	glGetShaderiv(fragmentShaderUIId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		int length = 0;
		glGetShaderiv(fragmentShaderUIId, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> infoLog(length);
		glGetShaderInfoLog(fragmentShaderUIId, length, NULL, &infoLog.at(0));

		glDeleteShader(fragmentShaderUIId);

		std::string msg = &infoLog.at(0);
		std::cout << msg << std::endl;
		throw std::exception();
	}
	
	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderId);
	glAttachShader(ID, fragmentShaderId);

	glBindAttribLocation(ID, 0, "a_Position");
	glBindAttribLocation(ID, 1, "a_TexCoord");
	glBindAttribLocation(ID, 2, "a_Normal");

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	modelLoc = glGetUniformLocation(ID, "u_Model");
	projectionLoc = glGetUniformLocation(ID, "u_Projection");
	viewLoc = glGetUniformLocation(ID, "u_View");
	lpLoc = glGetUniformLocation(ID, "lightPos");
	lcLoc = glGetUniformLocation(ID, "lightColor");
	asLoc = glGetUniformLocation(ID, "ambientStrength");
	ssLoc = glGetUniformLocation(ID, "specularStrength");

	glDetachShader(ID, vertexShaderId);
	glDetachShader(ID, fragmentShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	UI = glCreateProgram();
	glAttachShader(UI, vertexShaderUIId);
	glAttachShader(UI, fragmentShaderUIId);

	glBindAttribLocation(UI, 0, "a_Position");
	glBindAttribLocation(UI, 1, "a_TexCoord");

	glLinkProgram(UI);
	glGetProgramiv(UI, GL_LINK_STATUS, &success);

	if (!success)
	{
		throw std::exception();
	}

	modelUILoc = glGetUniformLocation(UI, "u_Model");
	projectionUILoc = glGetUniformLocation(UI, "u_Projection");
	viewUILoc = glGetUniformLocation(UI, "u_View");

	glDetachShader(UI, vertexShaderUIId);
	glDetachShader(UI, fragmentShaderUIId);
	glDeleteShader(vertexShaderUIId);
	glDeleteShader(fragmentShaderUIId);

}

ShaderProgram::~ShaderProgram()
{
}

GLuint ShaderProgram::getID()
{
	return ID;
}

GLuint ShaderProgram::getUI()
{
	return UI;
}

GLuint ShaderProgram::getmodelLoc()
{
	return modelLoc;
}

GLuint ShaderProgram::getprojectionLoc()
{
	return projectionLoc;
}

GLuint ShaderProgram::getviewLoc()
{
	return viewLoc;
}

GLuint ShaderProgram::getmodelUILoc()
{
	return modelUILoc;
}

GLuint ShaderProgram::getprojectionUILoc()
{
	return projectionUILoc;
}

GLuint ShaderProgram::getviewUILoc()
{
	return viewUILoc;
}

GLuint ShaderProgram::getlpLoc()
{
	return lpLoc;
}

GLuint ShaderProgram::getlcLoc()
{
	return lcLoc;
}

GLuint ShaderProgram::getasLoc()
{
	return asLoc;
}

GLuint ShaderProgram::getssLoc()
{
	return ssLoc;
}