#include "globalThings.h"


// The variable is HERE.
cLightManager* g_pTheLightManager = NULL;
std::vector< cMeshObject* > g_pMeshObjects;
int currentLight = 0;
int currentModel = 0;
cVAOManager* pVAOManager = new cVAOManager;
int theEditMode = eEditMode::MOVING_CAMERA;
int gameMode = eGameMode::Click;
bool isTyping = false;
PhysicsSystem g_physics_system;
PhysicsEngine g_engine;
GLFWwindow* window;
int numHitTargets = 0;
bool menuMode = true;
float rotateSpeed = 0.001f;
