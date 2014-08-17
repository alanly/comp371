/**
 * @author Alan Ly
 */

#pragma once

#include "SOIL.h"


class Image
{
public:
	Image(const char* filepath);
	~Image(void);

	unsigned char* GetImage(void) { return imageArray; }
	int GetWidth(void) { return width; }
	int GetHeight(void) { return height; }

private:
	unsigned char* imageArray;
	int width, height;

	void LoadImage(const char* filepath);
	void DeleteImage(unsigned char* image);
};

