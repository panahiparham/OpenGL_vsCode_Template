/* testGlut.cpp */

#include <glut.h>

#include <stdio.h>


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f(-0.5,  0.5);
    glEnd();

    glFlush();
}

void main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("testGlut");
    glutDisplayFunc(display);

    printf("%s", glGetString(GL_VERSION));

    glutMainLoop();
}