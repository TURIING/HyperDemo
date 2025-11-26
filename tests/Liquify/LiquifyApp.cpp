//
// Created by turiing on 2025/11/21.
//

#include "LiquifyApp.h"
#include <iostream>

LiquifyApp::LiquifyApp(int argc, char **argv): Application(argc, argv) {
    m_pScreenUnit = m_pScreenTool->CreateDrawUnit({0, 0, 600, 600});
    m_pScreenTool->AddScreenObject(m_pScreenUnit, m_pScreenUnit->GetArea());

    m_pEffectTool = m_pToolFactory->CreateEffectTool();
    auto imageInfo = loadImage("/Users/turiing/Desktop/demo.png");
    m_pTargetUnit = m_pEffectTool->CreateDrawUnit({0, 0, imageInfo.imageSize.width, imageInfo.imageSize.height});
    m_pEffectTool->FillDrawUnit(m_pTargetUnit, imageInfo.ptr, imageInfo.size, {0, 0});
    m_pEffectTool->SetTargetUnit(m_pTargetUnit);
}

void LiquifyApp::render() {
    m_pEffectTool->Begin({0, 0, 0, 0});
    m_pEffectTool->DoLiquify(std::bit_cast<HyperRender::PointI>(m_newMousePos), std::bit_cast<HyperRender::PointI>(m_oldMousePos), m_isPressed, m_firstFrame);
    m_pEffectTool->End();
    m_pEffectTool->RenderToUnit(m_pScreenUnit);

    m_pScreenTool->Begin({0, 0, WINDOW_SIZE.width, WINDOW_SIZE.height});
    m_pScreenTool->DoRender();
    m_pScreenTool->End();

    m_firstFrame = false;
}

void LiquifyApp::mousePressEvent(const MousePressEvent &event) {
    m_isPressed = true;
    m_newMousePos = event.GetPosition();
}

void LiquifyApp::mouseMoveEvent(const MouseMoveEvent &event) {
    m_oldMousePos = m_newMousePos;
    m_newMousePos = event.GetPosition();
    render();
}

void LiquifyApp::mouseReleaseEvent(const MouseReleaseEvent &event) {
    m_isPressed = false;
}
