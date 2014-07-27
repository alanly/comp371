//#include "DevIL.h"
//
//using namespace std;
//
//struct Image
//{
//	wchar_t * imgPath;
//	GLsizei imgHeight;
//	GLsizei imgWidth;
//	ILubyte * imgData;
//
//	Image() : imgPath(), imgHeight(), imgWidth(), imgData() {}
//	Image( wchar_t * imgPath ) : imgPath(imgPath) {}
//};
//
////Angles
//GLfloat xAngle = 0;
//GLfloat yAngle = 0;
//GLfloat zAngle = 0;
//
////Texture variables
//std::vector<Image> images;
//std::vector<wchar_t*> imgPaths;	// Image file paths
//GLuint *texName;		// Open GL texture obj array
//ILuint *ilTexName;		// DevIL images obj array
//
//GLUquadricObj *qdc = gluNewQuadric();
//
//// Initializes the DevIL Library
//void DevIL::InitDevIL()
//{
//	ilInit();
//	iluInit();
//	ilutInit();
//	ilutRenderer(ILUT_OPENGL);
//
//	glClearColor(0.0, 0.0, 0.0, 0.0); //clear the color buffers
//	glShadeModel(GL_FLAT); // type of shading: GL_FLAT or GL_SMOOTH(default)
//}
//
//// Add a new file image to DevIL's objects
//void DevIL::AddNewImage(wchar_t *textFile)
//{
//	imgPaths.push_back(textFile);
//	Image newImage(textFile);
//	images.push_back(newImage);
//}
//
//// Initializes DevIL textures
//void DevIL::InitTextures(void)
//{
//	InitDevIL();
//	// Initialize the OpenGL and DevIL Texture objects
//	texName = new GLuint[images.size()];
//	ilTexName = new ILuint[images.size()];
//
//	// Generate DevIL Image objects
//	ilGenImages(images.size(), ilTexName);
//
//	// Loads in image textures from the files
//	for (int currIndex = 0; currIndex < images.size(); currIndex++)
//	{
//		ilBindImage(ilTexName[currIndex]);
//		ilutGLBindTexImage();
//		ilLoadImage(imgPaths[currIndex]);
//		images[currIndex].imgHeight = ilGetInteger(IL_IMAGE_HEIGHT);
//		images[currIndex].imgWidth = ilGetInteger(IL_IMAGE_WIDTH);
//		images[currIndex].imgData = ilGetData();
//	}
//
//	InitTextureObjects();
//}
//
//void DevIL::InitTextureObjects(void)
//{	
//	glGenTextures(images.size(), texName);
//
//	for (int i = 0; i < images.size(); i++)
//	{
//		glBindTexture(GL_TEXTURE_2D, texName[i]); // Binds the texture
//		if (i == 1)
//		{
//			gluQuadricTexture(qdc, GL_TRUE);
//		}
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//Handles the wrapping properties of the texture
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//Handles the wrapping properties of the texture
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//Puts a magnification filter on the texture
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Puts a minification filter on the texture
//		ilutGLTexImage(0); //Draws image loaded into DevIL
//	}
//}
//
//void DevIL::Display (void)  //TODO CLEAN UP
//{
//	glEnable(GL_DEPTH_TEST);
//	glClearColor (0.0,0.0,0.0,1.0);
//	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
//
//	/* Draw and render cube with brick texture */
//	glPushMatrix();
//	//Code modified from sample program http://www.glprogramming.com/red/chapter09.html
//	glTranslatef(-1.5, 1.0, 0.0); //POSITION OF THE CUBE
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	//Handles how the texture is applied (GL_DECAL is another)
//	glBindTexture(GL_TEXTURE_2D, texName[0]);			//Bind the texture to the model
//	glBegin(GL_QUADS);
//	// Top face of the cube
//		glColor3f(1.0, 0.0, 0.0);	//Red
//		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, 0.5f, -0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);			// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);			// Bottom Right
//
//	//Bottom face of the cube
//		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, -0.5f, 0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);		// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, -0.5f);			// Bottom Right
//
//	//Front face of the cube
//		glColor3f(0.0, 0.0, 1.0);	//Blue
//		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, 0.5f, 0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, 0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, -0.5f, 0.5f);			// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f, -0.5f, 0.5f);			// Bottom Right
//
//	//Back face of the cube
//		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, 0.5f, -0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(0.5f, 0.5f, -0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(0.5f, -0.5f, -0.5f);			// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5f, -0.5f, -0.5f);		// Bottom Right
//
//	//Left face of the cube
//		glColor3f(0.0, 1.0, 0.0);	//Green
//		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5f, 0.5f, 0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5f, 0.5f, -0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5f, -0.5f, -0.5f);		// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5f, -0.5f, 0.5f);			// Bottom Right
//
//	//Right face of the cube
//		glTexCoord2f(0.0, 0.0); glVertex3f(0.5f, 0.5f,-0.5f);			// Top Right
//		glTexCoord2f(0.0, 1.0); glVertex3f(0.5f, 0.5f, 0.5f);			// Top Left
//		glTexCoord2f(1.0, 1.0); glVertex3f(0.5f,-0.5f, 0.5f);			// Bottom Left
//		glTexCoord2f(1.0, 0.0); glVertex3f(0.5f,-0.5f,-0.5f);			// Bottom Right
//	glEnd();
//	glPopMatrix();
//
//	/* Draw and render the sphere with the globe texture */
//	glPushMatrix();
//	glTranslatef(1.5, 1.0, 0.0);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);	//Handles how the texture is applied
//	glBindTexture(GL_TEXTURE_2D, texName[1]);			//Bind the texture to the model
//	gluSphere(qdc, 1.0, 50, 50);				//Draw a sphere	
//	glPopMatrix();
//
//	glFlush();
//	glDisable(GL_TEXTURE_2D);
//	
//	glutSwapBuffers();
//}
//
//void fakeMain(int argc, char*argv[])
//{
//		glutInit (&argc, argv);											//initializing glut	
//	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);		//display mode
//	glutInitWindowSize (1024, 768);									//window size
//	glutInitWindowPosition (150, 100);								//window position on the screen	
//	glutCreateWindow ("Two Cubes and a Sphere");					//title of the window
//	size_t convertedChars = 0;
//	char * brick("images/BurlywoodBrickwork.jpg");
//	wchar_t * brickW = new wchar_t[strlen(brick) + 1];
//	mbstowcs_s(&convertedChars, brickW, strlen(brick)+1, brick, _TRUNCATE);
//	//wcout << brickW << " (wchar_t *)" << endl;
//
//	char * globe("images/global_map2.jpg");
//	wchar_t * globeW = new wchar_t[strlen(globe) + 1];
//    mbstowcs_s(&convertedChars, globeW, strlen(globe) + 1, globe, _TRUNCATE);
//    // Display the result and indicate the type of string that it is.
//    //wcout << globeW << " (wchar_t *)" << endl;
//
//	//wchar_t * mychar(L"images/BurlywoodBrickwork.jpg");
//	//ILstring *brickFile(&mychar);//l"images/BurlywoodBrickwork.jpg");
//	//ILstring *globeFile(L"images/global_map2.jpg");
//	DevIL imageLoader;
//	imageLoader.AddNewImage(brickW);
//	imageLoader.AddNewImage(globeW);
//	imageLoader.InitTextures();
//	//glutDisplayFunc (Display );										//GL calling the display function to display images
//	//glutIdleFunc (Display );											//GL calling the display function when idling
//	//glutReshapeFunc (Reshape);										//GL calling the reshape function
//	//glutKeyboardFunc (Keyboard);									//GL handling the regular keyboard
//	//glutSpecialFunc (KeyboardSpecial);								//GL handling special keys
//	glutMainLoop ();	
//
//	//return 0;
//}