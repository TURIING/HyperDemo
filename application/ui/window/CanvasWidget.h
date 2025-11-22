/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2025/5/21 21:56
* @version: 1.0
* @description: 
********************************************************************************/
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QWindow>

class CanvasWidget : public QWidget {
Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;
    void* GetHandle() const;

#if PLATFORM_WINDOWS
	[[nodiscard]] QPaintEngine *paintEngine() const override;
#endif

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif //CANVASWIDGET_H
