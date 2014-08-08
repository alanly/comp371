#include "BillboardModel.h"
#include "Renderer.h"
#include "Common/ShaderUtils.h"
#include "Common/TextureUtils.h"
#include "GLFW/glfw3.h"

BillboardModel::BillboardModel(glm::vec3 p1, glm::vec3 p2, glm::vec3 normal, float width, glm::vec3 color) : RectangleModel(p1, p2, normal, width, color)
{
	glGenVertexArrays(1, &BillboardVertexArrayID);
	glBindVertexArray(BillboardVertexArrayID);

	mShaderProgramID = Renderer::LoadShaders("../Source/Shaders/Billboard.vertexshader", "../Source/Shaders/Billboard.fragmentshader");

	BillboardPosID = glGetUniformLocation(mShaderProgramID, "BillboardPos");
	BillboardSizeID = glGetUniformLocation(mShaderProgramID, "BillboardSize");

	LifeLevelID = glGetUniformLocation(mShaderProgramID, "LifeLevel");

	TextureID  = glGetUniformLocation(mShaderProgramID, "myTextureSampler");
	Texture = loadDDS("../Assets/ExampleBillboard.DDS");

	GLfloat g_vertex_buffer_data[] = {
		-0.5f,	-0.5f,	0.f,
		 0.5f,	-0.5f,	0.f,
		-0.5f,	 0.5f,  0.f,
		 0.5f,	 0.5f,	0.f
	};

	glGenBuffers(1, &BillboardBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BillboardBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
}


BillboardModel::~BillboardModel(void)
{
	glDeleteBuffers(1, &BillboardBufferID);
	glDeleteTextures(1, &TextureID);
	glDeleteProgram(mShaderProgramID);
	glDeleteVertexArrays(1, &BillboardVertexArrayID);
}


void BillboardModel::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUniform3f(BillboardPosID, 0.0f, 0.5f, 0.0f); // The billboard will be just above the cube
	glUniform2f(BillboardSizeID, 1.0f, 0.125f);     // and 1m*12cm, because it matches its 256*32 resolution =)

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	float LifeLevel = sin(glfwGetTime())*0.1f + 0.7f;
	glUniform1f(LifeLevelID, LifeLevel);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, BillboardBufferID);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);

	/*RectangleModel::Draw();*/
}