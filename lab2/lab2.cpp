#include <stdio.h>
#include <stdlib.h>
#include <freeglut.h>

int x, y, z, tx, ty, tz, thetaX, thetaY, thetaZ;
void SetupRC();
void ChangeSize(int, int);
void RenderScene(void);
void myKeyboard(unsigned char key, int x, int y);
void mySpecialKey(int key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("Moving Cube");
    SetupRC();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKey);

    glutMainLoop();
    return 0;
}
void SetupRC()
{
    // Light values and coordinates
    GLfloat whiteLight[] = {0.45f, 0.45f, 0.45f, 1.0f};
    GLfloat sourceLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    GLfloat lightPos[] = {0.0f, 25.0f, 20.0f, 0.0f};

    // Turns on lighting
    glEnable(GL_LIGHTING);

    // Setup and turn on light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);

    // Turn on color tracking
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
}

void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
    // Load the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10.0f, 0, 0, 0, 0, 1, 0);
    // Draw x, y, z axis
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -100);
    glVertex3f(0, 0, 100);
    glEnd();

    // perform transformation for the cube
    glLoadIdentity();
    glTranslatef(tx, ty, tz);
    glRotatef(thetaX, 1, 0, 0);
    glRotatef(thetaY, 0, 1, 0);
    glRotatef(thetaZ, 0, 0, 1);
    // Cube
    glColor3f(1, 1, 0);
    glutSolidCube(6);
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        thetaX = thetaY = thetaZ = 0;
        tx = ty = tz = 0;        
        break;
    case 'a':
        thetaX += 3;
        break;
    case 'd':
        thetaX -= 3;
        break;
    case 'w':
        thetaY += 3;
        break;
    case 's':
        thetaY -= 3;
        break;
    case 'z':
        thetaZ += 3;
        break;
    case 'x':
        thetaZ -= 3;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

#define MOVE_UNIT 2
void mySpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        tx -= MOVE_UNIT;
        break;
    case GLUT_KEY_RIGHT:
        tx += MOVE_UNIT;
        break;
    case GLUT_KEY_UP:
        ty += MOVE_UNIT;
        break;
    case GLUT_KEY_DOWN:
        ty -= MOVE_UNIT;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
