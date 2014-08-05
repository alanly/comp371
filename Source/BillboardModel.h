#pragma once
#include "rectanglemodel.h"
class BillboardModel : public RectangleModel
{
public:
	BillboardModel(glm::vec3 p1, glm::vec3 p2, glm::vec3 normal, float width, glm::vec3 color);
	~BillboardModel(void);
	void Draw();

private:
	unsigned int BillboardPosID;
	unsigned int BillboardSizeID;
	unsigned int TextureID;
	unsigned int Texture;
};

