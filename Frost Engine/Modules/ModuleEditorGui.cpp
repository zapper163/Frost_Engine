#include "Globals.h"
#include "Application.h"
#include "ModuleEditorGui.h"
#include "SDL\include\SDL_opengl.h"


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include "SDL/include/SDL_opengl.h"
#endif

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

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
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends---------------------------------------------------------------------------->Esto va en el MOduleRender3D
	//ImGui_ImplSDL2_InitForOpenGL(App->window->window, context);
	//ImGui_ImplOpenGL3_Init("#version 130");


	return ret;
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

	if (show_main_window)
	{
		// Using a Child allow to fill all the space of the window.
		// It also alows customization
		ImGui::Begin("GameRender", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::BeginChild("GameRender", ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
		ImVec2 wsize = ImGui::GetWindowSize();
		ImGui::Image((ImTextureID)App->renderer3D->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
		ImGui::End();

		ImGui::Begin("Main", NULL, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_AlwaysAutoResize);  
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
		ImGui::Text("Main Window");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Wireframe Mode", &wireframe);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Color", &color);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_credits_window);
		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow();
	}

	if (show_credits_window)
	{
		ImGui::Begin("Credits", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				if (ImGui::MenuItem("Close Tab"))
				{
					show_credits_window = false;                     //See ModuleImput 121
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
		ImGui::Begin("Hardware", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Settings"))
				{

				}
				if (ImGui::MenuItem("Close Tab"))
				{
					show_hardware_window = false;
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

