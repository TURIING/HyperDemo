/********************************************************************************
 * @author: TURIING
 * @email: turiing@163.com
 * @date: 2025/3/28 21:00
 * @version: 1.0
 * @description:
 ********************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../common/common.h"
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Application;
class CanvasWidget;

class MainWindow : public QWidget {
	Q_OBJECT

public:
	explicit			MainWindow(const std::string& title, const Size& size, Application* app, QWidget* parent = nullptr);
	~					MainWindow() override;
	[[nodiscard]] void* GetSurfaceHandle() const;
	[[nodiscard]] Size  GetSurfaceSize() const;

protected:
	void resizeEvent(QResizeEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event) override;

private:
	Ui::MainWindow* ui;
	Application* m_pApp	= nullptr;
};

#endif // MAINWINDOW_H
