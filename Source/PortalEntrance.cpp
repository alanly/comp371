#include "PortalEntrance.h"
#include "ArcModel.h"
// author: Tim Smith

PortalEntrance::PortalEntrance(glm::vec3 Position,glm::vec3 Normal, glm::vec3 Binormal,int numParts){
	mNormal = Normal;
	mBiNormal = Binormal;
	for(int i=0; i<numParts;i++){
		glm::vec4 arcCol;
		arcCol.x = ((float)rand()/(float)(RAND_MAX)) * 1.0f;
		arcCol.y = ((float)rand()/(float)(RAND_MAX)) * 1.0f;
		arcCol.z = ((float)rand()/(float)(RAND_MAX)) * 1.0f;
		arcCol.w = 1.0f;
		
	//	arcCol = glm::vec4(0.0f,0.0f,0.0f,1.0f);

		float innerRad = ((float)rand()/(float)(RAND_MAX)) * 1.0f + 1.4f;
		
		float outerRad = ((float)rand()/(float)(RAND_MAX)) * 1.0f + innerRad + 0.3f;

		float angle = ((float)rand()/(float)(RAND_MAX)) * 270.0f;
		glm::vec3 posOffset = glm::cross(Binormal,Normal);
		ArcModel * arc = new ArcModel(arcCol,arcCol, //glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f),
			Position+(posOffset*0.001f*(float)i), Normal,Binormal,
			innerRad, outerRad, angle, 8);

		arc->SetRotation(posOffset,(360.0f/numParts)*i);
		arc->SetParent(this);
		collection.push_back(arc);
	}


	setCollisionBoxSize(glm::vec3(2.0f));
}

PortalEntrance::~PortalEntrance(void)
{
}

void PortalEntrance::Update(float dt){
	for(int i=0;i<collection.size();i++){
		float angle =  i;
		collection[i]->SetRotation(glm::cross(mNormal,mBiNormal),collection[i]->GetRotationAngle()+(angle*0.3f));
	}
}

void PortalEntrance::Draw(){
	for(int i = 0; i<collection.size();i++){
		collection[i]->Draw();
	}
}