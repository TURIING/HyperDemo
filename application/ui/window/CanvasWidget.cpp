/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2025/5/21 21:56
* @version: 1.0
* @description:
********************************************************************************/
// You may need to build the project (run Qt uic code generator) to get "ui_CanvasWidget.h" resolved
#include "CanvasWidget.h"

#include <QWindow>
#include <QHBoxLayout>
#include <QResizeEvent>

#if PLATFORM_WINDOWS

CanvasWidget::CanvasWidget(QWidget *parent) :QWidget(parent) {
	this->setAttribute(Qt::WA_PaintOnScreen);
}

CanvasWidget::~CanvasWidget() {
}

void *CanvasWidget::GetHandle() const {
	return reinterpret_cast<void*>(winId());
}

void CanvasWidget::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
}

QPaintEngine* CanvasWidget::paintEngine() const {
	return nullptr;
}

#endif