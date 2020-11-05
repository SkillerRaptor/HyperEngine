#include "Application.hpp"

#include <chrono>

#include "HyperEvents/WindowEvents.hpp"
#include "Utilities/Random.hpp"
#include "Utilities/Timestep.hpp"

#include "Platform/Rendering/OpenGL/OpenGLWindow.hpp"
#include "Platform/Rendering/OpenGL/OpenGLRenderer2D.hpp"
#include "Platform/Rendering/OpenGL/Buffers/OpenGLFrameBuffer.hpp"

namespace Hyperion 
{
	Application* Application::m_Instance;

	Application::Application()
	{
		m_Instance = this;
		Init();
	}

	void Application::Init()
	{
		HP_CORE_INFO("");
		HP_CORE_INFO("_     _ __   __  _____  _______  ______ _______ __   _  ______ _____ __   _ _______");
		HP_CORE_INFO("|_____|   \\_/   |_____] |______ |_____/ |______ | \\  | |  ____   |   | \\  | |______");
		HP_CORE_INFO("|     |    |    |       |______ |    \\_ |______ |  \\_| |_____| __|__ |  \\_| |______");
		HP_CORE_INFO("");

		Random::Init();

		WindowData data;
		data.Title = "HyperEngine";
		data.Width = 1920;
		data.Height = 1080;
		data.XPos = -1;
		data.YPos = -1;
		data.VSync = false;
		data.EventBus = &m_EventBus;

		m_Window = OpenGLWindow::Construct(data);

		m_Scene = CreateRef<Scene>("Main Scene", m_Window->GetContext()->GetRenderer2D());

		m_LayerStack = new LayerStack();
		PushOverlayLayer(new ImGuiLayer(m_Scene));

		m_Window->GetContext()->GetRenderer2D()->SetShaderManager(static_cast<OpenGLShaderManager*>(m_Window->GetContext()->GetShaderManager()));
		m_Window->GetContext()->GetRenderer2D()->SetTextureManager(static_cast<OpenGLTextureManager*>(m_Window->GetContext()->GetTextureManager()));
	}

	void Application::Shutdown()
	{
		m_Running = false;

		for (Layer* layer : m_LayerStack->GetLayers())
		{
			layer->OnDetach();
			m_LayerStack->PopLayer(layer);
		}

		for (OverlayLayer* overlayLayer : m_LayerStack->GetOverlayLayers())
		{
			overlayLayer->OnDetach();
			m_LayerStack->PopOverlayLayer(overlayLayer);
		}

		delete m_LayerStack;
	}

	void Application::Run()
	{
		const int ticksPerSecond = 60;
		const int ticksPerFrame = 5;
		const int skipTicks = 1000 / ticksPerSecond;
		int loops = 0;
		int currentTick = 0;

		std::chrono::time_point currentTime = std::chrono::system_clock::now();

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

		TextureManager* textureManager = m_Window->GetContext()->GetTextureManager();
		uint32_t bufferTexture = textureManager->CreateTexture(m_Window->GetWindowData().Width, m_Window->GetWindowData().Height, TextureType::FRAMEBUFFER);
		uint32_t bufferTextureId = static_cast<OpenGLTextureData*>(textureManager->GetTextureData(bufferTexture))->TextureId;

		static_cast<ImGuiLayer*>(m_LayerStack->GetOverlayLayer("ImGui Layer"))->SetFrameTextureId(bufferTextureId);

		OpenGLFrameBuffer frameBuffer;

		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			OpenGLTextureData* textureData = static_cast<OpenGLTextureData*>(textureManager->GetTextureData(bufferTexture));
			textureData->Width = m_Window->GetWindowData().Width;
			textureData->Height = m_Window->GetWindowData().Height;
			textureManager->DeleteTextureData(bufferTexture);
			textureManager->GenerateTexture(textureData, true);

			frameBuffer.Bind();
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bufferTextureId, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			frameBuffer.Unbind();

			loops = 0;
			while (std::chrono::system_clock::now() > currentTime && loops < ticksPerFrame)
			{
				for (Layer* layer : m_LayerStack->GetLayers())
					layer->OnTick(currentTick);

				for (OverlayLayer* overlayLayer : m_LayerStack->GetOverlayLayers())
					overlayLayer->OnTick(currentTick);

				m_Scene->OnTick(currentTick);

				currentTick++;
				if (currentTick >= ticksPerSecond)
					currentTick = 0;

				currentTime += std::chrono::milliseconds(skipTicks);
				loops++;
			}

			const long long currentTimeNow = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime).time_since_epoch().count();
			const long long timeSinceEpoch = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();

			const Timestep timeStep = static_cast<double>(timeSinceEpoch + skipTicks - currentTimeNow) / static_cast<double>(skipTicks);

			while (m_EventBus.size() > 0)
			{
				Ref<Event> e = m_EventBus.front();
				if (e->Handled) continue;
				OnEvent(*e);
				m_EventBus.pop();
			}

			frameBuffer.Bind();

			for (Layer* layer : m_LayerStack->GetLayers())
			{
				layer->OnUpdate(timeStep);
				layer->OnRender();
			}

			m_Scene->OnUpdate(timeStep);
			m_Scene->OnRender();

			frameBuffer.Unbind();

			for (OverlayLayer* overlayLayer : m_LayerStack->GetOverlayLayers())
			{
				overlayLayer->OnUpdate(timeStep);
				overlayLayer->OnRender();
			}

			m_Window->OnUpdate(timeStep);
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& e)
			{
				Shutdown();
				return false;
			});

		for (Layer* layer : m_LayerStack->GetLayers())
			layer->OnEvent(event);

		for (OverlayLayer* overlayLayer : m_LayerStack->GetOverlayLayers())
			overlayLayer->OnEvent(event);

		m_Scene->OnEvent(event);
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->SetRenderContext(m_Window->GetContext());
		m_LayerStack->PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack->PopLayer(layer);
	}

	void Application::PopLayer(const std::string& layerName)
	{
		m_LayerStack->PopLayer(layerName);
	}

	void Application::PopLayer()
	{
		m_LayerStack->PopLayer();
	}

	Layer* Application::GetLayer(const std::string& layerName)
	{
		return m_LayerStack->GetLayer(layerName);
	}

	void Application::PushOverlayLayer(OverlayLayer* overlayLayer)
	{
		overlayLayer->SetRenderContext(m_Window->GetContext());
		m_LayerStack->PushOverlayLayer(overlayLayer);
	}

	void Application::PopOverlayLayer(OverlayLayer* overlayLayer)
	{
		m_LayerStack->PopOverlayLayer(overlayLayer);
	}

	void Application::PopOverlayLayer(const std::string& layerName)
	{
		m_LayerStack->PopOverlayLayer(layerName);
	}

	void Application::PopOverlayLayer()
	{
		m_LayerStack->PopOverlayLayer();
	}

	OverlayLayer* Application::GetOverlayLayer(const std::string& layerName)
	{
		return m_LayerStack->GetOverlayLayer(layerName);
	}

	Ref<Window> Application::GetNativeWindow() const
	{
		return m_Window;
	}

	Application* Application::Get()
	{
		return m_Instance;
	}
}
