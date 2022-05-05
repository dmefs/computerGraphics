#include <iostream>
#include <cmath>
#include <freeglut.h>

GLfloat mx, my;
GLfloat grid_width, grid_height, left_edge, right_edge, top_edge, down_edge;
GLint dimension = 10;

void myDrawDot(GLint x, GLint y);
void SetupRC();
void ChangeSize(int, int);
void RenderScene(void);
void myDrawingLine(GLint x0, GLint y0, GLint x1, GLint y1);
void myMouse(GLint button, GLint state, GLint x, GLint y);
void Draw2DGrid();
void menuSelect(int option);
void buildPopupMenu();

#define WINDOWS_HEIGHT 400
#define WINDOWS_WIDTH 400
int main(int argc, char **argv)
{
    mx = 1;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOWS_HEIGHT, WINDOWS_WIDTH);
    glutInitWindowPosition(600, 80);
    glutCreateWindow("2D grid");
    buildPopupMenu();
    SetupRC();
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutMouseFunc(myMouse);

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
    std::cout << "w: " << w << ", h: " << h << std::endl;
    glViewport(0, 0, w, h);
    // Load the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -10, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void RenderScene(void)
{
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 15.0f, 0, 0, 0, 0, 1, 0);
    Draw2DGrid();

    glutSwapBuffers();
}

void myMouse(GLint button, GLint state, GLint x, GLint y)
{
    if (!((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)))
        return;
    GLfloat len;
    static GLint Dotx, Doty, x1, y1, x2, y2, mouseState;

    mx = x - WINDOWS_WIDTH / 2;
    my = WINDOWS_HEIGHT / 2 - y;
    if (((mx - left_edge) < 0.001) || 
        ((right_edge - mx) < 0.001) || 
        ((my - down_edge) < 0.001) || 
        ((top_edge - my) < 0.001))
        return;
    GLint index_x = (int)((mx - left_edge) / grid_width);
    GLint index_y = (int)((my - down_edge) / grid_height);

    GLfloat grid_x = left_edge + index_x * grid_width;
    GLfloat grid_y = down_edge + index_y * grid_height;
    
    Dotx = index_x - dimension;
    Doty = index_y - dimension;
    std::cout << "x: " << Dotx << ", y: " << Doty << std::endl;
    switch (mouseState) {
        case 0:
            x1 = Dotx;
            y1 = Doty;
            glutPostRedisplay();
            break;
        case 1:
            x2 = Dotx;
            y2 = Doty;
            myDrawingLine(x1, y1, x2, y2);
            break;
        default:
            std::cout << "Error: state out of 1." << std::endl;
            break;
    }
    mouseState = (mouseState + 1) % 2;
}

void myDrawingLine(GLint x0, GLint y0, GLint x1, GLint y1) 
{
    GLint dx, sx, dy, sy, error, e2;
    dx = std::abs(x1 - x0);
    sx = x0 < x1 ? 1: -1;
    dy = -abs(y1 - y0);
    sy = y0 < y1 ? 1: -1;
    error = dx + dy;

    while (1) {
        myDrawDot(x0, y0);
        if ((x0 == x1) && (y0 == y1))
            break;
        if ((e2 = 2 * error) >= dy) {
            if (x0 == x1)
                break;
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            if (y0 == y1)
                break;
            error += dx;
            y0 += sy;
        }
    }
    myDrawDot(x1, y1);
}

void myDrawDot(GLint x, GLint y)
{
    x += dimension;
    y += dimension;
    GLfloat grid_x = left_edge + x * grid_width;
    GLfloat grid_y = down_edge + y * grid_height;
    
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 0.0f); // White (RGB)
    glVertex3f(grid_x, grid_y, 0);
    glVertex3f(grid_x + grid_width, grid_y, 0);
    glVertex3f(grid_x + grid_width, grid_y + grid_height, 0);
    glVertex3f(grid_x, grid_y + grid_height, 0);
    glEnd();
    glFlush();
}

void Draw2DGrid() {
    GLint index, num, half_windows_width, half_windows_height;
    GLfloat i;

    num = 2 * dimension + 3;
    grid_width = (GLfloat)WINDOWS_WIDTH / num;
    grid_height = (GLfloat)WINDOWS_HEIGHT / num;
    half_windows_width = WINDOWS_WIDTH / 2;
    half_windows_height = WINDOWS_HEIGHT / 2;
    left_edge = -half_windows_width + grid_width;
    right_edge = half_windows_width - grid_width;
    top_edge = half_windows_height - grid_height;
    down_edge = -half_windows_height + grid_height;

        i = left_edge;
    index = num - 1;
    glBegin(GL_LINES);
    while (index--)
    {
        glColor3f(1, 0, 0);
        glVertex3f(i, top_edge, 0);
        glVertex3f(i, down_edge, 0);
        i += grid_width;
    }

    i = down_edge;
    index = num - 1;
    while (index--) {
        glColor3f(1, 0, 0);
        glVertex3f(left_edge, i, 0);
        glVertex3f(right_edge, i, 0);
        i += grid_height;
    }
    glEnd();
}

enum {
    di_10,
    di_15,
    di_20
};

void menuSelect(int option)
{
	switch(option)
	{
	case di_10:
        dimension = 10;
		glutPostRedisplay();
		break;
	case di_15:
        dimension = 15;
		glutPostRedisplay();
		break;
	case di_20:
        dimension = 20;
		glutPostRedisplay();
        break;
	default:
        dimension = 10;
		glutPostRedisplay();
		break;
	}
}

void buildPopupMenu()
{
	int menu_id;
	menu_id = glutCreateMenu(menuSelect);
    glutAddMenuEntry("10",di_10);
    glutAddMenuEntry("15",di_15);
    glutAddMenuEntry("20",di_20);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
