// BallTrack.cpp : Defines the entry point for the application.
//

#include "BallTrack.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <memory>

#include "Drawables/Triangle.h"
#include "Drawables/Model3D.h"
#include "Math/Sc3D.h"
#include "Math/Dir3D.h"
#include "Math/TG3D.h"
#include "Utils/ObjLoader.h"
#include "Entities/SphereEntity.h"

using namespace BallTrack;

std::vector<std::unique_ptr<Entity>> allEntities;

float scale = 1.f;

bool pMode = true;

static float rx = 0.0F;            
//static float sens = 1.0F;          
static float ry = 0.0F;           
static float rz = 0.0F;

static int oldTime;

static const unsigned int TARGET_UPDATE_FPMS = 16;

//60 FPS
//We make it a little bit slower than 16, because GLUT only use int and milliseconds, so we cannot say the real 60 FPS, so it will be 16 frames per second
static const float TARGET_UPDATE_FPS = 0.015989f;

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

	oldTime = glutGet(GLUT_ELAPSED_TIME);
}

static void reshape(int wx, int wy) {
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = (double)wx / wy;
	if (wx > wy)
		glOrtho(-ratio, ratio, -1.0, 1.0, -50000, 50000);
	else
		glOrtho(-1.0, 1.0, -1.0 / ratio, 1.0 / ratio, -50000, 50000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void scene(void) {
	glPushMatrix();

	std::cout << "scale : " << scale << std::endl;
	std::cout << "rx : " << rx << std::endl;
	std::cout << "ry : " << ry << std::endl;
	std::cout << "rz : " << rz << std::endl;

	Rt3D rot = Rt3D(ry, Dir3D(0.0f, 1.0f, 0.f)) * Rt3D(rx, Dir3D(1.0f, 0.0f, 0.f)) * Rt3D(rz, Dir3D(0.0f, 0.0f, 1.f));

	for (auto& entity : allEntities)
	{
		entity->setScale(Sc3D(scale));
		entity->setRotation(rot);
		entity->render();
	}

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


static void special(int specialKey, int , int ) {
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
		rx -= 0.1F;
		glutPostRedisplay();
		break;
	}
}

static void updateEntities(int )
{
	int t = glutGet(GLUT_ELAPSED_TIME);
	float dtSeconds = (t - oldTime) / 1000.f;
	oldTime = t;

	//std::cout << "Elapsed time : " << dtSeconds << std::endl;

	//Just to be sure physics is updated the number of time needed per frame
	for (float i = dtSeconds; i >= TARGET_UPDATE_FPS; i -= TARGET_UPDATE_FPS)
	{
		for (auto& entity: allEntities)
		{
			entity->update(dtSeconds);
		}
	}

	glutPostRedisplay();
	glutTimerFunc(TARGET_UPDATE_FPMS, updateEntities, 1);
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
	glutDisplayFunc(display);
	glutTimerFunc(TARGET_UPDATE_FPMS, updateEntities, 1);

	std::vector<Model3D> allModels = ObjLoader::loadObjFile("../models/", "untitled");

	std::cout << "nmb models : " << allModels.size() << std::endl;

	if (allModels.size() > 0)
	{
		allEntities.push_back(std::make_unique<SphereEntity>(allModels[0]));
	}

	glutMainLoop();
	return 0;
}
