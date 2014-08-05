#include "BillboardModel.h"
#include "Renderer.h"
#include "Common/TextureUtils.h"

BillboardModel::BillboardModel(glm::vec3 p1, glm::vec3 p2, glm::vec3 normal, float width, glm::vec3 color) : RectangleModel(p1, p2, normal, width, color)
{
	mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Billboard.vertexshader", "../Source/Shaders/Billboard.fragmentshader");

	BillboardPosID = glGetUniformLocation(mShaderProgramID, "BillboardPos");
	BillboardSizeID = glGetUniformLocation(mShaderProgramID, "BillboardSize");

	TextureID  = glGetUniformLocation(mShaderProgramID, "myTextureSampler");
	Texture = loadDDS("../Assets/ExampleBillboard.DDS");
}


BillboardModel::~BillboardModel(void)
{
	glDeleteTextures(1, &TextureID);
	glDeleteProgram(mShaderProgramID);
}


void BillboardModel::Draw()
{
	glUniform3f(BillboardPosID, 0.0f, 0.5f, 0.0f); // The billboard will be just above the cube
	glUniform2f(BillboardSizeID, 1.0f, 0.125f);     // and 1m*12cm, because it matches its 256*32 resolution =)

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	RectangleModel::Draw();
}