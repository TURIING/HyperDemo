//
// Created by turiing on 2025/11/21.
//

#ifndef APP_H
#define APP_H

#include "app/Application.h"

class SectionApp: public Application {
public:
    SectionApp(int argc, char **argv);
protected:
    void render() override;
    void mousePressEvent(const MousePressEvent &event) override;
    void mouseMoveEvent(const MouseMoveEvent &event) override;
    void mouseReleaseEvent(const MouseReleaseEvent &event) override;

private:
    Point m_oldMousePos;
    Point m_newMousePos;
    bool m_isPressed = false;
    bool m_firstFrame = true;
    HyperRender::IDrawUnit* m_pScreenUnit = nullptr;
    HyperRender::IEffectTool* m_pEffectTool = nullptr;
    HyperRender::IDrawUnit* m_pTargetUnit = nullptr;
};

#endif //APP_H
