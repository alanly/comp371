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
};

