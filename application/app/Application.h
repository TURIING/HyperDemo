/********************************************************************************
 * @author: TURIING
 * @email: turiing@163.com
 * @date: 2025/3/28 21:05
 * @version: 1.0
 * @description:
 ********************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "HyperRender.h"
#include "ToolFactory.h"
#include "UIEvent.h"
// #include "ui/window/MainWindow.h"
// #include <QApplication>
class MainWindow;
class QApplication;

class Application {
public:
	Application(int argc, char **argv);
	virtual ~Application() = default;
	void ProcessEvent(Event &event);
	void Run();

protected:
	struct ImageInfo {
		void* ptr = nullptr;
		int64_t size = 0;
		Size imageSize;
	};
	virtual void render() = 0;
	virtual void renderEvent(RenderRequestEvent &event);
	virtual void resizeEvent(const WindowResizeEvent &event);
	virtual void mousePressEvent(const MousePressEvent &event);
	virtual void mouseMoveEvent(const MouseMoveEvent &event);
	virtual void mouseReleaseEvent(const MouseReleaseEvent &event);
	virtual void mouseWheelScrollEvent(const MouseWheelScrollEvent &event);
	[[nodiscard]] static ImageInfo loadImage(const std::string &fileName);

protected:
	HyperRender::ToolFactory *m_pToolFactory = nullptr;
	HyperRender::IScreenTool *m_pScreenTool = nullptr;
	HyperRender::IEffectTool *m_pEffectTool = nullptr;
	HyperRender::IScreenTarget *m_pScreenTarget = nullptr;
	HyperRender::IDrawUnit *m_pScreenUnit = nullptr;

private:
	QApplication* m_pApp = nullptr;
    MainWindow *m_pWindow = nullptr;
};

#endif // APPLICATION_H
