//
// Created by turiing on 2025/11/21.
//

#ifndef APP_H
#define APP_H

#include "app/Application.h"

class SelectionApp: public Application {
public:
    SelectionApp(int argc, char **argv);
protected:
    void render() override;
    void mousePressEvent(const MousePressEvent &event) override;
    void mouseMoveEvent(const MouseMoveEvent &event) override;
    void mouseReleaseEvent(const MouseReleaseEvent &event) override;

private:
    HyperRender::IDrawUnit* m_pScreenUnit = nullptr;
    HyperRender::ISelectionTool* m_pSelectionTool = nullptr;
    Point m_mousePressPos;
    Point m_mouseMovePos;
};

#endif //APP_H
