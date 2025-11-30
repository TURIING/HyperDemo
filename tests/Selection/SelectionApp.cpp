//
// Created by turiing on 2025/11/21.
//

#include "SelectionApp.h"

SelectionApp::SelectionApp(int argc, char **argv): Application(argc, argv) {
    m_pScreenUnit = m_pScreenTool->CreateDrawUnit({{0, 0}, std::bit_cast<HyperRender::Size>(m_windowSize)});
    m_pScreenTool->AddScreenObject(m_pScreenUnit);

    m_pSelectionTool = m_pToolFactory->CreateSelectionTool();
    m_pSelectionTool->ClearColor(m_pScreenUnit, HyperRender::Color::Black);
    m_pSelectionTool->SetTargetUnit(m_pScreenUnit);
}

void SelectionApp::render() {
    HyperRender::Offset2D offset = { m_mousePressPos.x, m_mousePressPos.y };
    HyperRender::Size size = { (uint32_t)(m_mouseMovePos.x - m_mousePressPos.x), (uint32_t)(m_mouseMovePos.y - m_mousePressPos.y) };
    m_pSelectionTool->Begin(m_pScreenUnit->GetArea());
    m_pSelectionTool->DoNormalSelection({offset, size}, HyperRender::Color::Black, 10);
    m_pSelectionTool->End();
    m_pSelectionTool->RenderToUnit(m_pScreenUnit);

    m_pScreenTool->Begin({0, 0, m_windowSize.width, m_windowSize.height});
    m_pScreenTool->DoRender();
    m_pScreenTool->End();
}

void SelectionApp::mousePressEvent(const MousePressEvent &event) {
    m_mousePressPos = event.GetPosition();
}

void SelectionApp::mouseMoveEvent(const MouseMoveEvent &event) {
    m_mouseMovePos = event.GetPosition();
    render();
}

void SelectionApp::mouseReleaseEvent(const MouseReleaseEvent &event) {
}
