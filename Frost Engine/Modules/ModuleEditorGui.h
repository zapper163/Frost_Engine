#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

struct Console_window
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;        // Index to lines offset
	bool                ScrollToBottom;

	void    Clear() { Buf.clear(); LineOffsets.clear(); }

	void    AddLog(const char file[], int line, const char* logText, ...)
	{
		static char tmp_string[4096];
		static char tmp_string2[4096];
		static va_list  ap;

		va_start(ap, logText);
		vsprintf_s(tmp_string, 4096, logText, ap);
		va_end(ap);
		sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
		OutputDebugString(tmp_string2);

		int old_size = Buf.size();
		va_list args;
		va_start(args, logText);
		Buf.appendfv(logText, args);
		Buf.appendfv("\n", args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
		{
			if (Buf[old_size] == '\n')
			{
				LineOffsets.push_back(old_size);
			}	
		}
		ScrollToBottom = true;
	}

	void    DrawConsole(const char* title, bool* p_opened)
	{
		ImGui::Begin(title, p_opened);
		if (ImGui::Button("Clear")) Clear();
		ImGui::SameLine();
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling");
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
		

		if (Filter.IsActive())
		{
			const char* buf_begin = Buf.begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != NULL; line_no++)
			{
				const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
				if (Filter.PassFilter(line, line_end))
				{
					ImGui::TextUnformatted(line, line_end);
				}
				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
		{
			ImGui::TextUnformatted(Buf.begin());
		}

		if (ScrollToBottom) {
			ImGui::SetScrollHereY(1.0f);
		}

		ScrollToBottom = false;
		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::End();
	}
};


class ModuleEditorGui : public Module
{
public:
	ModuleEditorGui(bool start_enabled = true);
	~ModuleEditorGui();

	bool Init();
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	bool CleanUp();

	void ShowConsole();

	void DisplayGameObjects(GameObject* game_object);

	void PushLog(std::vector<float>* Log, float toPush);

public:

	SDL_GLContext context;
	Console_window console;

	bool show_credits_window = false;
	bool show_main_window = true;
	bool show_hardware_window = false;
	bool show_console_window = true;
	bool show_gameobject_window = true;
	bool show_components_window = true;
	bool show_camera_window = false;
	bool console_visible = true;

	int textureColorbuffer_mini;

	std::vector<float> fpsLog;
	std::vector<float> timeLog;
	
	const char* cube_filepath = "Basic_Shapes/cube.fbx";
	const char* cone_filepath = "Basic_Shapes/cone.fbx";
	const char* sphere_filepath = "Basic_Shapes/sphere.fbx";

};