// Block.cpp
// OpenGL SuperBible, Chapter 1
// Demonstrates an assortment of basic 3D concepts
// Program by Richard S. Wright Jr.

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

/***freeglut***/
#include <freeglut.h>

// Keep track of effects step
int nStep = 0;

// Lighting data
GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat lightDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightSpecular[] = {0.9f, 0.9f, 0.9f};
GLfloat materialColor[] = {0.8f, 0.0f, 0.0f};
GLfloat vLightPos[] = {-80.0f, 120.0f, 100.0f, 0.0f};
GLfloat ground[3][3] = {{0.0f, -25.0f, 0.0f},
			{10.0f, -25.0f, 0.0f},
			{10.0f, -25.0f, -10.0f}};

GLuint textures[4];

// Called to draw scene
void RenderScene(void)
{

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glPushMatrix();

	// Draw plane that the cube rests on
	glDisable(GL_LIGHTING);

	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.0f, -25.3f, -100.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100.0f, -25.3f, 100.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100.0f, -25.3f, 100.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(100.0f, -25.3f, -100.0f);
	glEnd();

	// Set drawing color to Red
	glColor3f(1.0f, 0.0f, 0.0f);

	// Move the cube slightly forward and to the left
	glTranslatef(-10.0f, 0.0f, 10.0f);

	glColor3ub(255, 255, 255);
	// glGetFloatv(GL_MODELVIEW_MATRIX, mCubeTransform);

	// Front Face (before rotation)
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(25.0f, 25.0f, 25.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(25.0f, -25.0f, 25.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-25.0f, -25.0f, 25.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-25.0f, 25.0f, 25.0f);
	glEnd();

	// Top of cube
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(25.0f, 25.0f, 25.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(25.0f, 25.0f, -25.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-25.0f, 25.0f, -25.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-25.0f, 25.0f, 25.0f);
	glEnd();

	// Last two segments for effect
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(25.0f, 25.0f, -25.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(25.0f, -25.0f, -25.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(25.0f, -25.0f, 25.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(25.0f, 25.0f, 25.0f);
	glEnd();

	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context.
void SetupRC()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures(4, textures);
	std::string image_strs[4] = {"floor", "Block4", "Block5", "Block6"};
    GLint i = 0;

	for (auto &s : image_strs)
	{
		// Load the texture objects
		cv::Mat image = cv::imread("./block/" + s + ".jpg");

		if (image.empty())
		{
			std::cout << "image empty" << std::endl;
		}
		else
		{
			cv::flip(image, image, 0);
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image.ptr());
			glDisable(GL_TEXTURE_2D);
		}
        i++;
	}
}

void KeyPressFunc(unsigned char key, int x, int y)
{
	if (key == 32)
	{
		nStep++;

		if (nStep > 5)
			nStep = 0;
	}

	// Refresh the Window
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	// Calculate new clipping volume
	GLfloat windowWidth;
	GLfloat windowHeight;

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	// Keep the square square
	if (w <= h)
	{
		windowHeight = 100.0f * (GLfloat)h / (GLfloat)w;
		windowWidth = 100.0f;
	}
	else
	{
		windowWidth = 100.0f * (GLfloat)w / (GLfloat)h;
		windowHeight = 100.0f;
	}

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the clipping volume
	glOrtho(-100.0f, windowWidth, -100.0f, windowHeight, -200.0f, 200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, vLightPos);

	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(330.0f, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Texture Demo");
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(KeyPressFunc);
	glutDisplayFunc(RenderScene);

	SetupRC();

	glutMainLoop();
	glDeleteTextures(4, textures);
	return 0;
}
