#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include "PhysicsObject.h"
// This represents the location and orientation, etc. of 
//	a single mesh object (a bunch of triangles with colours
//	maybe textures, etc.) like a single PLY file.

class cMeshObject
{
public:
	cMeshObject();
	std::string meshName;

	// Human friendly name for this particular instance of the mesh
	std::string friendlyName;

	glm::vec3 position;     // 0,0,0 (origin)
	glm::vec3 rotation;     // 0,0,0 ration around each Euler axis
	float scale;
    bool isWireframe;		// false

    glm::vec4 RGBA_colour;		// RGA & Alpha, 0,0,0,1 (black, with transparency of 1.0)
	// When true, it will overwrite the vertex colours
	bool bUse_RGBA_colour; 

	bool bDoNotLight;

	bool bIsVisible;
	bool hasPhysicsObject;

	PhysicsObject* physics_object;
	// Later (after mid-term)
//	std::string textures[10];

};

#endif // _cMeshObject_HG_
