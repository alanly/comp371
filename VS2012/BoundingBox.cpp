#include "BoundingBox.h"
//#include "Model.h"
#include <vector>
#include <gl\glew.h>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>


BoundingBox::BoundingBox()//Model* m)
{
/*	//only "works" for spheres right now but cubes are their own bounding boxes and its a quick and easy implementation afterwards

	if(m == sphereModel)
	{
		center = sphereModel.center;
		halfSize = sphereModel.sphereRadius;
	}



}


BoundingBox::~BoundingBox(void)
{
}


bool BoundingBox::isColliding(Model* m1, Model* m2)
{
	float dist = glm::sqrt( (m1.center.x-m2.center.x)*(m2.center.x-m2.center.x) + (m1.center.y-m2.center.y)*(m2.center.y-m2.center.y) + (m1.center.z-m2.center.z)*(m2.center.z-m2.center.z); //covers only spheres currently

  if(dist <= m1.halfSize + m2.halfSize)
  {

	  return True; //meaning they're colliding
	  //we need to run isColliding every time we make a sphere move and every time a sphere is created.
	  // this can ensure that no spheres collide, if so though, we can have them change color (if we're just moving spheres).
	  //something like access the pointer, delete the values that its at, and then create a new sphere at that pointer value with diff color
  }
  else
  {
	  return False;
  }

  */
} 

