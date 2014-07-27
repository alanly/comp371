#include "Text2DModel.h"
#include "Common/Text2DUtils.h"

const char* fontTexture = "../Assets/ComicNeueLight.dds";

Text2DModel::Text2DModel(const char* message, unsigned int size, int x, int y, Model* parent)
{
	// Set parent model
	mParent = parent;

	tMessage = message;
	fSize = size;
	SetPosition(glm::vec3(x, y, 0));

	initText2D(fontTexture);
}


Text2DModel::~Text2DModel(void)
{
	cleanupText2D();
}

void Text2DModel::Update(float dt)
{
}

void Text2DModel::Draw()
{
	printText2D(tMessage, GetPosition().x, GetPosition().y, fSize);
}