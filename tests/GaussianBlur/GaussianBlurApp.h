//
// Created by turiing on 2025/11/21.
//

#ifndef APP_H
#define APP_H

#include "app/Application.h"

class GaussianBlurApp: public Application {
public:
    GaussianBlurApp(int argc, char **argv);
protected:
    void render() override;
    void mousePressEvent(const MousePressEvent &event) override;
    void mouseMoveEvent(const MouseMoveEvent &event) override;
    void mouseReleaseEvent(const MouseReleaseEvent &event) override;

private:
    HyperRender::IDrawUnit* m_pScreenUnit = nullptr;
    HyperRender::IEffectTool* m_pEffectTool = nullptr;
    HyperRender::IDrawUnit* m_pTargetUnit = nullptr;
    HyperRender::IEffectFactory* m_pEffectFactory = nullptr;
    HyperRender::IGaussianBlur* m_pEffect = nullptr;
};

#endif //APP_H
