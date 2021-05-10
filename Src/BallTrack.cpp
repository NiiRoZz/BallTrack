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
#include "Entities/Entity.h"
#include "Entities/PhysicEntity.h"

#include <cassert>

using namespace BallTrack;

std::vector<std::unique_ptr<Entity>> allEntities;

bool pMode = true;
bool cameraMode = false;
bool showPrimitives = false;

int f1, f2;

static float rx = 0.0F;
//static float sens = 1.0F;          
static float ry = 0.0F;
static float rz = 0.0F;

static int oldTime;

static bool updatePhysic = true;

static PhysicEntity* bille = nullptr;
static const Pos3D DefaultCameraPos(1500.0f, 1000.0f, 500.0f);
static const Pos3D CameraToBille(0.0f, 0.0f, -500.0f);

static const Pos3D StartPosition(0.0f, 40.9f, 8.f);
static const float RestartY = 0.f;

//60 FPS
static const unsigned int TARGET_UPDATE_FPMS = 16;
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
	glEnable(GL_TEXTURE_2D);

	oldTime = glutGet(GLUT_ELAPSED_TIME);
}

static void reshape(int wx, int wy) {
	glViewport(0, 0, wx, wy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ratio = (double)wx / wy;
	if (wx > wy)
		glOrtho(-ratio * 10, ratio * 10, -1.0 * 10, 1.0 * 10, 0.001f, 50000);
	else
		glOrtho(-1.0 * 10, 1.0 * 10, -1.0 / (ratio * 10), 1.0 / (ratio * 10), 0.0001f, 50000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void scene(void) {
	glPushMatrix();

	for (auto& entity : allEntities)
	{
		entity->render();
	}

	glPopMatrix();
}

static void display(void)
{
	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == true) ? GL_FILL : GL_LINE);
	glPushMatrix();
	if (bille != nullptr)
	{
		if (!cameraMode) {
			Pos3D setPosition = (bille->getPosition() + DefaultCameraPos);
			gluLookAt(setPosition.x, setPosition.y, setPosition.z, bille->getPosition().x, bille->getPosition().y, bille->getPosition().z, 0.f, 1.f, 0.f);
		}
		else {
			Pos3D setPosition = (bille->getPosition() + CameraToBille);
			gluLookAt(bille->getPosition().x, bille->getPosition().y, bille->getPosition().z, setPosition.x, setPosition.y, setPosition.z, 0.f, 1.f, 0.f);
		}
	}
	else {
		gluLookAt(20.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	}
	
	//glRotatef(rx, 1.f, 0.f, 0.f);
	//glRotatef(ry, 0.f, 1.f, 0.f);
	//glRotatef(rz, 0.f, 0.f, 1.f);
	
	scene();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}
static void keyboard(unsigned char key, int, int)
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
			glutSetWindow(f1);
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
	case 'Z':
	{
		pMode = !pMode;

		int currWindow = glutGetWindow();
		glutPostRedisplay();
		glutSetWindow((currWindow == f1) ? f2 : f1);
		glutPostRedisplay();
		glutSetWindow(currWindow);
	}
	break;

	case 'a':
	case 'A':
	{
		showPrimitives = !showPrimitives;

		int currWindow = glutGetWindow();
		glutPostRedisplay();
		glutSetWindow((currWindow == f1) ? f2 : f1);
		glutPostRedisplay();
		glutSetWindow(currWindow);
	}
	break;

	case 'g':
	case 'G':
	{
		updatePhysic = !updatePhysic;

		int currWindow = glutGetWindow();
		glutPostRedisplay();
		glutSetWindow((currWindow == f1) ? f2 : f1);
		glutPostRedisplay();
		glutSetWindow(currWindow);
	}
	break;

	}

}


static void special(int specialKey, int, int) {
	switch (specialKey) {
	case GLUT_KEY_RIGHT:
		ry += 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		ry -= 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		rx += 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		rx -= 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F1:
		rz += 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:
		rz -= 2.0F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F3:
	{
		cameraMode = !cameraMode;
		
		int currWindow = glutGetWindow();
		glutPostRedisplay();
		glutSetWindow((currWindow == f1) ? f2 : f1);
		glutPostRedisplay();
		glutSetWindow(currWindow);
		break;
	}
	}
}

static void updateEntities(int)
{
	int t = glutGet(GLUT_ELAPSED_TIME);
	float dtSeconds = (t - oldTime) / 1000.f;
	oldTime = t;

	if (updatePhysic)
	{
		//Just to be sure physics is updated the number of time needed per frame
		for (float i = dtSeconds; i >= TARGET_UPDATE_FPS; i -= TARGET_UPDATE_FPS)
		{
			//Update position entity from velocity, only physic entities
			for (auto& entity : allEntities)
			{
				PhysicEntity* physicEntity = dynamic_cast<PhysicEntity*>(entity.get());

				if (physicEntity != nullptr)
				{
					physicEntity->update(TARGET_UPDATE_FPS);
				}
			}

			//Update collisions
			for (auto& entity : allEntities)
			{
				PhysicEntity* physicEntity = dynamic_cast<PhysicEntity*>(entity.get());

				if (physicEntity != nullptr)
				{
					for (auto& target : allEntities)
					{
						PhysicEntity* physicTarget = dynamic_cast<PhysicEntity*>(target.get());

						if (physicTarget != nullptr)
						{
							if (physicEntity != physicTarget)
							{
								physicEntity->resolveCollision(physicTarget);

								if (!physicEntity->isStatic() && physicEntity->getPosition().y < RestartY)
								{
									physicEntity->setPosition(StartPosition);
								}
							}
						}
					}
				}
			}
		}

		glutPostRedisplay();
	}

	glutTimerFunc(TARGET_UPDATE_FPMS, updateEntities, 1);
}

void printText(int x, int y, std::string string)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(x, y);
	for (auto c : string)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
}

static void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	auto stringFullScreen = std::string("'F' to toggle full screen display");
	auto stringWireFrame = std::string("'Z' to toggle wire frame display : ");
	stringWireFrame.append((!pMode ? "on" : "off"));
	auto stringPrimitives = std::string("'A' to toggle primitives display : ");
	stringPrimitives.append((showPrimitives ? "on" : "off"));
	auto stringCamera = std::string("'F3' to switch camera mode : ");
	stringCamera.append((!cameraMode ? "3rd person" : "1st person"));
	auto stringUpdatePhysic = std::string("'G' to toggle the physic : ");
	stringUpdatePhysic.append((updatePhysic ? "on" : "off"));

	printText(24, 40, stringFullScreen);
	printText(24, 80, stringWireFrame);
	printText(24, 120, stringPrimitives);
	printText(24, 160, stringCamera);
	printText(24, 200, stringUpdatePhysic);

	glutSwapBuffers();
	int error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Attention erreur %d\n", error);
}

void reshape2(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	f1 = glutCreateWindow("BallTrack");
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(TARGET_UPDATE_FPMS, updateEntities, 1);

	{
		auto circuit = ObjLoader::loadEntity("../data/BallTrack/models/", "circuit_test_1");
		assert(circuit.get());
		circuit->setStatic(true);
		circuit->setPosition(Pos3D(0.0f, 0.f, 0.f));
		circuit->setScale(Sc3D(1.f, 1.f, 1.f));
		allEntities.push_back(std::move(circuit));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition);
		sphere->setScale(Sc3D(1.f));
		bille = sphere.get();
		allEntities.push_back(std::move(sphere));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition + Pos3D(0.f, 2.f, 0.f));
		sphere->setScale(Sc3D(1.f));
		allEntities.push_back(std::move(sphere));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition + Pos3D(0.f, 10.f, 0.f));
		sphere->setScale(Sc3D(1.f));
		allEntities.push_back(std::move(sphere));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition + Pos3D(0.f, 0.f, -2.f));
		sphere->setScale(Sc3D(1.f));
		allEntities.push_back(std::move(sphere));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition + Pos3D(0.f, 2.f, -2.f));
		sphere->setScale(Sc3D(1.f));
		allEntities.push_back(std::move(sphere));
	}

	{
		auto sphere = ObjLoader::loadEntity("../data/BallTrack/models/", "sphere");
		assert(sphere.get());
		sphere->setPosition(StartPosition + Pos3D(0.f, 10.f, -2.f));
		sphere->setScale(Sc3D(1.f));
		allEntities.push_back(std::move(sphere));
	}

	glutInitWindowSize(500, 230);
	glutInitWindowPosition(900, 50);
	f2 = glutCreateWindow("Settings");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutDisplayFunc(display2);
	glutReshapeFunc(reshape2);

	glutMainLoop();
	return 0;
}
