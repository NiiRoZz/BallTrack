// BallTrack.cpp : Defines the entry point for the application.
//

#include "BallTrack.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Drawables/Triangle.h"
#include "Drawables/Model3D.h"
#include "Math/Sc3D.h"
#include "Math/Dir3D.h"
#include "Utils/ObjLoader.h"

using namespace BallTrack;

Triangle triangle;
Triangle triangle2;
Model3D model3D;

float scale = 1.f;

bool pMode = true;

static float rx = 0.0F;            
static float sens = 1.0F;          
static float ry = 0.0F;           
static float rz = 0.0F;

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
	std::cout << "scale : " << scale << std::endl;
	model3D.setScale(Sc3D(scale));


	std::cout << "rx : " << rx << std::endl;
	std::cout << "ry : " << ry << std::endl;
	std::cout << "rz : " << rz << std::endl;


	//Rt3D rot =reinterpret_cast<Rt3D>( Rt3D(ry, Dir3D(0.0f, 1.0f, 0.f)) * Rt3D(rx, Dir3D(1.0f, 0.0f, 0.f)));

	model3D.setRotation(Rt3D(rx, Dir3D(1.0f, 0.0f, 0.f)));
	//model3D.setRotation(Rt3D(ry, Dir3D(0.0f, 1.0f, 0.f)));
	//model3D.setRotation(Rt3D(rz, Dir3D(0.0f, 0.0f, 1.0f)));


	model3D.render();
	glPopMatrix();
}

static void display(void)
{
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == true) ? GL_FILL : GL_LINE);
	
	scene();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}
static void keyboard(unsigned char key, int , int )
{
	switch (key)
	{
		case 'f':
		case 'F':
		{
			static bool fullScreen = false;
			static int tx;
			static int ty;
			static int px;
			static int py;
			fullScreen = !fullScreen;
			if (fullScreen)
			{
				px = glutGet(GLUT_WINDOW_X);
				py = glutGet(GLUT_WINDOW_Y);
				tx = glutGet(GLUT_WINDOW_WIDTH);
				ty = glutGet(GLUT_WINDOW_HEIGHT);
				glutFullScreen();
			}
			else
			{
				glutPositionWindow(px, py);
				glutReshapeWindow(tx, ty);
			}
		}
		break;

		case 'z':
		{ 
			pMode = !pMode;
			glutPostRedisplay();
		}
		break;

		case 'o':
		{
			scale -= 0.1f;
			glutPostRedisplay();
		}
		break;

		case 'p':
		{
			scale += 0.1f;
			glutPostRedisplay();
		}
		break;
	}
}


static void special(int specialKey, int x, int y) {
	switch (specialKey) {
	case GLUT_KEY_RIGHT:
		ry += 0.1F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		ry -= 0.1F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		 rx += 0.1F;
		 glutPostRedisplay();
		 break;
	case GLUT_KEY_DOWN:
		rx += 0.1F;
		glutPostRedisplay();
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
	glutSpecialFunc(special);

	glutReshapeFunc(reshape);
	//glutSpecialFunc(special);
	glutDisplayFunc(display);

	triangle.setRotation(Rt3D(1.57f, Dir3D(0.f, 0.f, 1.f)));
	triangle.setScale(Sc3D(1.f));

	triangle2.setScale(Sc3D(1.f));

	std::vector<Triangle> triangles({triangle, triangle2});
	model3D = Model3D(triangles);

	ObjLoader loader;
	loader.loadObjFile("models/", "untitled");

	glutMainLoop();
	return 0;
}
