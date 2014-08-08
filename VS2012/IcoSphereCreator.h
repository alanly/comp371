/*#include "IcoSphereCreator.h"


IcoSphereCreator::IcoSphereCreator(void)
{
}


IcoSphereCreator::~IcoSphereCreator(void)
{
}
*/

#include <iostream>
#include <vector>
#include <map>

#ifndef PROCEDURAL_ICOSPHERE
#define PROCEDURAL_ICOSPHERE

struct Point3D
{
float x, y, z;
Point3D(float x = 0.0, float y = 0.0, float z = 0.0): x(x), y(y), z(z) {};
};
struct MeshGeometry3D
{
std::vector<Point3D> Vertexs;
std::vector<Point3D>::iterator VertexIT;
std::vector<int> TriangleIndices;
std::vector<int>::iterator TriangleIndiceIT;
Point3D* VertexArray;
int VertexArraySize;
void GenerateVertexArray()
{
  VertexArraySize = 0;
  VertexArray = new Point3D[TriangleIndices.size()-1];
  for (TriangleIndiceIT = TriangleIndices.begin(); TriangleIndiceIT != TriangleIndices.end(); ++TriangleIndiceIT)
  {
   VertexArray[VertexArraySize] = Vertexs[(*TriangleIndiceIT)];
   VertexArraySize++;
  }
}
};
class IcoSphereCreator
{
private:
struct TriangleIndices
{
  int v1, v2, v3;
  TriangleIndices(int v1, int v2, int v3): v1(v1), v2(v2), v3(v3){};
};
MeshGeometry3D Geometry;
std::vector<TriangleIndices> Faces;
std::vector<TriangleIndices>::iterator FaceIT;
std::map<int, int> MiddlePointIndex;
std::map<int, int>::iterator MiddlePointIndexIT;
int Index;
int AddVertex( Point3D p)
{
  float length = sqrt( p.x*p.x + p.y*p.y + p.z*p.z);
  Geometry.Vertexs.push_back( Point3D( p.x/length, p.y/length, p.z/length) );
  return Index++;
}
void AddFace( int vert1, int vert2, int vert3)
{
  Faces.push_back( TriangleIndices(vert1, vert2, vert3) );
}
int GetMiddlePoint(int p1, int p2)
{
  // first check if we have it already

  bool FirstIsSmaller = p1 < p2;
  int SmallerIndex = FirstIsSmaller ? p1 : p2;
  int GreaterIndex = FirstIsSmaller ? p2 : p1;
  int Key = (SmallerIndex << 16) + GreaterIndex;
  if (MiddlePointIndex.count(Key) > 0)
  {
   //std::cout << "yes" << std::endl;
   return MiddlePointIndex.find(Key)->second;
  }
  // not in cache, calculate it
  Point3D point1 = Geometry.Vertexs[p1];
  Point3D point2 = Geometry.Vertexs[p2];
  Point3D middle = Point3D((point1.x + point2.x) / 2,
		 (point1.y + point2.y) / 2,
		 (point1.z + point2.z) / 2);
  // add vertex makes sure point is on unit sphere
  int i = AddVertex(middle);
  // store it, return index
  MiddlePointIndex.insert(std::pair<int, int>(Key, i));
  return i;
}
public:
IcoSphereCreator()
{
  Index = 0;
}
MeshGeometry3D Create(int RecursionLevel)
{
  float t = (float)((1.0 + sqrt(5.0)) / 2.0);
  AddVertex( Point3D(-1.0,  t, 0.0));
  AddVertex( Point3D( 1.0,  t, 0.0));
  AddVertex( Point3D(-1.0, -1, 0.0));
  AddVertex( Point3D( 1.0, -t, 0.0));
  AddVertex( Point3D(0.0, -1,  t));
  AddVertex( Point3D(0.0,  1,  t));
  AddVertex( Point3D(0.0, -1, -t));
  AddVertex( Point3D(0.0,  1, -t));
  AddVertex(  Point3D(t, 0.0, -1));
  AddVertex(  Point3D(t, 0.0,  1));
  AddVertex( Point3D(-t, 0.0, -1));
  AddVertex( Point3D(-t, 0.0,  1));
  // 5 faces around point 0
  AddFace( 0, 11, 5 );
  AddFace( 0, 5,  1 );
  AddFace( 0, 1,  7 );
  AddFace( 0, 7,  10);
  AddFace( 0, 10, 11);
  // 5 adjacent faces
  AddFace( 1,  5,  9 );
  AddFace( 5,  11, 4 );
  AddFace( 11, 10, 2 );
  AddFace( 10, 7,  6 );
  AddFace( 7,  1,  8 );
  // 5 faces around point 3
  AddFace( 3, 9, 4 );
  AddFace( 3, 4, 2 );
  AddFace( 3, 2, 6 );
  AddFace( 3, 6, 8 );
  AddFace( 3, 8, 9 );
  // 5 adjacent faces
  AddFace( 4, 9, 5 );
  AddFace( 2, 4, 11);
  AddFace( 6, 2, 10);
  AddFace( 8, 6, 7 );
  AddFace( 9, 8, 1 );
  for (int i = 0; i < RecursionLevel; i++)
  {
   std::vector<TriangleIndices> Faces2;
   std::vector<TriangleIndices>::iterator Face2IT;
   for (FaceIT = Faces.begin(); FaceIT != Faces.end(); ++FaceIT)
   {
	int a = GetMiddlePoint((*FaceIT).v1, (*FaceIT).v2);
	int b = GetMiddlePoint((*FaceIT).v2, (*FaceIT).v3);
	int c = GetMiddlePoint((*FaceIT).v3, (*FaceIT).v1);
	Faces2.push_back( TriangleIndices((*FaceIT).v1, a, c));
	Faces2.push_back( TriangleIndices((*FaceIT).v2, b, a));
	Faces2.push_back( TriangleIndices((*FaceIT).v3, c, b));
	Faces2.push_back( TriangleIndices(a, b, c));
   }
   Faces = Faces2;
  }
  for (FaceIT = Faces.begin(); FaceIT != Faces.end(); ++FaceIT)
  {
   Geometry.TriangleIndices.push_back((*FaceIT).v1);
   Geometry.TriangleIndices.push_back((*FaceIT).v3);
   Geometry.TriangleIndices.push_back((*FaceIT).v2);
  }
  return Geometry;
}
};
#endif