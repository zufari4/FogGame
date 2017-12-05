#include "Editor.h"

int main(int, char**)
{
    Editor editor;
    if (!editor.Init())
        return 1;
    editor.Run();

    return 0;
}

bool Editor::Init()
{
    if (!Engine.Init("Game editor", 1024, 768, SDL_WINDOW_MAXIMIZED| SDL_WINDOW_RESIZABLE))
        return false;

    if (!Engine.SetGUIFont("./res/Roboto-Regular.ttf", 21))
        return false;

    if (!Engine.InitPhysics(vec2(0, 10)))
        return false;

    Engine.SetFrameCallback(this, &Editor::Loop);
    Engine.SetMouseDownCallback(this, &Editor::OnMouseDown);
    Engine.SetMouseUpCallback(this, &Editor::OnMouseUp);
    Engine.SetMouseMoveCallback(this, &Editor::OnMouseMove);
    Engine.SetWindowResizeCallback(this, &Editor::OnWindowResize);

    textureBtnBox = Engine.LoadTexture("./res/phy_box.png");
    textureBtnJoin = Engine.LoadTexture("./res/phy_join.png");
    textureBtnPlay = Engine.LoadTexture("./res/phy_play.png");
    textureBtnPause = Engine.LoadTexture("./res/phy_pause.png");

    int w = Engine.GetSurfaceWidth();
    int h = Engine.GetSurfaceHeight();
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(p2m(w / 2.0f), p2m(h));
    b2Body* groundBody = Engine.CreateBody(&groundBodyDef);
    b2EdgeShape shape;
    shape.Set(b2Vec2(-w, 0.0), b2Vec2(w, 0.0));
    groundBody->CreateFixture(&shape, 0.0f);

    return true;
}

void Editor::Run()
{
    Engine.phyPause = true;
    Engine.Run();
}

void Editor::Loop(Uint32 now)
{
    DrawGui();
}

void Editor::OnMouseDown(int x, int y, int button)
{
    //rect->Show();
    //rect->a = vec2(x, y);
}

void Editor::OnMouseUp(int x, int y, int button)
{
    //rect->Hide();
}

void Editor::OnMouseMove(int x, int y)
{
    //rect->b = vec2(x, y);
}

void Editor::OnWindowResize(int w, int h)
{
    surfWidth = w;
    surfHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Editor::DrawGui()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(400, surfHeight), ImGuiCond_Always);

    ImGui::Begin("Main", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    ImVec2 v(48, 48);
    if (Engine.phyPause) {
        if (ImGui::ImageButton((ImTextureID)textureBtnPlay->id, v))
            ButtonPhyRunClick();
    }
    else {
        if (ImGui::ImageButton((ImTextureID)textureBtnPause->id, v))
            ButtonPhyRunClick();
    }
    if (ImGui::CollapsingHeader("Create object", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::TreeNode("Physics objects")) 
        {
            
            if (ImGui::ImageButton((ImTextureID)textureBtnBox->id, v)) {
                ButtonPhyBoxClick();
            }

            ImGui::SameLine();
            ImGui::ImageButton((ImTextureID)textureBtnJoin->id, v);
            ImGui::TreePop();
        }
    }

    ImGui::End();
}

void Editor::ButtonPhyBoxClick()
{
    PhyBox* box = new PhyBox();
    vec2 center(Engine.GetSurfaceWidth() / 2, Engine.GetSurfaceHeight() / 2);
    box->SetRect(center - vec2(100, 100), center + vec2(100, 100));
    box->Show();
}

void Editor::ButtonPhyRunClick()
{
    if (Engine.phyPause)
        Engine.StartPhysics();
    else Engine.PausePhysics();
}
