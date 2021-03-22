// BallTrack.cpp : Defines the entry point for the application.
//

#include "BallTrack.h"

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 320);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Un circuit matérialisé par des anneaux");
	return 0;
}
