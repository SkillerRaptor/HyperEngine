#include "OpenGL46ImGuiRenderer.hpp"

#include <backends/imgui_impl_opengl3.h>

namespace Hyperion
{
	void OpenGL46ImGuiRenderer::OnAttach()
	{
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	void OpenGL46ImGuiRenderer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
	}

	void OpenGL46ImGuiRenderer::Start()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void OpenGL46ImGuiRenderer::End()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
