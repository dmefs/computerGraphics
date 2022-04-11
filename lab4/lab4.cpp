#include <iostream>
#include <cmath>
#include <freeglut.h>

enum MyAxis
{
    x_axis,
    y_axis,
    z_axis
};

GLfloat translateMatrix[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0};

GLfloat rotMatrix_X[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0};

GLfloat rotMatrix_Y[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0};

GLfloat rotMatrix_Z[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0};

GLfloat scalMatrix[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0};

GLfloat mx, my, tx, ty, tz, thetaX, thetaY, thetaZ, sx, sy, sz;
void SetupRC();
void ChangeSize(int, int);
void RenderScene(void);
void myKeyboard(unsigned char key, int x, int y);
void mySpecialKey(int key, int x, int y);
void myTranslatef();
void myScalingf();
void myRotatef(enum MyAxis a);
void myMouse(GLint button, GLint state, GLint x, GLint y);

#define WINDOWS_HEIGHT 400
#define WINDOWS_WIDTH 400
int main(int argc, char **argv)
{
    sx = sy = sz = 1;
    mx = 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOWS_HEIGHT, WINDOWS_WIDTH);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("Moving Cube");
    SetupRC();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutKeyboardFunc(myKeyboard);
    glutMouseFunc(myMouse);
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
    // Draw random axis
    glColor3f(1, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(mx * 100, my * 100, 0);
    glEnd();

    // perform transformation for the cube
    glLoadIdentity();
    // scaling
    myScalingf();
    // glTranslatef(tx, ty, tz);
    myTranslatef();
    // glRotatef(thetaX, 1, 0, 0);
    myRotatef(x_axis);
    // glRotatef(thetaY, 0, 1, 0);
    myRotatef(y_axis);
    // glRotatef(thetaZ, 0, 0, 1);
    myRotatef(z_axis);
    //  Cubw
    glColor3f(1, 1, 0);
    glutSolidCube(6);
    glutSwapBuffers();
}

#define SCALE_UNIT 0.1
#define ROTATION_UNIT 3

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        thetaX = thetaY = thetaZ = 0;
        tx = ty = tz = 0;
        break;
    case 'a':
        thetaX += ROTATION_UNIT;
        break;
    case 'd':
        thetaX -= ROTATION_UNIT;
        break;
    case 'w':
        thetaY += ROTATION_UNIT;
        break;
    case 's':
        thetaY -= ROTATION_UNIT;
        break;
    case 'z':
        thetaZ += ROTATION_UNIT;
        break;
    case 'x':
        thetaZ -= ROTATION_UNIT;
        break;
    case 'j':
        sx += SCALE_UNIT;
        break;
    case 'k':
        sy += SCALE_UNIT;
        break;
    case 'l':
        sz += SCALE_UNIT;
        break;
    case 'u':
        sx -= SCALE_UNIT;
        break;
    case 'i':
        sy -= SCALE_UNIT;
        break;
    case 'o':
        sz -= SCALE_UNIT;
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

static inline float getSin(float theta)
{
    return sin(theta * M_PI / 180.0);
}

static inline float getCos(float theta)
{
    return cos(theta * M_PI / 180.0);
}

void myTranslatef()
{
    translateMatrix[12] = tx;
    translateMatrix[13] = ty;
    translateMatrix[14] = tz;
    glMultMatrixf(translateMatrix);
}
void myRotateMatrixAssignf(GLfloat *m, GLfloat theta, GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat cos, sin;

    cos = getCos(theta);
    sin = getSin(theta);
    m[0] = cos + (1 - cos) * x * x;
    m[1] = (1 - cos) * x * y + sin * z;
    m[2] = (1 - cos) * z * x - sin * y;
    m[4] = (1 - cos) * x * y - sin * z;
    m[5] = cos + (1 - cos) * y * y;
    m[6] = (1 - cos) * z * y + sin * x;
    m[8] = (1 - cos) * x * z + sin * y;
    m[9] = (1 - cos) * y * z - sin * x;
    m[10] = cos + (1 - cos) * z * z;

    glMultMatrixf(m);
}

void myRotatef(enum MyAxis a)
{
    switch (a)
    {
    case x_axis:
        myRotateMatrixAssignf(rotMatrix_X, thetaX, mx, my, 0);
        break;

    case y_axis:
        myRotateMatrixAssignf(rotMatrix_Y, thetaY, my, -mx, 0);
        break;

    case z_axis:
        rotMatrix_Z[0] = getCos(thetaZ);
        rotMatrix_Z[1] = getSin(thetaZ);
        rotMatrix_Z[4] = -getSin(thetaZ);
        rotMatrix_Z[5] = getCos(thetaZ);
        glMultMatrixf(rotMatrix_Z);
        break;

    default:
        std::cout << "error" << std::endl;
        break;
    }
}

void myScalingf()
{
    scalMatrix[0] = sx;
    scalMatrix[5] = sy;
    scalMatrix[10] = sz;
    glMultMatrixf(scalMatrix);
}

void myMouse(GLint button, GLint state, GLint x, GLint y)
{
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
    {
        GLfloat len;
        mx = x - WINDOWS_WIDTH / 2;
        my = WINDOWS_HEIGHT / 2 - y;
        len = sqrt(mx * mx + my * my);
        mx = mx / len;
        my = my / len;
    }
    glutPostRedisplay();
}