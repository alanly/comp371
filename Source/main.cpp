//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

#include "Renderer.h"
#include "World.h"
#include "EventManager.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "DevIL.h"

int main(int argc, char*argv[])
{
	glutInit (&argc, argv);											//initializing glut	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);		//display mode
	glutInitWindowSize (1024, 768);									//window size
	glutInitWindowPosition (150, 100);								//window position on the screen	
	glutCreateWindow ("Two Cubes and a Sphere");					//title of the window
	size_t convertedChars = 0;
	char * brick("images/BurlywoodBrickwork.jpg");
	wchar_t * brickW = new wchar_t[strlen(brick) + 1];
	mbstowcs_s(&convertedChars, brickW, strlen(brick)+1, brick, _TRUNCATE);
	//wcout << brickW << " (wchar_t *)" << endl;

	char * globe("images/global_map2.jpg");
	wchar_t * globeW = new wchar_t[strlen(globe) + 1];
    mbstowcs_s(&convertedChars, globeW, strlen(globe) + 1, globe, _TRUNCATE);
    // Display the result and indicate the type of string that it is.
    //wcout << globeW << " (wchar_t *)" << endl;

	//wchar_t * mychar(L"images/BurlywoodBrickwork.jpg");
	//ILstring *brickFile(&mychar);//l"images/BurlywoodBrickwork.jpg");
	//ILstring *globeFile(L"images/global_map2.jpg");
	DevIL imageLoader;
	imageLoader.AddNewImage(brickW);
	imageLoader.AddNewImage(globeW);
	imageLoader.InitTextures();
	glutDisplayFunc (Display );										//GL calling the display function to display images
	glutIdleFunc (Display );											//GL calling the display function when idling
	//glutReshapeFunc (Reshape);										//GL calling the reshape function
	//glutKeyboardFunc (Keyboard);									//GL handling the regular keyboard
	//glutSpecialFunc (KeyboardSpecial);								//GL handling special keys
	glutMainLoop ();	

	return 0;
}
