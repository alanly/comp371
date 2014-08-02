#pragma once

#include "Model.h"

class Text2DModel : public Model
{
public:
	Text2DModel(const char* message, unsigned int size = 32, int x = 0, int y = 0, Model* parent = NULL);
	~Text2DModel(void);

	virtual void Update(float dt);
	virtual void Draw();

private:
	const char*  tMessage;
	unsigned int fSize;

	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	unsigned int Text2DUniformID;

	void initText2D(const char * texturePath);
	void printText2D(const char * text, int x, int y, int size);
	void cleanupText2D();
};

