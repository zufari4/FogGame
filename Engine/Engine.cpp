#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_freetype.h>
#include "Engine.h"

float phyScale = 250.0f;

engine::engine():
    phyWorld(vec2(0.0f,10.0f)),
    init(false),
    window(NULL),
    glContext(NULL),
    phyPause(false)
{
    frameCallback.func = NULL;
    mouseDownCallback.func = NULL;
    mouseUpCallback.func = NULL;
    mouseMoveCallback.func = NULL;
}

engine::~engine()
{
    Cleanup();
}

bool engine::Init(const char* title, int width, int height, int exflags)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        return false;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    Uint32 windowFlags = SDL_WINDOW_OPENGL | exflags;

    window = SDL_CreateWindow(title, 0, 0, width, height, windowFlags);
    glContext = SDL_GL_CreateContext(window);

    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, dw, dh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, dw, dh, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.4f, 0.4f, 0.6f, 1.0f);

    ImGui_ImplSdlGL2_Init(window);

    ImGuiStyle* style = &ImGui::GetStyle();
    style->WindowRounding = 3;
    style->FrameRounding  = 3;
    style->ScrollbarRounding = 3;
    style->GrabRounding = 3;

    init = true;
    return true;
}

bool engine::InitPhysics(const vec2& gravity, float scale, int TimeUpdate, int velIters, int posIters)
{
    phyScale = scale;
    phyStep = TimeUpdate;
    phyVelIters = velIters;
    phyPosIters = posIters;
    phyHz = 1.0f/(1000.0f/(float)TimeUpdate);
    // Construct a world object, which will hold and simulate the rigid bodies.
    phyWorld.SetGravity(gravity);

    return true;
}

void engine::Cleanup()
{
    for (auto it : gameObjects)
        delete it;
    for (auto it : textures)
        delete it;
    gameObjects.clear();
    ImGui_ImplSdlGL2_Shutdown();
    if (glContext)
        SDL_GL_DeleteContext(glContext);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void engine::Run()
{
    if (!init) return;
    done = false;
    FrameCallback callback = reinterpret_cast<FrameCallback>(frameCallback.func);
    int    delta = 0;
    Uint32 now;
    last = SDL_GetTicks();
    phyAccum = 0;
    
    while (!done)
    {
        ParseEvent();

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplSdlGL2_NewFrame(window);
        
        now   = SDL_GetTicks();
        delta = (now - last);
        last  = now;
        if (delta > 48) delta = 48;
        if (!phyPause)
            UpdatePhysics(delta);
        else
            phyAccum = 0;

        if (callback)
            (frameCallback.obj->*callback)(SDL_GetTicks());

        for (auto it : gameObjects) {
            if (needUpdate)
                it->Update(now);
            if (it->visible)
                it->Draw();
        }

        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }
}

void engine::ParseEvent()
{
    static SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSdlGL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            done = true;
            break;
        case SDL_MOUSEMOTION:
            for (auto obj : gameObjects)
                obj->OnMouseMove(event.motion.x, event.motion.y);
            if (mouseMoveCallback.func) {
                MouseMoveCallback callback = reinterpret_cast<MouseMoveCallback>(mouseMoveCallback.func);
                (mouseMoveCallback.obj->*callback)(event.motion.x, event.motion.y);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            bool sel = true;
            for (auto obj : gameObjects) {
                if (obj->PointInRect(vec2(event.button.x, event.button.y))) {
                    obj->selected = sel;
                    sel = false;
                }
                else
                    obj->selected = false;
                obj->OnMouseDown(event.button.x, event.button.y, event.button.button);
            }
            if (mouseDownCallback.func) {
                MouseKeyCallback callback = reinterpret_cast<MouseKeyCallback>(mouseDownCallback.func);
                (mouseDownCallback.obj->*callback)(event.button.x, event.button.y, event.button.button);
            }
        }
            break;
        case SDL_MOUSEBUTTONUP:
            for (auto obj : gameObjects)
                obj->OnMouseUp(event.button.x, event.button.y, event.button.button);
            if (mouseUpCallback.func) {
                MouseKeyCallback callback = reinterpret_cast<MouseKeyCallback>(mouseUpCallback.func);
                (mouseUpCallback.obj->*callback)(event.button.x, event.button.y, event.button.button);
            }
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                MouseMoveCallback callback = reinterpret_cast<MouseMoveCallback>(windowResizeCallback.func);
                (windowResizeCallback.obj->*callback)(event.window.data1, event.window.data2);
            }
            break;
        }
    }
}

void engine::UpdatePhysics(int delta)
{
    phyAccum += delta;
    needUpdate = false;
    while (phyAccum >= phyStep) {
        phyWorld.Step(phyHz, phyVelIters, phyPosIters);
        phyAccum -= phyStep;
        needUpdate = true;
    }
}

SupportRectangle* engine::CreateSupportRectangle()
{
    SupportRectangle* res = new SupportRectangle();
    gameObjects.push_back(res);
    return res;
}

int engine::GetSurfaceWidth()
{
    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    return dw;
}

int engine::GetSurfaceHeight()
{
    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    return dh;
}

Texture* engine::LoadTexture(const char* filename)
{
    Texture* texture = new Texture();
    if (!texture->Load(filename)) {
        delete texture;
        texture = &emptyTexture;
    }
    else
        textures.push_back(texture);
    return texture;
}

bool engine::SetGUIFont(const char * filename, float size)
{
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(filename, size, NULL, io.Fonts->GetGlyphRangesCyrillic());
    if (font == NULL)
        return false;
    else
        ImGuiFreeType::BuildFontAtlas(io.Fonts, ImGuiFreeType::RasterizerFlags::ForceAutoHint);

    return font->IsLoaded();
}

b2Body* engine::CreateBody(b2BodyDef* def)
{
    return phyWorld.CreateBody(def);
}

void engine::DeleteBody(b2Body* body)
{
    phyWorld.DestroyBody(body);
}

void engine::AddGameObject(GameObject * obj)
{
    gameObjects.push_back(obj);
}

void engine::PausePhysics()
{
    phyPause = true;
    
}

void engine::StartPhysics()
{
    phyAccum = 0;
    last = SDL_GetTicks();
    phyPause = false;
}

void engine::SelectObject(GameObject * obj)
{
    for (auto it : gameObjects)
        if (it == obj) {
            it->selected = true;
        }
        else
            it->selected = false;
}
