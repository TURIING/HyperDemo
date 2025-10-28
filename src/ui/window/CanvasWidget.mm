/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2025/5/21 21:56
* @version: 1.0
* @description: 
********************************************************************************/
// You may need to build the project (run Qt uic code generator) to get "ui_CanvasWidget.h" resolved
#if defined(PLATFORM_IOS) || defined(PLATFORM_MACOS)
#include "CanvasWidget.h"

#if PLATFORM_IOS
#import <UIKit/UIKit.h>
#elif PLATFORM_MACOS
#import <AppKit/AppKit.h>
#import <QuartzCore/CAMetalLayer.h>
#endif
#import <Metal/Metal.h>
#include <QWindow>
#include <QHBoxLayout>
#include <QResizeEvent>

#if defined(PLATFORM_IOS) && defined(GRAPHICS_OPENGL)
    UIView *gView = nullptr;
    CAEAGLLayer *gLayer = nullptr;
#elif defined(PLATFORM_IOS) && defined(GRAPHICS_VULKAN)
    UIView *gView = nullptr;
    CAMetalLayer *gLayer = nullptr;
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_VULKAN)
    NSView *gView = nullptr;
    CAMetalLayer *gLayer = nullptr;
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_OPENGL)
    NSView *gView = nullptr;
#endif

CanvasWidget::CanvasWidget(QWidget *parent) :QWidget(parent) {
#if defined(PLATFORM_IOS) && defined(GRAPHICS_OPENGL)
    // 强转qt主窗口的指针
    UIView *view = reinterpret_cast<UIView *>(this->winId());

    // 创建drawable layer，注意同Vulkan surface中的layer类型不同
    gLayer = [CAEAGLLayer layer];

    // 创建子view
    auto size = this->size();
    CGRect  viewRect = CGRectMake(0, 0, size.width(), size.height());
    gView = [[UIView alloc] initWithFrame:viewRect];

    gLayer.frame = gView.bounds;  // 设置图层的大小
    gLayer.opaque = YES;  // 设置图层为不透明

    // 将layer挂载在子view中
    [gView.layer addSublayer:gLayer];

    // qt主窗口挂载子view
    [view addSubview: gView];

#elif defined(PLATFORM_IOS) && defined(GRAPHICS_VULKAN)
    UIView *view = reinterpret_cast<UIView *>(this->winId());

    auto size = this->size();
    CGRect  viewRect = CGRectMake(0, 0, size.width(), size.height());
    gView = [[UIView alloc] initWithFrame:viewRect];

    gLayer = [CAMetalLayer layer];
    gLayer.device = MTLCreateSystemDefaultDevice();
    gLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    gLayer.framebufferOnly = YES;
    gLayer.opaque = YES;
    gLayer.frame = gView.bounds;

    [gView.layer addSublayer:gLayer];
    [view addSubview:gView];
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_VULKAN)
    auto view = reinterpret_cast<NSView *>(this->winId());

    auto size = this->size();
    CGRect viewRect = CGRectMake(0, 0, size.width(), size.height());

    // 创建一个新的 NSView（或直接使用原始 view）
    gView = [[NSView alloc] initWithFrame:viewRect];

    // 创建并配置 CAMetalLayer
    gLayer = [CAMetalLayer layer];
    gLayer.device = MTLCreateSystemDefaultDevice();
    gLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    gLayer.framebufferOnly = YES;
    gLayer.opaque = YES;
    gLayer.frame = gView.bounds;

    // 将 Metal Layer 设置为 gView 的 layer
    [gView setWantsLayer:YES];
    [gView setLayer:gLayer];

    // 添加 gView 到 Qt 窗口的原始 NSView 上
    [view addSubview:gView];
#elif defined(PLATFORM_MACOS) && defined(GRAPHICS_OPENGL)
    auto view = reinterpret_cast<NSView *>(this->winId());

    auto size = this->size();
    CGRect viewRect = CGRectMake(0, 0, size.width(), size.height());

    // 创建一个新的 NSView（或直接使用原始 view）
    gView = [[NSView alloc] initWithFrame:viewRect];

    // 添加 gView 到 Qt 窗口的原始 NSView 上
    [view addSubview:gView];
#endif
}

CanvasWidget::~CanvasWidget() {
}

void *CanvasWidget::GetHandle() const {
#if defined(PLATFORM_MACOS) && defined(GRAPHICS_OPENGL)
    return gView;
#else
    return gLayer;
#endif
}

void CanvasWidget::resizeEvent(QResizeEvent *event) {
#if defined(PLATFORM_MACOS)
    const auto size = event->size();
    gView.frame = CGRectMake(0, 0, size.width(), size.height());
#else
//    const auto geometry = this->geometry() * devicePixelRatio();
    const auto size = event->size()* devicePixelRatio();
    gView.frame = CGRectMake(0, 0, size.width(), size.height());
    gLayer.frame = gView.bounds;
#endif
    QWidget::resizeEvent(event);
}

#endif
