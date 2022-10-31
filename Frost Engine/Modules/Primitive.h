
#pragma once
#include "glmath.h"
#include "Color.h"


enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Plane,
};

class Primitive
{
public:
	Primitive();

	void Update();
	virtual void	Render() const;
	PrimitiveTypes	GetType() const;


	Color color;
	mat4x4 transform;
	bool axis,wire;

protected:
	virtual void InnerRender() const;
	PrimitiveTypes type;
};

class Plano : public Primitive
{
public:
	Plano();
	Plano(float x, float y, float z, float d);

protected:
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};
