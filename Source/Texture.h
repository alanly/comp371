// Include GLEW - OpenGL Extension Wrangler
#define GLEW_STATIC
#include <GL/glew.h>

class Texture
{
public:
	static GLuint loadDDS(const char * imagepath);
};