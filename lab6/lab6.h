#pragma once

#include <freeglut.h>
#include <math.h>

static inline GLint myipart(GLfloat x) { return (int)floor(x);}
static inline GLfloat myround(GLfloat x) {return round(x);}
static inline GLfloat myfpart(GLfloat x) {return x - floor(x);}
static inline GLfloat myrfpart(GLfloat x) {return 1.0 - myfpart(x);}