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
#include <chrono>
#include <thread>
#include <QApplication>
const double MAX_FPS = 60.0;                         // 最大调用次数/秒

Application::Application(int argc, char **argv): m_windowSize(WINDOW_SIZE) {
	m_pApp = new QApplication(argc, argv);
	// Singleton<LogManager>::GetInstance()->Init();

	m_pWindow = new MainWindow("HyperDemo", m_windowSize, this);
	m_pWindow->show();

	const auto size = std::bit_cast<HyperRender::Size>(m_pWindow->GetSurfaceSize());
    // LOG_INFO("{},{}", size.width, size.height);
#if GRAPHICS_OPENGL
	m_pToolFactory = new HyperRender::ToolFactory(HyperRender::GpuType::OPENGL);
#elif GRAPHICS_VULKAN
	m_pToolFactory = new HyperRender::ToolFactory(HyperRender::GpuType::VULKAN);
#endif

	m_pScreenTool  = m_pToolFactory->CreateScreenTool();
	// m_pEffectTool = m_pToolFactory->CreateEffectTool();

	HyperRender::PlatformWindowInfo surfaceInfo{
		.handle = m_pWindow->GetSurfaceHandle(),
		.size = size
	};
	m_pScreenTarget = m_pScreenTool->CreateScreen(surfaceInfo);
	m_pScreenTool->SetScreenTarget(m_pScreenTarget);

	// QImage image("/Users/turiing/Desktop/demo.png");
	// image = image.convertToFormat(QImage::Format_RGBA8888);
	// auto unit = m_pScreenTool->CreateDrawUnit({{100,100}, {500, 500}});
	// m_pScreenTool->ClearColor(unit, {1.0, 0,0, 1.0});
	// m_pEffectTool->FillDrawUnit(unit, image.constBits(), image.sizeInBytes(), {0, 0});
	// m_pScreenTool->AddScreenObject(unit, unit->GetArea());
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

void Application::Run() {
	render();
	m_pApp->exec();
	// const auto frame_interval = std::chrono::duration<double>(1.0 / MAX_FPS);
	// auto next_time = std::chrono::steady_clock::now() + frame_interval;
	// while (true)
	// {
	// 	render();
	// 	auto now = std::chrono::steady_clock::now();
	// 	if (now < next_time)
	// 	{
	// 		std::this_thread::sleep_until(next_time);
	// 	}
	// 	next_time += frame_interval;
	// }
}

void Application::renderEvent(RenderRequestEvent &event) {
	render();
}

void Application::resizeEvent(const WindowResizeEvent &event) {}

void Application::mousePressEvent(const MousePressEvent &event) {}

void Application::mouseMoveEvent(const MouseMoveEvent &event) {}

void Application::mouseReleaseEvent(const MouseReleaseEvent &event) {}

void Application::mouseWheelScrollEvent(const MouseWheelScrollEvent &event) {}

Application::ImageInfo Application::loadImage(const std::string &fileName) {
	QImage image(fileName.c_str());
	image = image.convertToFormat(QImage::Format_RGBA8888);
	return {
		image.bits(), image.sizeInBytes(),
		{(uint32_t)image.width(), (uint32_t)image.height()}
	};
}
