//
// Created by turiing on 2025/11/21.
//

#include "SwirlWarpApp.h"
#include <iostream>

SwirlWarpApp::SwirlWarpApp(int argc, char **argv): Application(argc, argv) {
    m_pEffectTool = m_pToolFactory->CreateEffectTool();
    m_pEffectFactory = m_pEffectTool->CreateEffectFactory();
    m_pEffect = m_pEffectFactory->CreateSwirlWarpEffect();

    auto imageInfo = loadImage("/Users/turiing/Desktop/demo.png");
    m_pTargetUnit = m_pEffectTool->CreateDrawUnit({0, 0, imageInfo.imageSize.width, imageInfo.imageSize.height});
    m_pEffectTool->FillDrawUnit(m_pTargetUnit, imageInfo.ptr, imageInfo.size, {0, 0});
    m_pEffectTool->SetTargetUnit(m_pTargetUnit);
    m_pEffectTool->SetEffect(m_pEffect);

    m_pScreenUnit = m_pScreenTool->CreateDrawUnit({0, 0, imageInfo.imageSize.width, imageInfo.imageSize.height});
    m_pScreenTool->AddScreenObject(m_pScreenUnit);
}

void SwirlWarpApp::render() {
    m_pEffect->SetSwirlInfo({m_mousePos.x, m_mousePos.y}, -360, 100);
    m_pEffectTool->Begin({0, 0, 0, 0});
    m_pEffectTool->DoRender();
    m_pEffectTool->End();
    m_pEffectTool->RenderToUnit(m_pScreenUnit);

    m_pScreenTool->Begin({0, 0, WINDOW_SIZE.width, WINDOW_SIZE.height});
    m_pScreenTool->DoRender();
    m_pScreenTool->End();
}

void SwirlWarpApp::mousePressEvent(const MousePressEvent &event) {
    m_mousePos = event.GetPosition();
    render();
}

void SwirlWarpApp::mouseMoveEvent(const MouseMoveEvent &event) {
    m_mousePos = event.GetPosition();
    render();
}

void SwirlWarpApp::mouseReleaseEvent(const MouseReleaseEvent &event) {
}
