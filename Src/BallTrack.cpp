// BallTrack.cpp : Defines the entry point for the application.
//

#include "BallTrack.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Drawables/Triangle.h"
#include "Math/Sc3D.h"
#include "Math/Dir3D.h"

using namespace BallTrack;

Triangle triangle;
Triangle triangle2;


static int pMode = 1;


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

static void reshape(int wx, int wy) {
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = (double)wx / wy;
	if (wx > wy)
		glOrtho(-ratio, ratio, -1.0, 1.0, -1.0, 1.0);
	else
		glOrtho(-1.0, 1.0, -1.0 / ratio, 1.0 / ratio, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void scene(void) {
	glPushMatrix();
	triangle.render();
	triangle2.render();
	glPopMatrix();
}

static void display(void)
{
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == 1) ? GL_FILL : GL_LINE);
	scene();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}
static void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'f':
	case 'F':
	{ static int fullScreen = 0;
	static int tx;
	static int ty;
	static int px;
	static int py;
	fullScreen = !fullScreen;
	if (fullScreen) {
		px = glutGet(GLUT_WINDOW_X);
		py = glutGet(GLUT_WINDOW_Y);
		tx = glutGet(GLUT_WINDOW_WIDTH);
		ty = glutGet(GLUT_WINDOW_HEIGHT);
		glutFullScreen();
	}
	else
		glutPositionWindow(px, py);
	glutReshapeWindow(tx, ty); }
	break;

	case 'z':
	{ pMode = !pMode;
	glutPostRedisplay(); }
	break;

	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 320);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("BallTrack");
	init();
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	//glutSpecialFunc(special);
	glutDisplayFunc(display);

	triangle.setRotation(Rt3D(1.57f, Dir3D(0.f, 0.f, 1.f)));
	triangle.setScale(Sc3D(1.f));

	triangle2.setScale(Sc3D(1.f));

	glutMainLoop();
	return 0;
}
