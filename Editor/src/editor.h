#pragma once
#include <stdio.h>
#include <imgui.h>
#include <SDL.h>
#include <Box2D/Box2D.h>
#include "engine.h"
#include "base_class.h"
#include "phy_box.h"

class Editor: public BaseClass
{
private:
    Texture* textureBtnBox;
    Texture* textureBtnJoin;
    Texture* textureBtnPlay;
    Texture* textureBtnPause;
    int surfWidth;
    int surfHeight;
public:
    Editor() {};
    bool Init();
    void Run();
    void Loop(Uint32);
    void OnMouseDown(int x, int y, int button);
    void OnMouseUp(int x, int y, int button);
    void OnMouseMove(int x, int y);
    void OnWindowResize(int w, int h);
    void DrawGui();
    void ButtonPhyBoxClick();
    void ButtonPhyRunClick();
};
