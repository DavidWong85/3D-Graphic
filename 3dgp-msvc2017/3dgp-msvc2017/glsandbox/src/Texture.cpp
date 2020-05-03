#include "Texture.h"

void Texture::LoadTexture(std::string _path)
{
	int w = 0;
	int h = 0;

	unsigned char *data = stbi_load(_path.c_str(), &w, &h, NULL, 4);

	if (!data)
	{
		throw std::exception();
	}

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getID()
{
	return ID;
}