#include "BillboardModel.h"
#include "Renderer.h"

BillboardModel::BillboardModel(glm::vec3 p1, glm::vec3 p2, glm::vec3 normal, float width, glm::vec3 color) : RectangleModel(p1, p2, normal, width, color)
{
	mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Billboard.vertexshader", "../Source/Shaders/Billboard.fragmentshader");
}


BillboardModel::~BillboardModel(void)
{
}


void BillboardModel::Draw()
{
	
}