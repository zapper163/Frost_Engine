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
	App->camera->CalculateViewMatrix();

	viewMatrix2 = frustum2.ViewMatrix();
	viewMatrix2.Transpose();

	frustum2.type = PerspectiveFrustum;
	frustum2.nearPlaneDistance = nearPlaneDistance2;
	frustum2.farPlaneDistance = farPlaneDistance2;
	frustum2.front = float3::unitZ;
	frustum2.up = float3::unitY;
	frustum2.verticalFov = 60.0f * DEGTORAD;
	frustum2.horizontalFov = 2.0f * atanf(tanf(frustum2.verticalFov / 2.0f) * (16.f / 9.f));

	frustum2.pos = float3(0, 0, -5);

	Move(float3(1.0f, 1.0f, 0.0f));

	InitFrameBuffer();
}

C_Camera::~C_Camera()
{

}

void C_Camera::Update()
{

	if (App->editorGui->show_camera_window)
	{
		//FrameBuffer
		glBindFramebuffer(GL_FRAMEBUFFER, textureColorbuffer_mini);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}
}

void C_Camera::OnGui()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen ))
	{
		ImGui::Text("Near Plane Distance ");
		ImGui::SameLine();
		ImGui::DragFloat("##NearPlane2", &frustum2.nearPlaneDistance, 0.1f);

		ImGui::Text("Far Plane Distance ");
		ImGui::SameLine();
		ImGui::DragFloat("##FarPlane2", &frustum2.farPlaneDistance, 0.1f);
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
	frustum2.pos += Movement;
}

