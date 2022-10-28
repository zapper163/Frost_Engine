#include "Globals.h"
#include "Application.h"
#include "ModuleEditorGui.h"


#include <Windows.h>


ModuleEditorGui::ModuleEditorGui(bool start_enabled) : Module(start_enabled)
{
}

// Destructor
ModuleEditorGui::~ModuleEditorGui()
{}

// Called before render is available
bool ModuleEditorGui::Init()
{
	bool ret = true;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	
	ImGui::StyleColorsDark();

	return ret;
}
update_status ModuleEditorGui::Update(float dt)
{
	float FPS = floorf(App->GetFrameRate());
	float MS = (App->GetDt() * 1000.f);

	PushLog(&fpsLog, FPS);
	PushLog(&timeLog, MS);

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleEditorGui::PostUpdate(float dt)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	
	static float f = 0.0f;
	static int counter = 0;

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
	ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
	ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("BackGround Window", nullptr, windowFlags);

	ImGui::PopStyleVar(3);

	ImGuiID dockSpaceId = ImGui::GetID("BackGroundWindowDockSpace");

	ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::End();


	if (show_main_window)
	{
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::Begin("GameRender", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus );
		ImGui::BeginChild("GameRender", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
		ImVec2 wsize = ImGui::GetWindowSize();
		ImGui::Image((ImTextureID)App->renderer3D->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
		ImGui::End();

		ImGui::Begin("Main", NULL, ImGuiWindowFlags_MenuBar);  
		
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Main"))
			{
				ImGui::EndMenu();
			}
		
			if (ImGui::BeginMenu("Help"))
			{
				
				if (ImGui::MenuItem("Documentation"))
				{
					ShellExecuteA(NULL, "open", "https://github.com/zapper163/Frost_Engine/wiki", NULL, NULL, SW_SHOWDEFAULT);
				}
				if (ImGui::MenuItem("Download Latest"))
				{
					ShellExecuteA(NULL, "open", "https://github.com/zapper163/Frost_Engine/releases", NULL, NULL, SW_SHOWDEFAULT);
				}
				if (ImGui::MenuItem("Hardware"))
				{
					show_hardware_window = true;
				}
				if (ImGui::MenuItem("About"))
				{
					show_credits_window = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Console"))
			{
				show_console_window = true;
				console_visible = !console_visible;

				console.AddLog(__FILE__, __LINE__, "Console Started");

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Exit"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					show_main_window = false;                     //See ModuleImput 121
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("Main Window");
		ImGui::Checkbox("Cube", &App->meshRender->cube);
		ImGui::Checkbox("Wireframe Mode", &wireframe);
		ImGui::Checkbox("Color", &color);      
		
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		
		if (ImGui::CollapsingHeader("FRAMERATE"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			char title[25];
			sprintf_s(title, 25, "Framerate %1.f", fpsLog[fpsLog.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.f", timeLog[timeLog.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &timeLog[0], timeLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

		}
		ImGui::End();
	}


	if (show_credits_window)
	{
		ImGui::Begin("Credits", &show_credits_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("FROST ENGINE  by Alejandro Giralt\n\n");
		ImGui::Text("External Libraries:");
		if (ImGui::Button("ImGui 1.88")) {

			::ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("MathGeoLib 2016")) {

			::ShellExecuteA(NULL, "open", "https://github.com/juj/MathGeoLib", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("Assimp")) {

			::ShellExecuteA(NULL, "open", "https://github.com/assimp/assimp", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		ImGui::Text("\n\n");
		if (ImGui::Button("Glew 2.1.0.0")) {

			::ShellExecuteA(NULL, "open", "https://github.com/nigels-com/glew", NULL, NULL, SW_SHOWDEFAULT);
		}
		ImGui::SameLine();
		if (ImGui::Button("Json parser 1.1.0")) {

			::ShellExecuteA(NULL, "open", "https://github.com/json-parser/json-parser", NULL, NULL, SW_SHOWDEFAULT);
		}

		ImGui::Text("\n\n");
		ImGui::Text("MIT License\n\nCopyright(c) 2022 zapper163\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this softwareand associated documentation files(the Software), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions :\n\n");
		ImGui::Text("The above copyright noticeand this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\n");
		ImGui::Text("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");

		ImGui::End();
	}

	if (show_hardware_window)
	{
		ImGui::Begin("Hardware", &show_hardware_window, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Text("SDL Version: 2.0.4\n");
		ImGui::Text("CPU's: %d", SDL_GetCPUCount());
		ImGui::Text("RAM: %d", SDL_GetSystemRAM());

		ImGui::Text("\n\n");

		ImGui::End();
	}

	if (console_visible)
	{
		ShowConsole();
	}

	// Rendering
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditorGui::CleanUp()
{
	LOG("Destroying ImGui");

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleEditorGui::ShowConsole()
{
	if (show_console_window)
	{
		console.DrawConsole("Console", &show_console_window);
		
	}
	if (show_console_window == NULL)
	{
		console_visible = !console_visible;
	}
}

void ModuleEditorGui::PushLog(std::vector<float>* Log, float toPush)
{

	if (Log->size() > 100)
	{
		Log->erase(Log->begin());
		Log->push_back(toPush);
	}
	else Log->push_back(toPush);


}