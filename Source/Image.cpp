/**
 * @author Alan Ly
 */

#include "Image.h"


Image::Image(const char* filepath)
{
	LoadImage(filepath);
}


Image::~Image(void)
{
	DeleteImage(imageArray);
}


void Image::LoadImage(const char* filepath)
{
	imageArray = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);
}


void Image::DeleteImage(unsigned char* image)
{
	SOIL_free_image_data(image);
}