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
#include "Camera/Camera.h"

#include <cassert>

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

static TG3D projectionMatrix;
static const Pos3D DefaultCameraPos = Pos3D(0.0f, 0.0f, 4.0f);
static Camera camera(DefaultCameraPos, Pos3D(0.f, 0.f, 0.f), Dir3D(0.f, 1.f, 0.f));
static PhysicEntity* bille = nullptr;

//60 FPS
//We make it a little bit slower than 16, because GLUT only use int and milliseconds, so we cannot say the real 60 FPS, so it will be 16 frames per second
static const float TARGET_UPDATE_FPS = 0.015989f;

namespace BallTrack
{
	/*static TG3D perspective(const float fovy,
		const float aspect,
		const float zNear,
		const float zFar) 
	{
		assert(aspect != 0.f);
		assert(zFar != zNear);

		const float rad = fovy;
		const float tanHalfFovy = std::tan(rad / 2.f);
		TG3D result(0.f);
		result.mat[0][0] = 1.f / (aspect * tanHalfFovy);
		result.mat[1][1] = 1.f / (tanHalfFovy);
		result.mat[2][2] = -(zFar + zNear) / (zFar - zNear);
		result.mat[3][2] = -1.f;
		result.mat[2][3] = -(2.f * zFar * zNear) / (zFar - zNear);
		return result;
	}*/

	static TG3D ortho(
		const float left,
		const float right,
		const float bottom,
		const float top,
		const float zNear,
		const float zFar)
	{
		TG3D result;
		result.mat[0][0] = 2.f / (right - left);
		result.mat[1][1] = 2.f / (top - bottom);
		result.mat[2][2] = - 2.f / (zFar - zNear);
		result.mat[0][3] = -(right + left) / (right - left);
		result.mat[1][3] = -(top + bottom) / (top - bottom);
		result.mat[2][3] = -(zFar + zNear) / (zFar - zNear);
		return result;
	}

}

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
		projectionMatrix = BallTrack::ortho(-ratio * 3, ratio * 3, -1.0 * 3, 1.0 * 3, 0.001f, 50000);
	else
		projectionMatrix = BallTrack::ortho(-1.0 * 3, 1.0 * 3, -1.0 / (ratio * 3), 1.0 / (ratio * 3), 0.0001f, 50000);

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
	TG3D viewProjection = projectionMatrix * camera.getViewMatrix();

	for (auto& entity : allEntities)
	{
		//std::cout << "Position : " << entity->getPosition().x << " " << entity->getPosition().y << " " << entity->getPosition().z << std::endl;
		entity->setRotation(rot);
		entity->render(viewProjection);
	}

	std::cout << std::endl;

	glPopMatrix();
}

static void display(void)
{
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

	//Just to be sure physics is updated the number of time needed per frame
	for (float i = dtSeconds; i >= TARGET_UPDATE_FPS; i -= TARGET_UPDATE_FPS)
	{
		//Update position entity from velocity, only physic entities
		for (auto& entity: allEntities)
		{
			PhysicEntity* physicEntity = dynamic_cast<PhysicEntity*>(entity.get());

			if (physicEntity != nullptr)
			{
				physicEntity->update(TARGET_UPDATE_FPS);
			}
		}

		//Update static collisions only physic entities
		std::vector<std::pair<PhysicEntity*, PhysicEntity*>> collidingPairs;
		for (auto& entity: allEntities)
		{
			PhysicEntity* physicEntity = dynamic_cast<PhysicEntity*>(entity.get());

			if (physicEntity != nullptr)
			{
				for (auto& target: allEntities)
				{
					PhysicEntity* physicTarget = dynamic_cast<PhysicEntity*>(target.get());

					if (physicTarget != nullptr)
					{
						if (physicEntity != physicTarget && physicEntity->resolveCollision(physicTarget))
						{
							collidingPairs.emplace_back(physicEntity, physicTarget);
						}
					}
				}
			}
		}

		// Now work out dynamic collisions
		/*for (const auto& c : collidingPairs)
		{
			c.first->dynamicCollision(c.second);
		}*/
	}

	if (bille != nullptr)
	{
		camera.setPosition(bille->getPosition() + DefaultCameraPos);
		camera.setCenter(bille->getPosition());
	}

	glutPostRedisplay();
	glutTimerFunc(TARGET_UPDATE_FPMS, updateEntities, 1);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
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
		std::unique_ptr<PhysicEntity> cubeEntity = std::make_unique<PhysicEntity>(cubes[0], true);
		cubeEntity->setPosition(Pos3D(0.0f, 0.f, 0.f));
		cubeEntity->setScale(Sc3D(3.f, 1.f, 3.f));

		cubeEntity->addCollisionPrimitive(CollisionPrimitive::CreateRectangle(cubeEntity.get(), Pos3D(0.f, 0.f, 0.f), Rt3D(), Vector3(1.f, 1.f, 1.f)));

		cubeEntity->addCollisionPrimitive(CollisionPrimitive::CreateRectangle(cubeEntity.get(), Pos3D(2.f, 1.f, 0.f), Rt3D(), Vector3(1.f, 10.f, 1.f)));
		cubeEntity->addCollisionPrimitive(CollisionPrimitive::CreateRectangle(cubeEntity.get(), Pos3D(-2.f, 1.f, 0.f), Rt3D(), Vector3(1.f, 1.f, 1.f)));

		cubeEntity->addCollisionPrimitive(CollisionPrimitive::CreateRectangle(cubeEntity.get(), Pos3D(0.f, 1.f, 2.f), Rt3D(), Vector3(1.f, 1.f, 1.f)));
		cubeEntity->addCollisionPrimitive(CollisionPrimitive::CreateRectangle(cubeEntity.get(), Pos3D(0.f, 1.f, -2.f), Rt3D(), Vector3(1.f, 1.f, 1.f)));

		allEntities.push_back(std::move(cubeEntity));
	}

	std::vector<Model3D> spheres = ObjLoader::loadObjFile("../data/BallTrack/models/", "sphere");

	std::cout << "nmb spheres : " << spheres.size() << std::endl;

	if (spheres.size() > 0)
	{
		{
			std::unique_ptr<PhysicEntity> sphereEntity = std::make_unique<PhysicEntity>(spheres[0], false);
			sphereEntity->setPosition(Pos3D(0.0f, 5.9f, 0.5f));
			sphereEntity->setScale(Sc3D(1.f));

			sphereEntity->addCollisionPrimitive(CollisionPrimitive::CreateSphere(sphereEntity.get(), Pos3D(0.f, 0.f, 0.f), Rt3D(), 1.f));

			bille = sphereEntity.get();

			allEntities.push_back(std::move(sphereEntity));
		}

		{
			std::unique_ptr<PhysicEntity> sphereEntity = std::make_unique<PhysicEntity>(spheres[0], false);
			sphereEntity->setPosition(Pos3D(-0.2f, 2.9f, 0.f));
			sphereEntity->setScale(Sc3D(1.f));

			sphereEntity->addCollisionPrimitive(CollisionPrimitive::CreateSphere(sphereEntity.get(), Pos3D(0.f, 0.f, 0.f), Rt3D(), 1.f));

			allEntities.push_back(std::move(sphereEntity));
		}
	}

	glutMainLoop();
	return 0;
}
