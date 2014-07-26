#pragma once

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <glut\glut.h>
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

class DevIL
{
public:
	DevIL();
	~DevIL();
	static void InitDevIL();
	void AddNewImage(wchar_t* file);
	void InitTextures(void);
	void InitTextureObjects(void);
	void Display(void);
};