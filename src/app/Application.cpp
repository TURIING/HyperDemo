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

	HyperRender::PlatformSurfaceInfo surfaceInfo{.handle = m_pWindow->GetSurfaceHandle(), .size = {500, 500}};
	m_pToolFactory = new HyperRender::ToolFactory(surfaceInfo);
	m_pScreenTool  = m_pToolFactory->CreateScreenTool();
}

void Application::Run() const {
	m_pWindow->Update();
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
	m_pScreenTool->Draw();
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