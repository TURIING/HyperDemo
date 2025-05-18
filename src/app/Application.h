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

class MainWindow;

class Application {
public:
		 Application();
	void Run() const;
	void ProcessEvent(Event &event);

private:
	void renderEvent(RenderRequestEvent &event) const;
	void resizeEvent(const WindowResizeEvent &event) const;
	void mousePressEvent(const MousePressEvent &event) const;
	void mouseMoveEvent(const MouseMoveEvent &event) const;
	void mouseReleaseEvent(const MouseReleaseEvent &event) const;
	void mouseWheelScrollEvent(const MouseWheelScrollEvent &event) const;

private:
    MainWindow *m_pWindow = nullptr;
    HyperRender::ToolFactory *m_pToolFactory = nullptr;
    HyperRender::IScreenTool *m_pScreenTool = nullptr;
    HyperRender::IEffectTool *m_pEffectTool = nullptr;
    HyperRender::IScreenTarget *m_pScreenTarget = nullptr;
    HyperRender::IDrawUnit *m_pScreenUnit = nullptr;
};

#endif // APPLICATION_H
