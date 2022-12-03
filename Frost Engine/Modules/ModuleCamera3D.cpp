#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"

ModuleCamera3D::ModuleCamera3D(bool start_enabled) : Module(start_enabled)
{
	CalculateViewMatrix();

	frustum.type = PerspectiveFrustum;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 500.f;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * (16.f / 9.f));

	frustum.pos = float3(0, 5, -20);
}

ModuleCamera3D::~ModuleCamera3D()
{}

bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Setting up the camera");

	bool ret = true;

	return ret;
}

bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");
	App->editorGui->console.AddLog(__FILE__, __LINE__, "Cleaning camera");



	return true;
}

update_status ModuleCamera3D::Update(float dt)
{

	vec3 newPos(0,0,0);
	Quat direction = Quat::identity;

	float speed = 3.0f * dt;
	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f * dt;

	//Focus On 
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		LookAt(float3 (0, 0, 0));
	}

	//While Right Click, "WASD" movement

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos += frustum.front * speed;
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos -= frustum.front * speed;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos -= frustum.WorldRight() * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos += frustum.WorldRight() * speed;

	//Mouse Scroll
	if(App->input->GetMouseZ() != 0) frustum.pos += frustum.front * speed * App->input->GetMouseZ();
	
	
	Position += newPos;
	Reference += newPos;

	// Alt + Left Click, Mouse Motion
	if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Quat dir;
		frustum.WorldMatrix().Decompose(float3(), dir, float3());

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;
			Quat X = Quat::identity;
			X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);
			dir = X * dir;
		}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;
			Quat Y = Quat::identity;
			Y.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DeltaY * DEGTORAD);
			dir = dir * Y;
		}

		float4x4 rm = frustum.WorldMatrix();
		rm.SetRotatePart(dir.Normalized());
		frustum.SetWorldMatrix(rm.Float3x4Part());
	}

	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

void ModuleCamera3D::Look(const float3 &Position, const float3&Reference, bool RotateAroundReference)
{
	frustum.pos = Position;
	reference = Reference;

	LookAt(reference);

	if(!RotateAroundReference)
	{
		reference = Position;
	}
}


void ModuleCamera3D::LookAt( const float3 &Spot)
{
	reference = Spot;
	frustum.front = (Spot - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}

void ModuleCamera3D::Move(const float3 &Movement)
{
	frustum.pos += Movement;
}

float* ModuleCamera3D::GetOpenGLViewMatrix()
{
	return viewMatrix.ptr();
}

void ModuleCamera3D::CalculateViewMatrix()
{
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
}
