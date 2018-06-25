#include "engine.h"
#include "Gui.h"

namespace Engine
{
    b2World       phy_world_(b2Vec2_zero);
    std::atomic_bool phy_pause_ = true;
    float         camera_scale_ = 1.0f;
    bool          is_init_ = false;
    std::atomic_bool is_done_ = true;
    SDL_Window*   window_ = nullptr;
    SDL_GLContext gl_context_ = nullptr;
    double        phy_step_ = 0;
    float         phy_step_s_ = 0;
    int           phy_vel_iters_ = 0;
    int           phy_pos_iters_ = 0;
    double        phy_accum_ = 0;
    Uint32        phy_last_ = 0;
    bool          phy_is_updated_ = false;
    std::vector<Texture*> textures_;
    Texture       empty_texture_;
    std::vector<Game_object*> game_objects_;
    SDL_Event     event_;
    i1_callback_link cb_frame_;
    f2_callback_link cb_window_resize_;
    f2_callback_link cb_mouse_move_;
    f3_callback_link cb_mouse_down_;
    f3_callback_link cb_mouse_up_;

    bool Init(const char* title, int width, int height, float scale, Uint32 exflags)
    {
        is_init_ = false;

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            return false;

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

        window_ = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL | exflags);
        gl_context_ = SDL_GL_CreateContext(window_);
        SDL_GL_SetSwapInterval(0);

        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_MULTISAMPLE);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_POLYGON_SMOOTH);
        glClearColor(0.4f, 0.4f, 0.6f, 1.0f);

        int dw, dh;
        SDL_GL_GetDrawableSize(window_, &dw, &dh);
        Setup_camera((float)dw, (float)dh, scale);

        Gui::Init(window_);
        Gui::Set_rounding(3);

        is_init_ = true;
        return true;
    }

    bool Init_physics(const vec2& gravity, double phy_hz, int vel_iters, int pos_iters)
    {
        phy_step_ = 1000.0/phy_hz;
        phy_step_s_ = 1.0 / phy_hz;
        phy_vel_iters_ = vel_iters;
        phy_pos_iters_ = pos_iters;
        phy_world_.SetGravity(gravity);

        return true;
    }

    void Select_object(Game_object* obj)
    {
        for (auto& it : game_objects_)
            it->selected = (it == obj);
    }

    void Parse_events()
    {
        while (SDL_PollEvent(&event_))
        {
            Gui::ProcessEvent(&event_);

            switch (event_.type) {
            case SDL_QUIT:
                Stop();
                break;
            case SDL_MOUSEMOTION:
            {
                vec2 cursor((float)event_.button.x * camera_scale_, (float)event_.button.y * camera_scale_);
                for (const auto& obj : game_objects_) {
                    obj->On_mouse_move(cursor.x, cursor.y);
                }
                if (cb_mouse_move_.func) {
                    (cb_mouse_move_.obj->*cb_mouse_move_.func)(cursor.x, cursor.y);
                }
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                vec2 cursor((float)event_.button.x * camera_scale_, (float)event_.button.y * camera_scale_);
                if (phy_pause_)
                {
                    for (const auto& obj : game_objects_) {
                        if (obj->Cursor_enter(cursor)) {
                            Select_object(obj);
                            break;
                        }
                        else
                            obj->selected = false;
                    }
                }
                for (const auto& obj : game_objects_) {
                    obj->On_mouse_down(cursor.x, cursor.y, event_.button.button);
                }
                if (cb_mouse_down_.func) {
                    (cb_mouse_down_.obj->*cb_mouse_down_.func)(cursor.x, cursor.y, event_.button.button);
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                vec2 cursor((float)event_.button.x * camera_scale_, (float)event_.button.y * camera_scale_);
                for (const auto& obj : game_objects_)
                    obj->On_mouse_up(cursor.x, cursor.y, event_.button.button);
                if (cb_mouse_up_.func) {
                    (cb_mouse_up_.obj->*cb_mouse_up_.func)(cursor.x, cursor.y, event_.button.button);
                }
            }
            break;
            case SDL_WINDOWEVENT:
            {
                if (event_.window.event == SDL_WINDOWEVENT_RESIZED) {
                    if (cb_window_resize_.func) {
                        (cb_window_resize_.obj->*cb_window_resize_.func)((float)event_.window.data1, (float)event_.window.data2);
                    }
                }
            }
            break;
            }
        }
    }

    void Update_physics()
    {
        if (phy_pause_) {
            phy_accum_ = 0;
            phy_is_updated_ = false;
        }
        else {
            phy_is_updated_ = phy_accum_ >= phy_step_;
            while (phy_accum_ >= phy_step_) {
                phy_world_.Step(phy_step_s_, phy_vel_iters_, phy_pos_iters_);
                phy_accum_ -= phy_step_;
            }
        }
    }

    void Cleanup()
    {
        for (auto it : game_objects_)
            delete it;
        for (auto it : textures_)
            delete it;
        game_objects_.clear();
        Gui::Shutdown();
        if (gl_context_)
            SDL_GL_DeleteContext(gl_context_);
        if (window_)
            SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void Run()
    {
        if (!is_init_) return;
        is_done_ = false;
        Uint32 now;
        phy_last_ = SDL_GetTicks();
        phy_accum_ = 0;
        phy_is_updated_ = false;

        while (!is_done_)
        {
            Parse_events();

            now = SDL_GetTicks();
            phy_accum_ += (now - phy_last_);
            phy_last_ = now;
            if (phy_accum_ > 160) phy_accum_ = 160;
            Update_physics();

            glClear(GL_COLOR_BUFFER_BIT);
            Gui::New_frame();

            for (const auto& it : game_objects_) {
                if (phy_is_updated_)
                    it->Update(now);
                if (it->visible)
                    it->Draw();
            }

            if (cb_frame_.func) {
                (cb_frame_.obj->*cb_frame_.func)(now);
            }

            Gui::Render();
            SDL_GL_SwapWindow(window_);
        }

        Cleanup();
    }

    void Stop()
    {
        is_done_ = true;
    }

    void Setup_camera(float width, float height, float scale)
    {
        glViewport(0, 0, (GLsizei)width, (GLsizei)height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width * scale, height * scale, 0, 0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        camera_scale_ = scale;
    }


    float Get_dpi()
    {
        int i = SDL_GetWindowDisplayIndex(window_);
        if (i < 0)
            return 96;
        float dpi;
        if (SDL_GetDisplayDPI(i, &dpi, nullptr, nullptr) != 0)
            dpi = 96;
        return dpi;
    }

    Texture* Load_texture(const char* filename)
    {
        Texture* texture = new Texture();
        if (!texture->Load(filename)) {
            delete texture;
            texture = &empty_texture_;
        }
        else {
            textures_.push_back(texture);
        }
        return texture;
    }

    void Pause_physics()
    {
        phy_pause_ = true;
        phy_is_updated_ = false;
    }

    void Start_physics()
    {
        phy_accum_ = 0;
        phy_is_updated_ = false;
        phy_last_ = SDL_GetTicks();
        phy_pause_ = false;
    }

    float Get_surface_width()
    {
        int dw;
        SDL_GL_GetDrawableSize(window_, &dw, nullptr);
        return (float)dw;
    }

    float Get_surface_height()
    {
        int dh;
        SDL_GL_GetDrawableSize(window_, nullptr, &dh);
        return (float)dh;
    }

    void Add_game_object(Game_object* obj)
    {
        game_objects_.insert(game_objects_.begin(), obj);
    }

    b2Body* Get_body_at_point(const vec2& p)
    {
        for (const auto& obj : game_objects_) {
            if (obj->Get_type() == otPhysicBody) {
                Phy_body_object* body_obj = static_cast<Phy_body_object*>(obj);
                if (body_obj->TestPoint(p)) {
                    return body_obj->Get_body();
                }
            }
        }
        return nullptr;
    }

    bool Physic_paused()
    {
        return phy_pause_;
    }

    float Get_camera_scale()
    {
        return camera_scale_;
    }

    b2World& Get_world()
    {
        return phy_world_;
    }

    unsigned Get_fps()
    {
        return ImGui::GetIO().Framerate;
    }

    void SetWindowTitle(const char* text)
    {
        SDL_SetWindowTitle(window_, text);
    }

    void _Set_callback_frame(Base_class* object, i1_callback function)
    {
        cb_frame_.obj = object;
        cb_frame_.func = function;
    }

    void _Set_callback_window_resize(Base_class* object, f2_callback function)
    {
        cb_window_resize_.obj = object;
        cb_window_resize_.func = function;
    }

    void _Set_callback_mouse_down(Base_class* object, f3_callback function)
    {
        cb_mouse_down_.obj = object;
        cb_mouse_down_.func = function;
    }

    void _Set_callback_mouse_up(Base_class* object, f3_callback function)
    {
        cb_mouse_up_.obj = object;
        cb_mouse_up_.func = function;
    }

    void _Set_callback_mouse_move(Base_class* object, f2_callback function)
    {
        cb_mouse_move_.obj = object;
        cb_mouse_move_.func = function;
    }
}


