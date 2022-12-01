#pragma once
#include "Globals.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"
#include "C_Camera.h"

#include <iostream>
#include <string>
#include <vector>

C_Camera::C_Camera(GameObject* gameObject) : Component(gameObject, TYPE::CAMERA)
{
	//CalculateViewMatrix();
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();

	frustum.type = PerspectiveFrustum;
	frustum.nearPlaneDistance = nearPlaneDistance;
	frustum.farPlaneDistance = farPlaneDistance;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;
	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.7f); // 16:9 ~= 1,77777...

	frustum.pos = float3(0, 0, -10);

	Move(float3(1.0f, 1.0f, 0.0f));

	InitFrameBuffer();
	
}

C_Camera::~C_Camera()
{

}

void C_Camera::Update()
{
	//Movement Disabled
	/*
	vec3 newPos(0, 0, 0);
	Quat direction = Quat::identity;

	float speed = 3.0f;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 8.0f;

	//Focus On 
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		//LookAt(float3(0, 0, 0));
	}

	//While Right Click, "WASD" movement

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos += frustum.front * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos -= frustum.front * speed;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos -= frustum.WorldRight() * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos += frustum.WorldRight() * speed;

	//Move vertically independently of camera rotation
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) frustum.pos.y -= speed;

	//Mouse Scroll
	if (App->input->GetMouseZ() != 0) frustum.pos += frustum.front * speed * App->input->GetMouseZ();


	Position += newPos;
	Reference += newPos;

	// Mouse motion while Left Click
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Quat dir;
		frustum.WorldMatrix().Decompose(float3(), dir, float3());

		Position -= Reference;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;
			Quat X = Quat::identity;
			X.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DeltaX * DEGTORAD);
			dir = X * dir;
		}

		if (dy != 0)
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

	//CalculateViewMatrix();
	viewMatrix = frustum.ViewMatrix();
	viewMatrix.Transpose();
	*/
}

void C_Camera::OnGui()
{

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen ))
	{
		ImGui::Text("Near Plane Distance ");
		ImGui::SameLine();
		ImGui::DragFloat3("##Cam", &nearPlaneDistance, 0.1f);


		

	}

}

void C_Camera::InitFrameBuffer()
{
	//Framebuffer--------------------------------------------------------------------------------------
	glGenFramebuffers(1, &framebuffer_mini);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_mini);

	// generate texture
	glGenTextures(1, &textureColorbuffer_mini);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer_mini);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer_mini, 0);
	// create render buffer object
	glGenRenderbuffers(1, &renderbuffer_mini);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_mini);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720); //Size of the screen printed
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer_mini);

}


void C_Camera::Move(const float3& Movement)
{
	frustum.pos += Movement;
}


void BindBuffer(int textureBuffer)
{
	glBindFramebuffer(GL_FRAMEBUFFER, textureBuffer);
}
/*
void ResizeBuffer(int width, int height)
{

}
*/