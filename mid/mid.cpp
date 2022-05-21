#include <iostream>
#include <cmath>
#include <freeglut.h>
#include <vector>
#include "mid.h"

GLfloat mx, my;
GLfloat grid_width, grid_height, left_edge, right_edge, top_edge, down_edge;
GLint dimension = 10;
std::vector<std::pair<GLfloat, GLfloat>> vertexs;

void RasterizeSelect(int option);
int jordanInside(int x, int y);
void DrawPolygon();
void (*MyRasterize)();
void MenuSelect(int option);
void GridSelect(int option);
void myDrawDot(GLint x, GLint y, GLfloat c);
void SetupRC();
void ChangeSize(int, int);
void RenderScene(void);
void midpoint(GLint x0, GLint y0, GLint x1, GLint y1);
void midpoint();
void myMouse(GLint button, GLint state, GLint x, GLint y);
void Draw2DGrid();
void GridSelect(int option);
void buildPopupMenu();

#define WINDOWS_HEIGHT 800
#define WINDOWS_WIDTH 800
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
    MyRasterize = midpoint;
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
    vertexs.clear();
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
    static GLint Dotx, Doty, x1, y1, x2, y2;

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
    vertexs.push_back({Dotx, Doty});
    myDrawDot(Dotx, Doty, 1.0f);
    std::cout << "x: " << Dotx << ", y: " << Doty << std::endl;
}

void midpoint() 
{
    std::pair<GLfloat, GLfloat> prev_pair, curr_pair;
    prev_pair = vertexs[0];
    for (int i = 1; i < vertexs.size(); i++) {
        curr_pair = vertexs[i];
        midpoint(prev_pair.first, prev_pair.second, curr_pair.first, curr_pair.second);
        prev_pair = curr_pair;
    }
    curr_pair = vertexs[0];
    midpoint(prev_pair.first, prev_pair.second, curr_pair.first, curr_pair.second);
}

void midpoint(GLint x0, GLint y0, GLint x1, GLint y1) 
{
    GLint dx, sx, dy, sy, error, e2, yi;
    GLfloat f;
    dx = std::abs(x1 - x0);
    sx = x0 < x1 ? 1: -1;
    dy = -abs(y1 - y0);
    sy = y0 < y1 ? 1: -1;
    error = dx + dy;

    while (1) {
        myDrawDot(x0, y0, 1.0f);
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
    myDrawDot(x1, y1, 1.0f);
}

void myDrawDot(GLint x, GLint y, GLfloat c)
{
    x += dimension;
    y += dimension;
    GLfloat grid_x = left_edge + x * grid_width;
    GLfloat grid_y = down_edge + y * grid_height;
    
    glBegin(GL_POLYGON);
    glColor3f(c, c, 0.0f); // White (RGB)
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
    di_20,
};

void GridSelect(int option)
{
	switch(option)
	{
	case di_10:
        dimension = 10;
		break;
	case di_15:
        dimension = 15;
		break;
	case di_20:
        dimension = 20;
        break;
	default:
        dimension = 10;
		break;
	}
    glutPostRedisplay();
}

enum {
    draw_op,
    reset_op,
    lines_op,
    polygon_op
};

void buildPopupMenu()
{
	int menu, grid_id, rasterize_id;
	grid_id = glutCreateMenu(GridSelect);
    glutAddMenuEntry("10",di_10);
    glutAddMenuEntry("15",di_15);
    glutAddMenuEntry("20",di_20);
	rasterize_id = glutCreateMenu(RasterizeSelect);
    glutAddMenuEntry("lines", lines_op);
    glutAddMenuEntry("polygon", polygon_op);
    menu = glutCreateMenu(MenuSelect);
    glutAddSubMenu("Grid size", grid_id);
    glutAddSubMenu("Rasterization mode", rasterize_id);
    glutAddMenuEntry("Draw",draw_op);
    glutAddMenuEntry("Reset",reset_op);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void RasterizeSelect(int option)
{
	switch(option)
	{
	case lines_op:
        MyRasterize = midpoint;
        break;
    case polygon_op:
        MyRasterize = DrawPolygon;
        break;
	default:
        MyRasterize = midpoint;
		break;
	}
    glutPostRedisplay();
}

void MenuSelect(int option)
{
	switch(option)
	{
	case draw_op:
        MyRasterize();
        break;
    case reset_op:
        dimension = 10;
        glutPostRedisplay();
        break;
	default:
		break;
	}
}

int jordanInside(int x, int y) 
{
    int cross = 0;
    int x0, y0, x1, y1, len;

    len = vertexs.size() - 1;
    x0 = vertexs[len].first - x;
    y0 = vertexs[len].second - y;
    for (int i = 0; i < vertexs.size(); i++) {
        x1 = vertexs[i].first - x;
        y1 = vertexs[i].second - y;
        if (y0 > 0) {
            if (y1 <= 0) {
                if (x1*y0 > y1*x0)
                    cross++;
            }
        } else
            if (y1 > 0)
                if (x0*y1 > y0*x1)
                    cross++;
        x0 = x1;
        y0 = y1;
    }

    return cross & 1;
}


void DrawPolygon() 
{
    int centerx = 0, centery = 0, xMin, xMax, yMin, yMax;
    int len = vertexs.size();

    xMin = vertexs[0].first;
    xMax = vertexs[0].first;
    yMin = vertexs[0].second;
    yMax = vertexs[0].second;
    for (unsigned int i = 0; i < len; i++) {
        if (xMin > vertexs[i].first)   //��̤j�̤p��
            xMin = vertexs[i].first;
        if (xMax < vertexs[i].first)
            xMax = vertexs[i].first;
        if (yMin > vertexs[i].second)
            yMin = vertexs[i].second;
        if (yMax < vertexs[i].second)
            yMax = vertexs[i].second;

        centerx = centerx + vertexs[i].first;  //�p��T���Ϊ������I
        centery = centery + vertexs[i].second;
    }
    centerx = centerx / len;
    centery = centery / len;
    for (int y = yMin; y <= yMax; y++) {
        for (int x = xMin; x <= xMax; x++) {
            if (jordanInside(x, y))
                myDrawDot(x, y, 1.0f);
        }
    }
}