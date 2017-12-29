#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_freetype.h>
#include "engine.h"

float   phy_scale = 1.0f;
float   phy_scale_inv = 1.0f;

Engine::Engine():
    phy_world(vec2(0.0f,10.0f)),
    init(false),
    window(NULL),
    gl_context(NULL),
    phy_pause(false),
    callback_frame(nullptr),
    callback_mouse_down(nullptr),
    callback_mouse_up(nullptr),
    callback_mouse_move(nullptr)
{
}

Engine::~Engine()
{
    Cleanup();
}

bool Engine::Init(const char* title, int width, int height, int exflags)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        return false;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    Uint32 window_flags = SDL_WINDOW_OPENGL | exflags;

    window     = SDL_CreateWindow(title, 0, 0, width, height, window_flags);
    gl_context = SDL_GL_CreateContext(window);

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

bool Engine::Init_physics(const vec2& gravity, float scale, int time_update, int vel_iters, int pos_iters)
{
    phy_scale = scale;
    phy_scale_inv = 1.0f / scale;
    phy_step  = time_update;
    phy_vel_iters = vel_iters;
    phy_pos_iters = pos_iters;
    phy_hz = 1.0f/(1000.0f/(float)time_update);
    phy_world.SetGravity(gravity);

    return true;
}

void Engine::Cleanup()
{
    for (auto it : game_objects)
        delete it;
    for (auto it : textures)
        delete it;
    game_objects.clear();
    ImGui_ImplSdlGL2_Shutdown();
    if (gl_context)
        SDL_GL_DeleteContext(gl_context);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::Run()
{
    if (!init) return;
    done = false;
    int delta = 0;
    Uint32 now;
    last = SDL_GetTicks();
    phy_accum   = 0;
    phy_updated = false;

    while (!done)
    {
        Parse_events();

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplSdlGL2_NewFrame(window);
        
        now   = SDL_GetTicks();
        delta = (now - last);
        last  = now;
        if (delta > 160) delta = 160;
        Update_physics(delta);

        for (auto it : game_objects) {
            if (phy_updated)
                it->Update(now);
            if (it->visible)
                it->Draw();
        }

        if (callback_frame)
            callback_frame(now);

        ImGui::Render();
        SDL_GL_SwapWindow(window);
    }
}

void Engine::Parse_events()
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
            for (const auto& obj : game_objects)
                obj->On_mouse_move(event.motion.x, event.motion.y);
            if (callback_mouse_move) {
                callback_mouse_move(event.motion.x, event.motion.y);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            vec2 cursor((float)event.button.x, (float)event.button.y);
            for (const auto& obj : game_objects) {
                if (obj->Cursor_enter(cursor)) {
                    Select_object(obj);
                    break;
                }
                else
                    obj->selected = false;
            }
            for (const auto& obj : game_objects) {
                obj->On_mouse_down(event.button.x, event.button.y, event.button.button);
            }
            if (callback_mouse_down) {
                callback_mouse_down(event.button.x, event.button.y, event.button.button);
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
            for (const auto& obj : game_objects)
                obj->On_mouse_up(event.button.x, event.button.y, event.button.button);
            if (callback_mouse_up) {
                callback_mouse_up(event.button.x, event.button.y, event.button.button);
            }
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                if (callback_window_resize) {
                    callback_window_resize(event.window.data1, event.window.data2);
                }
            }
            break;
        }
    }
}

void Engine::Update_physics(int delta)
{
    if (phy_pause) {
        phy_accum   = 0;
        phy_updated = false;
        return;
    }
    phy_accum  += delta;
    phy_updated = phy_accum >= phy_step;

    while (phy_accum >= phy_step) {
        phy_world.Step(phy_hz, phy_vel_iters, phy_pos_iters);
        phy_accum -= phy_step;
    }
}

int Engine::Get_surface_width()
{
    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    return dw;
}

int Engine::Get_surface_height()
{
    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    return dh;
}

Texture* Engine::Load_texture(const char* filename)
{
    Texture* texture = new Texture();
    if (!texture->Load(filename)) {
        delete texture;
        texture = &empty_texture;
    }
    else
        textures.push_back(texture);
    return texture;
}

bool Engine::Set_gui_font(const char * filename, float size)
{
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF(filename, size, NULL, io.Fonts->GetGlyphRangesCyrillic());
    if (font == NULL)
        return false;
    else
        ImGuiFreeType::BuildFontAtlas(io.Fonts, ImGuiFreeType::RasterizerFlags::ForceAutoHint);

    return font->IsLoaded();
}

b2Body* Engine::Create_body(const b2BodyDef& def)
{
    return phy_world.CreateBody(&def);
}

void Engine::Delete_body(b2Body* body)
{
    phy_world.DestroyBody(body);
}

b2Joint* Engine::Create_joint(b2JointDef* def)
{
    return phy_world.CreateJoint(def);
}

void Engine::Delete_join(b2Joint* j)
{
    phy_world.DestroyJoint(j);
}

void Engine::Add_game_object(Game_object* obj)
{
    game_objects.insert(game_objects.begin(), obj);
}

void Engine::Pause_physics()
{
    phy_pause   = true;
    phy_updated = false;
}

void Engine::Start_physics()
{
    phy_accum   = 0;
    phy_updated = false;
    last        = SDL_GetTicks();
    phy_pause   = false;
}

void Engine::Select_object(Game_object* obj)
{
    for (auto& it : game_objects)
       it->selected = (it == obj);
}

b2Body* Engine::Get_body_at_point(const vec2& p)
{
    for (const auto& obj : game_objects) {
        if (obj->Get_type() == otPhysicBody) {
            Phy_body_object* body_obj = static_cast<Phy_body_object*>(obj);
            if (body_obj->TestPoint(p)) {
                return body_obj->Get_body();
            }
        }
    }
    return nullptr;
}
