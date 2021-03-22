// BallTrack.cpp : Defines the entry point for the application.
//

#include "BallTrack.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static void init(void) {
	const GLfloat shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
}

static void reshape(int x, int y) {
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70.0F, (float)x / y, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display(void)
{
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 320);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("BallTrack");
	init();
	//glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	//glutSpecialFunc(special);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
