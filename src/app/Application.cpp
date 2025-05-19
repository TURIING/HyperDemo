/********************************************************************************
 * @author: TURIING
 * @email: turiing@163.com
 * @date: 2025/3/28 21:05
 * @version: 1.0
 * @description:
 ********************************************************************************/
#include "Application.h"
#include "../common/common.h"
#include "../ui/window/MainWindow.h"

Application::Application() {
	Singleton<LogManager>::GetInstance()->Init();

	m_pWindow = new MainWindow("HyperDemo", WINDOW_SIZE, this);
	m_pWindow->show();

	const auto size = std::bit_cast<HyperRender::Size>(m_pWindow->GetSurfaceSize());

#if GRAPHICS_OPENGL
	m_pToolFactory = new HyperRender::ToolFactory(HyperRender::GpuType::OPENGL);
#elif GRAPHICS_VULKAN
	m_pToolFactory = new HyperRender::ToolFactory(HyperRender::GpuType::VULKAN);
#endif

	m_pScreenTool  = m_pToolFactory->CreateScreenTool();
//	m_pEffectTool = m_pToolFactory->CreateEffectTool();

	HyperRender::PlatformWindowInfo surfaceInfo{
		.handle = m_pWindow->GetSurfaceHandle(),
		.size = size
	};
	m_pScreenTarget = m_pScreenTool->CreateScreen(surfaceInfo);
	m_pScreenTool->SetScreenTarget(m_pScreenTarget);
	//    m_pScreenUnit = m_pScreenTool->CreateDrawUnit({0, 0, size.width, size.height});
	//    m_pScreenTool->ClearColor(m_pScreenUnit, {1.0, 0.0, 0.0, 1.0});
	//
	//    IDrawUnit *unit = m_pScreenTool->CreateDrawUnit({100, 100, 500, 500});
	//    m_pScreenTool->ClearColor(unit, {0.0, 0.0, 1.0, 1.0});
	//    m_pEffectTool->Begin({unit, unit->GetArea()});
	//    m_pEffectTool->End(bgUnit);
	//    m_pScreenTool->Begin({bgUnit, bgUnit->GetArea()});
}

void Application::ProcessEvent(Event &event) {
	EventDispatcher dispatcher(event);
	dispatcher.dispatch<RenderRequestEvent>(std::bind(&Application::renderEvent, this, std::placeholders::_1));
	dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::resizeEvent, this, std::placeholders::_1));
	dispatcher.dispatch<MousePressEvent>(std::bind(&Application::mousePressEvent, this, std::placeholders::_1));
	dispatcher.dispatch<MouseMoveEvent>(std::bind(&Application::mouseMoveEvent, this, std::placeholders::_1));
	dispatcher.dispatch<MouseReleaseEvent>(std::bind(&Application::mouseReleaseEvent, this, std::placeholders::_1));
	dispatcher.dispatch<MouseWheelScrollEvent>(std::bind(&Application::mouseWheelScrollEvent, this, std::placeholders::_1));
}

void Application::renderEvent(RenderRequestEvent &event) const {
	const auto size = std::bit_cast<HyperRender::Size>(m_pWindow->GetSurfaceSize());
	m_pScreenTool->BeginRenderToScreen({0, 0, size.width, size.height});
	m_pScreenTool->EndRenderToScreen();
}

void Application::resizeEvent(const WindowResizeEvent &event) const {

	// m_pCurInstance->OnResize(event.GetSize());
}

void Application::mousePressEvent(const MousePressEvent &event) const {}

void Application::mouseMoveEvent(const MouseMoveEvent &event) const {
	// m_pCurInstance->OnMouseMove(event.GetMouseButton(), event.GetPosition());
}

void Application::mouseReleaseEvent(const MouseReleaseEvent &event) const {}

void Application::mouseWheelScrollEvent(const MouseWheelScrollEvent &event) const {
	// LOG_ASSERT(m_pCurInstance);
	// m_pCurInstance->OnMouseScroll(event.GetDelta());
}