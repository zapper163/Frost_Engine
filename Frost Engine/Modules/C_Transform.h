#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"

#include <iostream>
#include <string>
#include <vector>


class C_Transform : public Component
{
public:
	C_Transform(GameObject* gameObject);
	~C_Transform();
};