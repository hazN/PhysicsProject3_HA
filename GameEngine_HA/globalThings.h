#ifndef _globalThings_HG_
#define _globalThings_HG_

// This is anything that is shared by all (or many) of the files

#include <GLFW/glfw3.h>

#include "cMeshObject.h"
#include "cVAOManager/sModelDrawInfo.h"
#include "cLightManager.h"
#include "PhysicsEngine.h"
#include "cVAOManager/cVAOManager.h"
#include "PhysicsSystem.h"
// extern means the variable isn't actually here...
// ...it's somewhere else (in a .cpp file somewhere)
extern GLFWwindow* window;
extern cLightManager* g_pTheLightManager;
extern std::vector< cMeshObject* > g_pMeshObjects;
extern int currentLight;
extern int currentModel;
extern cVAOManager* pVAOManager;
extern bool isTyping;
enum eEditMode
{
	MOVING_CAMERA,
	MOVING_LIGHT,
	MOVING_SELECTED_OBJECT,
	MOVING_PHYSICS_OBJECT
};
enum eGameMode
{
	Click,
	Hover
};
extern int theEditMode;
extern PhysicsSystem g_physics_system;
extern PhysicsEngine g_engine;
extern int numHitTargets;
extern bool menuMode;
extern int gameMode;
extern float rotateSpeed;
#endif
