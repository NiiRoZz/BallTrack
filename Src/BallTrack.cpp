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
#include "Entities/RectangleEntity.h"

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

//camera moving in x
/*
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
float fraction = 0.1f;
*/


SphereEntity* bille = nullptr;

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
		glOrtho(-ratio*3, ratio*3 , -1.0*3  , 1.0*3 , -50000, 50000);
	else
		glOrtho(-1.0*3, 1.0*3, -1.0 / (ratio*3), 1.0 / (ratio*3), -50000, 50000);
	
	//glOrtho(-ortho, ortho, -ortho, ortho, -250, 250);
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
		//std::cout << "Position : " << entity->getPosition().x << " " << entity->getPosition().y << " " << entity->getPosition().z << std::endl;
		//entity->setScale(Sc3D(scale));
		entity->setRotation(rot);
		entity->render();
	}

	std::cout << std::endl;

	glPopMatrix();
}

static void display(void)
{
	//camera moving in x
	/*
	gluLookAt(x, 0.0f, z,
		x + lx, 0.0f, z + lz,
		0.0f, 1.0f, 0.0f);*/

	glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (pMode == true) ? GL_FILL : GL_LINE);

	scene();
	glFlush();
	glLoadIdentity();
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
		/*
		case 'v':
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'n':
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'g':
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 'b':
			x -= lx * fraction;
			z -= lz * fraction;
			break;*/
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
	case GLUT_KEY_F1:
		rz += 0.1F;
		glutPostRedisplay();
		break;
	case GLUT_KEY_F2:
		rz -= 0.1F;
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
		//Update position entity from velocity, only physic entities
		for (auto& entity: allEntities)
		{
			PhysicEntity* physicEntity = dynamic_cast<PhysicEntity*>(entity.get());

			if (physicEntity != nullptr)
			{
				physicEntity->update(dtSeconds);
			}
		}

		//Update static collisions only physic entities
		std::vector<std::pair<SphereEntity*, PhysicEntity*>> collidingPairs;
		for (auto& entity: allEntities)
		{
			SphereEntity* sphereEntity = dynamic_cast<SphereEntity*>(entity.get());

			if (sphereEntity != nullptr)
			{
				for (auto& target: allEntities)
				{
					PhysicEntity* physicTarget = dynamic_cast<PhysicEntity*>(target.get());

					if (physicTarget != nullptr)
					{
						if (sphereEntity != physicTarget && sphereEntity->resolveCollision(physicTarget))
						{
							collidingPairs.emplace_back(sphereEntity, physicTarget);
						}
					}
				}
			}
		}

		// Now work out dynamic collisions
		for (const auto& c : collidingPairs)
		{
			c.first->dynamicCollision(c.second);
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

	std::vector<Model3D> cubes = ObjLoader::loadObjFile("../data/BallTrack/models/", "cube");

	std::cout << "nmb cubes : " << cubes.size() << std::endl;

	if (cubes.size() > 0)
	{
		std::unique_ptr<RectangleEntity> cubeEntity = std::make_unique<RectangleEntity>(cubes[0]);
		cubeEntity->setSize({1.f, 1.f, 1.f});
		cubeEntity->setPosition(Pos3D(0.0f, -1.f, 0.f));
		cubeEntity->setScale(Sc3D(3.f, 1.f, 3.f));
		allEntities.push_back(std::move(cubeEntity));
	}

	std::vector<Model3D> spheres = ObjLoader::loadObjFile("../data/BallTrack/models/", "sphere");

	std::cout << "nmb spheres : " << spheres.size() << std::endl;

	if (spheres.size() > 0)
	{
		{
			std::unique_ptr<SphereEntity> sphereEntity = std::make_unique<SphereEntity>(spheres[0]);
			sphereEntity->setRadius(1.f);
			sphereEntity->setPosition(Pos3D(0.0f, 0.9f, 0.f));
			bille = sphereEntity.get();// if bille != null ptr 
			allEntities.push_back(std::move(sphereEntity));
		}

		{
			std::unique_ptr<SphereEntity> sphereEntity = std::make_unique<SphereEntity>(spheres[0]);
			sphereEntity->setRadius(1.f);
			sphereEntity->setPosition(Pos3D(1.0f, 0.9f, 0.f));
			allEntities.push_back(std::move(sphereEntity));
		}
	}

	glutMainLoop();
	return 0;
}
