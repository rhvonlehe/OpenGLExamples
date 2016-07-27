#include "simpleglwindow.h"

void SimpleGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, width(), height());
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

