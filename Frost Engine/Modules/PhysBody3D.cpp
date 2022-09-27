#include "PhysBody3D.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ---------------------------------------------------------
PhysBody3D::PhysBody3D()
	: body(nullptr)
	, parentPrimitive(nullptr)
	, collision_listeners()
{
	
}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	//TODO 2: And delete them!
	//Make sure there's actually something to delete, check before deleting

}

void PhysBody3D::InitBody(Sphere* primitive, float mass)
{
	//TODO 1: Store all "new" created values
	assert(HasBody() == false);
	parentPrimitive = primitive;

	btCollisionShape* colShape = new btSphereShape(primitive->radius);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&primitive->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);

	body = new btRigidBody(rbInfo);


	body->setUserPointer(this);
	App->physics->AddBodyToWorld(body);
}

bool PhysBody3D::HasBody() const
{
	return body != nullptr;
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if (HasBody() == false)
		return;
	//TODO 5: Set the Physical Body transform into "matrix"
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if (HasBody() == false)
		return;

	//TODO 5: Set the Physical Body transform to equal "matrix"
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	if (HasBody() == false)
		return;

	//TODO 5: Set the Physical Body position to x, y, z. Make sure not to change the rotation!
}
