/********************************************************************************
 * @author: TURIING
 * @email: turiing@163.com
 * @date: 2025/3/28 21:00
 * @version: 1.0
 * @description:
 ********************************************************************************/
// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "../../app/Application.h"
#include "ui_MainWindow.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QWindow>

#include "CanvasWidget.h"

MainWindow::MainWindow(const std::string& title, const Size& size, Application* app, QWidget* parent) : QWidget(parent), ui(new Ui::MainWindow), m_pApp(app) {
	ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(title));
	this->resize(size.width, size.height);
    ui->surfaceWidget->installEventFilter(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

void* MainWindow::GetSurfaceHandle() const {
    return ui->surfaceWidget->GetHandle();
}

Size MainWindow::GetSurfaceSize() const {
#if defined(PLATFORM_IOS)
    const auto size = ui->surfaceWidget->size();
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_VULKAN)
    const auto size = ui->surfaceWidget->size();
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_OPENGL)
    const auto size = ui->surfaceWidget->size() * devicePixelRatio();
#elif defined(PLATFORM_WINDOWS)
	const auto size = ui->surfaceWidget->size() * devicePixelRatio();
#endif
    return {static_cast<uint32_t>(size.width()), static_cast<uint32_t>(size.height())};
}

void MainWindow::resizeEvent(QResizeEvent* event) {
	// if(m_timer.isActive()) {
	// 	const auto size = ui->pSurfaceWidget->size();
	// 	WindowResizeEvent resizeEvent(Size { static_cast<uint32_t>(size.width()), static_cast<uint32_t>(size.height())});
	// 	resizeEvent.SetFunc([this] {
	// 		const auto size = this->size();
	// 		const auto surfaceSize = m_pSurface->size();
	// 		LOG_INFO("The window size has changed, MainWindow size({}, {}), Surface widget size({}, {})", size.width(), size.height(), surfaceSize.width(), surfaceSize.height());
	// 	});
	// 	m_pApp->ProcessEvent(resizeEvent);
	// }
	QWidget::resizeEvent(event);
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event) {
    if(watched == ui->surfaceWidget) {
        RenderRequestEvent renderRequestEvent;
        renderRequestEvent.SetFunc([&]{ this->repaint(); });
        switch(event->type()) {
            case QEvent::MouseButtonPress: {
                const auto		_event = dynamic_cast<QMouseEvent*>(event);
                const auto		pos	   = _event->pos();
                MousePressEvent mousePressEvent(static_cast<MouseButton>(_event->button()), {pos.x(), pos.y()});
                m_pApp->ProcessEvent(mousePressEvent);
                m_pApp->ProcessEvent(renderRequestEvent);
                break;
            }
            case QEvent::MouseButtonRelease: {
                const auto		  _event = dynamic_cast<QMouseEvent*>(event);
                const auto		  pos	 = _event->pos();
                MouseReleaseEvent mouseReleaseEvent(static_cast<MouseButton>(_event->button()), {pos.x(), pos.y()});
                m_pApp->ProcessEvent(mouseReleaseEvent);
                break;
            }
            case QEvent::MouseMove: {
                const auto _event = dynamic_cast<QMouseEvent*>(event);
                const auto pos = _event->pos();
                
                auto button = MouseButton::None;
                if(auto btn = _event->buttons(); btn & Qt::RightButton) {
                    button = MouseButton::Right;
                } else if(btn & Qt::LeftButton) {
                    button = MouseButton::Left;
                }
                
                MouseMoveEvent mouseMoveEvent(button, {pos.x(), pos.y()});
                m_pApp->ProcessEvent(mouseMoveEvent);
                break;
            }
            case QEvent::Wheel: {
                const auto _event = dynamic_cast<QWheelEvent*>(event);
                const auto delta = _event->angleDelta().y() * 0.05;
                MouseWheelScrollEvent mouseWheelScrollEvent(delta);
                m_pApp->ProcessEvent(mouseWheelScrollEvent);
                m_pApp->ProcessEvent(renderRequestEvent);
                break;
            }
            default:
                break;
        }
        
        return QWidget::eventFilter(watched, event);
    }
}
