

#pragma once
#//include "Model.h"


class BoundingBox
{
public:
	BoundingBox();//Model* m);

	~BoundingBox(void);

	//bool isColliding(Model* m1, Model* m2);


	


private:
	float xMin;
	float xMax;
	float yMin;
	float yMax;
	float zMin;
	float zMax;

	//glm::vec3 m_center;
	//glm::vec3 m_halfSize;

};
