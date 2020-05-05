#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <string>
#include <fstream>

class VertexBuffer;
class VertexArray;

class Model
{
	std::shared_ptr<VertexBuffer> vbp;
	std::shared_ptr<VertexBuffer> vbt;
	std::shared_ptr<VertexBuffer> vbn;
	std::shared_ptr<VertexArray> va;

	/*
	VertexBuffer* vbp; //position
	VertexBuffer* vbt; //texture coordinate
	VertexBuffer* vbn; //normal
	VertexArray* va;
	*/
public:
	Model(std::string path);
	~Model();

	void SplitStringWhiteSpace(const std::string& input, std::vector<std::string>& output);
	void SplitString(const std::string& input, char splitter, std::vector<std::string>& output);
	void LoadModel(const std::string& path);
	void Draw();
};