/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2025/5/21 21:56
* @version: 1.0
* @description: 
********************************************************************************/
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#if defined(PLATFORM_IOS) || defined(PLATFORM_MACOS)

#include <QWidget>
#include <QWindow>

class CanvasWidget : public QWidget {
Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget() override;
    void* GetHandle();

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif
#endif //CANVASWIDGET_H
