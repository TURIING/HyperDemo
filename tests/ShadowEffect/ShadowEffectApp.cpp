//
// Created by turiing on 2025/11/21.
//

#include "ShadowEffectApp.h"
#include <iostream>

ShadowEffectApp::ShadowEffectApp(int argc, char **argv): Application(argc, argv) {
    m_pEffectTool = m_pToolFactory->CreateEffectTool();
    m_pEffectFactory = m_pEffectTool->CreateEffectFactory();
    m_pEffect = m_pEffectFactory->CreateShadowEffect();

    auto imageInfo = loadImage("/Users/turiing/Desktop/demo5.png");
    m_pTargetUnit = m_pEffectTool->CreateDrawUnit({0, 0, imageInfo.imageSize.width, imageInfo.imageSize.height});
    m_pEffectTool->FillDrawUnit(m_pTargetUnit, imageInfo.ptr, imageInfo.size, {0, 0});
    m_pEffectTool->SetTargetUnit(m_pTargetUnit);
    m_pEffectTool->SetEffect(m_pEffect);

    m_pScreenUnit = m_pScreenTool->CreateDrawUnit({0, 0, imageInfo.imageSize.width, imageInfo.imageSize.height});
    m_pScreenTool->AddScreenObject(m_pScreenUnit);
}

void ShadowEffectApp::render() {
    m_pEffect->SetShadowInfo({ 0.0, 0.0, 0.0, 1 }, { 0, 0}, 10);
    m_pEffectTool->Begin({0, 0, 0, 0});
    m_pEffectTool->DoRender();
    m_pEffectTool->End();
    m_pEffectTool->RenderToUnit(m_pScreenUnit);

    m_pScreenTool->Begin({0, 0, WINDOW_SIZE.width, WINDOW_SIZE.height});
    m_pScreenTool->DoRender();
    m_pScreenTool->End();
}

void ShadowEffectApp::mousePressEvent(const MousePressEvent &event) {
    render();
}

void ShadowEffectApp::mouseMoveEvent(const MouseMoveEvent &event) {
}

void ShadowEffectApp::mouseReleaseEvent(const MouseReleaseEvent &event) {
}
